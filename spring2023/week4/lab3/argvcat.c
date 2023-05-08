#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* print out an error message and exit */
void my_error(char *s)
{
    perror(s);
    exit(1);
}

/* Concatnate two strings.
 * Dynamically allocate space for the result.
 * Return the address of the result.
 */
char *my_strcat(char *s1, char *s2)
{
    // string length is always 1 more than true length because it terminates with a null byte, \0
    // allocate space for s1 (no null byte) + s2 (include null byte)
    s1 = realloc(s1, strlen(s1) + (strlen(s2) + 1));

    // concatenate s2 to s1
    strcat(s1, s2);

    return s1;
}

int main(int argc, char *argv[])
{
    char * s = malloc(1);
    s[0] = '\0';

    s = my_strcat(s, argv[0]);

    for (int i = 1; i < argc; i++) {
        s = my_strcat(s, argv[i]);
    }

    printf("%s\n", s);

    free(s);

    return 0;
}