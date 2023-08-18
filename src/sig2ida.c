
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

/* For output */
#define PRE_SIG  "\""
#define PRE_HEX  " "
#define UNK_STR  " ?"
#define POST_SIG "\"\n"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"sig\"\n", argv[0]);
        return 1;
    }

    const char* sig = argv[1];

    /*
     * Meanings:
     *  -1: Start of string, we don't want to print an extra space
     *   0: Last char was not important
     *   1: Last char was '\'
     *   2: Last char was 'x' after '\'
     */
    int was_pre_hex = -1;

    printf("%s", PRE_SIG);

    for (int i = 0; sig[i] != '\0'; i++) {
        char c = tolower(sig[i]);
        switch (c) {
            case '\\':
                if (was_pre_hex == 0)
                    was_pre_hex = 1;

                break;
            case 'x':
                if (was_pre_hex == 1)
                    was_pre_hex = 2;
                else
                    was_pre_hex = 0;
                break;
            case '?':
                printf("%s", UNK_STR);
                was_pre_hex = 0;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
                if (was_pre_hex == 2)
                    printf("%s", PRE_HEX);

                /* Respect original case */
                putchar(sig[i]);
                was_pre_hex = 0;

                break;
            default:
                /* Invalid pattern */
                break;
        }
    }

    printf("%s", POST_SIG);

    return 0;
}
