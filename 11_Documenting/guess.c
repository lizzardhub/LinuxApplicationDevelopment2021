/*! \mainpage
\verbatim
Usage: guess [OPTION...]
A number divination program that reads your mind.

  -r, --roman                Print numbers in Roman numeric system
  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version

Report bugs to <maximelianos.m@gmail.com>.

\endverbatim
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <libintl.h>
#include <locale.h>
#include <argp.h>

/** @file guess.c
 * Implementation
 * 
 * A number divination program that reads your mind.
 * Numbers can be shown in Roman numeric system by using -r cmd option.
 *
 */

#define _(STRING) gettext(STRING)

enum {
    ANS_LEN = 100,
    INTERVAL_L = 1,
    INTERVAL_R = 4000,

    CODE_I = 1,
    CODE_V = 5,
    CODE_X = 10,
    CODE_L = 50,
    CODE_C = 100,
    CODE_D = 500,
    CODE_M = 1000
};

/** Calculate roman number string for @p x.
 *
 * @param x — number to be converted
 * @param buf — an allocated string where result is stored
 */
void
to_roman(int x, char *buf) {
    char* roman[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
    int numbers[] = { 1,   4,    5,   9,   10,   40,  50,   90,  100, 400,  500, 900, 1000};
    int n_idx = 12;

    buf[0] = '\0';
    while (x > 0) {
        int cur_num = numbers[n_idx];
        if (x >= cur_num) {
            strcat(buf, roman[n_idx]);
            x -= cur_num;
        } else {
            n_idx -= 1;
        }
    }
}

/** Convert from roman number to arabic.
 *
 * @param buf — a string containing roman number string
 * @return converted arabic number
 */
int
from_roman(char *buf) {
    int codes[ANS_LEN];
    int len = strlen(buf);
    int i = 0;
    for (i = 0; i < len; i++) {
        switch (buf[i])
        {
        case 'I':
            codes[i] = CODE_I;
            break;
        case 'V':
            codes[i] = CODE_V;
            break;
        case 'X':
            codes[i] = CODE_X;
            break;
        case 'L':
            codes[i] = CODE_L;
            break;
        case 'C':
            codes[i] = CODE_C;
            break;
        case 'D':
            codes[i] = CODE_D;
            break;
        case 'M':
            codes[i] = CODE_M;
            break;
        default:
            break;
        }
    }

    int res = 0;
    i = 0;
    while (i < len) {
        if (i < len - 1 && codes[i] < codes[i + 1]) {
            res += codes[i + 1] - codes[i];
            i += 2;
        } else {
            res += codes[i];
            i += 1;
        }
    }
    return res;
}

/** After asking the user, read the answer in the form "yes" or "no".
 *
 * @param buf — an allocated buffer, input is read into it
 * @return 1 if "yes", 0 if "no", if input does not match then asks again
 */
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

const char *argp_program_version =
    "guess 1.0";
const char *argp_program_bug_address =
    "<maximelianos.m@gmail.com>";

struct arguments {
    int arg_roman;
};

static error_t
parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;

    switch (key) {
        case 'r':
            arguments->arg_roman = 1;
            break;
        case ARGP_KEY_ARG:
            /* we don't have non-keyword arguments */
            argp_usage(state);
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

int
main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    bindtextdomain("guess", getenv("PWD"));
    textdomain("guess");

    // CMD option parsing

    char doc[ANS_LEN] = {0};
    sprintf(doc, "%s", _("A number divination program that reads your mind."));

    char arg_roman_help[ANS_LEN] = {0};
    sprintf(arg_roman_help, "%s", _("Print numbers in Roman numeric system"));
    struct argp_option options[] = {
        {"roman", 'r', 0, 0, arg_roman_help, 0},
        {0}
    };
    struct argp argp = {options, parse_opt, 0, doc};

    struct arguments arguments = {0};
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    printf("%s\n", _("Hello! Choose a number from 1 to 3999, I'll try to guess it."));
    
    int l = INTERVAL_L;
    int r = INTERVAL_R;
    while (r - l > 1) {
        int m = (l + r) / 2;

        char number[ANS_LEN];
        if (arguments.arg_roman) {
            to_roman(m - 1, number);
        } else {
            sprintf(number, "%d", m - 1);
        }
        printf(_("Is your number larger than %s?\n"), number);

        char ans[ANS_LEN];
        if (read_ans(ans)) { 
            // x >= m
            l = m;
        } else {
            // x < m
            r = m;
        }
    }

    char number[ANS_LEN];
    if (arguments.arg_roman) {
        to_roman(l, number);
    } else {
        sprintf(number, "%d", l);
    }
    printf("%s %s!\n", _("Your number is"), number);

    return 0;
}