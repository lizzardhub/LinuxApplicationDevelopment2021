#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _(STRING) gettext(STRING)

enum {
    ANS_LEN = 1000,
    INTERVAL_L = 1,
    INTERVAL_R = 101
};

int
read_ans(char *buf) {
    while (1) {
        scanf("%s", buf);
        if (strcmp(buf, _("yes")) == 0) {
            return 1;
        } else if (strcmp(buf, _("no")) == 0) {
            return 0;
        } else {
            printf("%s", _("Please enter \"yes\" or \"no\"\n"));
        }
    }
}

int
main(void) {
    setlocale(LC_ALL, "");
    bindtextdomain("guess", getenv("PWD"));
    textdomain("guess");

    printf("%s\n", _("Hello! Choose a number, I'll try to guess it."));
    
    int l = INTERVAL_L;
    int r = INTERVAL_R;
    while (r - l > 1) {
        int m = (l + r) / 2;
        printf(_("Is your number larger than %d?\n"), m - 1);
        char ans[ANS_LEN];
        if (read_ans(ans)) { 
            // x >= m
            l = m;
        } else {
            // x < m
            r = m;
        }
    }

    printf("%s %d!\n", _("Your number is"), l);

    exit(0);
}