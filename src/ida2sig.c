
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

/* For output */
#define PRE_SIG  "\"\\x"
#define PRE_HEX  "\\x"
#define UNK_STR  "?"
#define POST_SIG "\"\n"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"sig\"\n", argv[0]);
        return 1;
    }

    const char* sig  = argv[1];
    bool was_pre_hex = false;

    printf("%s", PRE_SIG);

    for (int i = 0; sig[i] != '\0'; i++) {
        char c = tolower(sig[i]);
        switch (c) {
            case ' ':
                was_pre_hex = true;
                break;
            case '?':
                printf("%s", UNK_STR);
                was_pre_hex = false;
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
                if (was_pre_hex)
                    printf("%s", PRE_HEX);

                /* Respect original case */
                putchar(sig[i]);
                was_pre_hex = false;
                break;
        }
    }

    printf("%s", POST_SIG);

    return 0;
}
