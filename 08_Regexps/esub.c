// # gcc -Wall -o esub esub.c && ./esub "[a-z]*([0-9]+)([a-z]*)" 1 "___abc123def___ghi456___"

#include <stdio.h>
#include <string.h>
#include <regex.h>

enum {
    STRING_BUF = 1000,
    MAX_GROUPS = 10
};

int
main(int argc, char **argv) {
    char usage_string[] = "Usage: esub <regex> <replacement> <source string>";
    if (argc < 4) {
        printf("Insufficient arguments. %s\n", usage_string);
        return 1;
    }
    char *regex_string = argv[1];
    char *replace = argv[2];
    char *source = argv[3];

    // compile regex
    regex_t regex_compiled;
    int error_code = regcomp(&regex_compiled, regex_string, REG_EXTENDED);
    if (error_code) {
        char error_msg[STRING_BUF];
        regerror(error_code, &regex_compiled, error_msg, STRING_BUF);
        fprintf(stderr, "Could not compile regular expression: %s\n", error_msg);
        return 1;
    }

    // execute match
    regmatch_t groups[MAX_GROUPS];
    error_code = regexec(&regex_compiled, source, MAX_GROUPS, groups, 0);

    if (error_code) {
        printf("%s\n", source);
    } else {
        printf("%.*s", groups[0].rm_so, source); // before match
        int i = 0;
        while (replace[i] != '\0') {
            if (replace[i] == '\\') {
                // print source group
                int group_num = replace[i + 1] - '0';
                int group_len = groups[group_num].rm_eo - groups[group_num].rm_so; 
                printf("%.*s", group_len, source + groups[group_num].rm_so);
                i += 2;
            } else {
                // print replacement char
                printf("%c", replace[i]);
                i += 1;
            }
        }
        printf("%s\n", source + groups[0].rm_eo); // after match
    }
    regfree(&regex_compiled);

    return 0;
}