#include <stdio.h>
#include <stdlib.h>

enum {
    DEC_BASE = 10,
    ARGS0 = 1,
    ARGS1 = 2,
    ARGS2 = 3,
    ARGS3 = 4
};

void
die(int condition, const char *message) {
    if (condition) {
        printf("Exiting with error: %s\n", message);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {
    if (argc == ARGS0) {
        printf("Help!\n");
        return 0;
    }
    int m = 0;
    int n = 0;
    int s = 1;
    
    int arg = 1;
    if (argc == ARGS1) {
        n = strtol(argv[arg++], NULL, DEC_BASE);
    } else if (argc == ARGS2) {
        m = strtol(argv[arg++], NULL, DEC_BASE);
        n = strtol(argv[arg++], NULL, DEC_BASE);
    } else if (argc >= ARGS3) {
        m = strtol(argv[arg++], NULL, DEC_BASE);
        n = strtol(argv[arg++], NULL, DEC_BASE);
        s = strtol(argv[arg++], NULL, DEC_BASE);
    }
    
    if (s > 0) {
        for (int i = m; i < n; i += s) {
            printf("%d\n", i);
        }
    } else if (s < 0) {
        for (int i = m; i > n; i += s) {
            printf("%d\n", i);
        }
    }
    // if s == 0, pass

    return 0;
}