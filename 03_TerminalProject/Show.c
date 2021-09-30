#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

enum {
    KEY_ESC = 27,
    STR_BUF_SIZE = 1000
};

struct DynamicString {
    char *buf;
    size_t len, mem_size;
};

void init_string(struct DynamicString *s, size_t initial_size) {
    s->buf = calloc(initial_size, sizeof(*(s->buf)));
    s->len = 0;
    s->mem_size = initial_size;
    s->buf[s->len] = '\0';
}

void string_insert(struct DynamicString *s, char c) {
    if (s->len > s->mem_size / 2) {
        s->mem_size <<= 1;
        s->buf = realloc(s->buf, s->mem_size * sizeof(*(s->buf)));
    }
    s->buf[s->len] = c;
    s->len++;
    s->buf[s->len] = '\0';
}

struct DynamicArray {
    struct DynamicString **buf;
    size_t len, mem_size;
};

void init_array(struct DynamicArray *s, size_t initial_size) {
    s->buf = calloc(initial_size, sizeof(*(s->buf)));
    s->len = 0;
    s->mem_size = initial_size;
}

void array_insert(struct DynamicArray *s, struct DynamicString *p) {
    if (s->len > s->mem_size / 2) {
        s->mem_size <<= 1;
        s->buf = realloc(s->buf, s->mem_size * sizeof(*(s->buf)));
    }
    s->buf[s->len] = p;
    s->len++;
    s->buf[s->len] = 0;
}

void
die(int condition, const char *message) {
    if (condition) {
        printf("Exiting with error: %s\n", message);
        exit(EXIT_FAILURE);
    }
}

int
main(int argc, char **argv) {
    // Read file into memory
    FILE *f = fopen(argv[1], "r");
    int c;

    die(f == NULL, "could not open file");
    struct DynamicArray *text = malloc(sizeof(*text));
    init_array(text, STR_BUF_SIZE);
    
    int string_num = 0;
    struct DynamicString *tmp_str = malloc(sizeof(*tmp_str));
    init_string(tmp_str, STR_BUF_SIZE);
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') {
            array_insert(text, tmp_str);
            tmp_str = malloc(sizeof(*tmp_str));
            init_string(tmp_str, STR_BUF_SIZE);
        } else {
            string_insert(tmp_str, c);
        }
    }
    if (tmp_str->len) {
        array_insert(text, tmp_str);
    }
    
    fclose(f);

    int str_cnt = text->len;
    printf("str_cnt = %d\n", str_cnt);

    int width = 80;
    int height = 30;
    die(!initscr(), "cannot initialize nscurses");
    curs_set(0);
    refresh();

    noecho();
    cbreak();
    set_escdelay(0);
    keypad(stdscr, TRUE);

    if (width >= COLS) width = COLS - 1;
    if (height >= LINES) height = LINES - 1;

    int offx = (COLS - width) / 2;
    int offy = (LINES - height) / 2;

    WINDOW *win = newwin(height, width, offy, offx);
    wrefresh(win);

    int text_pos = 0; // Index of line in all text
    char strbuf[STR_BUF_SIZE] = {0};

    int line_start = offx + 4;
    int chars_in_line = width - 5;
    

    int loop = 1;
    while (loop) {
        // Draw
        werase(win);
        mvaddstr(0, 0, argv[1]); // file title
        box(win, 0, 0);
        // file contents
        int window_height = height - 2;
        for (int str_idx = text_pos; 
                str_idx < str_cnt && str_idx - text_pos < window_height; str_idx++) {
            int copy_len = strlen(text->buf[str_idx]->buf);
            
            if (copy_len > chars_in_line) copy_len = chars_in_line;
            memcpy(strbuf, text->buf[str_idx]->buf, chars_in_line);

            mvaddstr(offy+1+str_idx-text_pos, line_start, strbuf);
        }
        //mvaddstr(LINES/2, (COLS-strlen(text[string_idx]))/2, text[string_idx]);
        
        wrefresh(win);

        // Read input
        int ch = getch();
        if (ch == KEY_ESC) {
            loop = 0;
        }
        if (ch == KEY_DOWN) {
            if (text_pos + 1 < str_cnt) text_pos += 1;
        } else if (ch == KEY_UP) {
            if (text_pos - 1 >= 0) text_pos -= 1;
        }
    }
    
    delwin(win);
    endwin();
    return 0;
}