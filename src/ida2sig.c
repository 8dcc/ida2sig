
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static bool use_mask = false;

static bool valid_args(int argc, char** argv) {
    bool ret = true;

    if (argc == 3) {
        if (strcmp(argv[1], "-m") != 0) {
            fprintf(stderr, "Unknown option \"%s\"\n", argv[1]);
            ret = false;
        } else {
            use_mask = true;
        }
    } else if (argc != 2) {
        fprintf(stderr, "Unknown invalid number of arguments: %d\n", argc);
        ret = false;
    }

    return ret;
}

int main(int argc, char** argv) {
    if (!valid_args(argc, argv)) {
        fprintf(stderr, "Usage: %s [-m] \"sig\"\n", argv[0]);
        return 1;
    }

    if (use_mask)
        printf("code = ");

    printf("\"");

    /* Last argument has to be the signature */
    const char* sig = argv[argc - 1];

    /* Skip preceding spaces from pattern, if any */
    while (*sig == ' ')
        sig++;

    int mask_p  = 0;
    int mask_sz = 100;
    char* mask  = NULL;

    if (use_mask)
        mask = malloc(mask_sz);

    char last_c = ' ';
    for (int i = 0; sig[i] != '\0'; i++) {
        char c = tolower(sig[i]);

        if (c == '?') {
            if (use_mask) {
                /* If we are using mask, print "\x00" instead of "?" */
                printf("\\x00");

                /* Make sure the mask string is not full */
                if (mask_p >= mask_sz) {
                    mask_sz += 100;
                    mask = realloc(mask, mask_sz);
                }

                /* Store in the mask for later */
                mask[mask_p++] = '?';
            } else {
                putchar('?');
            }
        } else if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')) {
            if (isspace(last_c) || last_c == '?') {
                printf("\\x");

                /* Placeholder for the mask, put once per byte, not IDA char */
                if (use_mask)
                    mask[mask_p++] = 'x';
            }

            /* Respect original case */
            putchar(sig[i]);
        }

        /* Save for next iteration */
        last_c = c;
    }

    printf("\"\n");

    /* If we want to print a mask, do it now */
    if (use_mask) {
        printf("mask = \"");

        for (int i = 0; i < mask_p; i++)
            putchar(mask[i]);

        printf("\"\n");
        free(mask);
    }

    return 0;
}
