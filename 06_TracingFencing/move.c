#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

/*
RETURN CODES
0 - success
1 - cannot open input file
2 - cannot open output file
3 - error during copying
4 - cannot close input file
5 - cannot close output file
6 - cannot delete input file
-1 - any other error
*/

enum {
    ARG_CNT = 2,
    BUF_BYTES = 1<<20 // 1 Megabyte
};

static char *infile, *outfile;
static FILE *inf, *ouf;

void
die(int condition, const char *message, int retcode) {
    if (condition) {
        printf("Exiting: %s\n", message);
        exit(retcode);
    }
}

void
die_errno(int condition, const char *message, int retcode) {
    if (condition) {
        char *errorbuf = strerror(errno);
        printf("Exiting: %s (%s)\n", message, errorbuf);
        exit(retcode);
    }
}

void
delete_and_quit(int condition, const char *message, int retcode) {
    if (condition) {
        die_errno(fclose(inf), "cannot close inf after incomplete transfer", -1);
        die_errno(fclose(ouf), "cannot close ouf after incomplete transfer", -1);
        die_errno(remove(outfile), "cannot remove outfile after incomplete transfer", -1);
        die(1, message, retcode);
    }
}

int
is_same_file(const char* file_a, const char* file_b) {
    struct stat sa;
    int res_a = stat(file_a, &sa);
    struct stat sb;
    int res_b = stat(file_b, &sb);
    if (res_a || res_b) {
        return 0;
    }

    return sa.st_dev == sb.st_dev && sa.st_ino == sb.st_ino;
}

int
main(int argc, char **argv) {
    if (argc < ARG_CNT + 1) {
        printf("Usage: ./move infile outfile\n");
        exit(-1);
    }
    int arg = 1;
    infile = argv[arg++];
    outfile = argv[arg++];
    if (is_same_file(infile, outfile)) {
        return 0;
    }
    inf = fopen(infile, "r"); 
    die_errno(inf == NULL, "cannot open infile", 1);
    ouf = fopen(outfile, "w");
    die_errno(ouf == NULL, "cannot open outfile", 2);

    int cont = 1;
    char *buf = malloc(BUF_BYTES);
    delete_and_quit(buf == NULL, "cannot malloc buffer", -1);
    while (cont) {
        size_t read_elems = fread(buf, sizeof(*buf), BUF_BYTES, inf);

        if (feof(inf)) { // file depleted
            cont = 0;
        }
        delete_and_quit(ferror(inf), "error while reading file", 3);
        
        // write to ouf
        int written_elems = 0;
        while (written_elems < read_elems) {
            size_t write_elems = fwrite(buf + written_elems, 
                sizeof(*buf), read_elems - written_elems, ouf);
            delete_and_quit(ferror(ouf), "error while writing file", 3);
            written_elems += write_elems;
        }
    }
    free(buf); // no error is possible here according to man

    die_errno(fclose(inf), "cannot close inf", 4);
    die_errno(fclose(ouf), "cannot close ouf", 5);
    die_errno(remove(infile), "cannot delete infile", 6);

    return 0;
}