#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strstr */
#include <ctype.h> /* islower */
#include <errno.h> /* Get error string */
#include <unistd.h> /* isatty */

#include "rhash.h" /* LibRHash interface */
#include "config.h" /* autotools */

#ifdef HAVE_LIBREADLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

enum {
    HASH_NAME_LEN = 20,
    MAX_LINE = 1000000, // bytes
};

int
next_line(char **line) {
#ifdef HAVE_LIBREADLINE
    if (isatty(STDIN_FILENO)) {
        *line = readline(NULL);
        if (*line == NULL) {
            return 0;
        }
        add_history(*line);
        return 1;
    }
#endif

    *line = malloc(MAX_LINE);
    char *ret = fgets(*line, MAX_LINE, stdin);
    if (ret == NULL) {
        return 0;
    }
    (*line)[strlen(*line) - 1] = '\0'; // line includes \n at the end
    return 1;
}

int
find_hash_type(char *hash_name) {
    char lowercase[HASH_NAME_LEN];
    int len = strlen(hash_name);
    for (int i = 0; i < len; i++) {
        char c = hash_name[i];
        if ('a' < c && c < 'z') {
            lowercase[i] = c - 'a' + 'A';
        } else {
            lowercase[i] = c;
        }
    }
    lowercase[len] = '\0';
    if (strcmp(lowercase, "CRC32") == 0) return RHASH_CRC32;
    if (strcmp(lowercase, "MD5") == 0) return RHASH_MD5;
    if (strcmp(lowercase, "SHA1") == 0) return RHASH_SHA1;
    if (strcmp(lowercase, "SHA256") == 0) return RHASH_SHA256;
    if (strcmp(lowercase, "SHA512") == 0) return RHASH_SHA512;
    if (strcmp(lowercase, "SHA3-256") == 0) return RHASH_SHA3_256;
    if (strcmp(lowercase, "SHA3-512") == 0) return RHASH_SHA3_512;
    if (strcmp(lowercase, "TTH") == 0) return RHASH_TTH;
    return 0;
}

int
main() {
    unsigned char digest[64];
    char output[130];

    rhash_library_init(); /* initialize static data */

    char *line;

    int cont = 1;
    while (cont) {
        if (!next_line(&line)) {
            cont = 0;
            break;
        }

        char *hash_name = strtok(line, " ");
        char *param = strtok(NULL, " ");
        if (hash_name == NULL || param == NULL) {
            fprintf(stderr, "input not recongnized, should be <hash_name> <filename-or-str>\n");
            continue;
        }

        int hash_format;
        if (islower(hash_name[0])) {
            hash_format = RHPR_BASE64;
        } else {
            hash_format = RHPR_HEX;
        }
        int hash_type = find_hash_type(hash_name);
        if (hash_type == 0) {
            fprintf(stderr, "hash type not found in supported types\n");
            continue;
        }

        if (param[0] == '\"' || param[0] == '\'') {
            // hash of string
            int len = strlen(param);
            char *substr = malloc(len - 1);
            memcpy(substr, &param[1], len - 2);
            substr[len - 2] = '\0';

            int res = rhash_msg(hash_type, substr, strlen(substr), digest);
            free(substr);
            if (res < 0) {
                fprintf(stderr, "message digest calculation error\n");
                continue;
            }
        } else {
            // hash of file
            int res = rhash_file(hash_type, param, digest);
            if (res < 0) {
                fprintf(stderr, "file digest calculation error\n");
                continue;
            }
        }
        // print result
        rhash_print_bytes(output, digest, rhash_get_digest_size(hash_type),
            (hash_format | RHPR_UPPERCASE));
        printf("%s\n", output);

        if (line) {
            free(line);
        }
    }

    return 0;
}
