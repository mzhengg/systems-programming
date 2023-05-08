#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "linkedlist.h"

#define MAX_TOKEN_LEN 32
#define FORMAT_STR "%32s"

void print_help(void);

int main(int argc, char **argv) {
  int res;
  char token[MAX_TOKEN_LEN + 1]; // add 1 for NUL

  node *head = NULL;

  while (1) {
    res = scanf(FORMAT_STR, token);
    if (res == EOF)
      break;
    if (!isspace(getchar())) {
      error_message(ERR_LONGTOKEN);
      exit(-1);
    }
    // puts(token);

    if (!strcmp(token, "help")) {
      print_help();
      continue;
    } else if (!strcmp(token, "reverse") || !strcmp(token, "r")) {
      head = reverse_list(head);
    } else if (!strcmp(token, "info") || !strcmp(token, "i")) {
      printf("head = %p\n", head);
      print_list_details(head);
    }
    // could support more functions/commands
    else {
      // try to convert it to an integer
      // we use atol()
      long lv;
      char *endptr;

      char action = 'a';
      char *pn = token;

      if (token[0] == 'd' || token[0] == 'a' || token[0] == 'p') {
        if (!token[1]) {
          error_message(ERR_NONUMBER);
          continue;
        }

        action = token[0];
        pn++;
      }

      lv = strtol(pn, &endptr, 10); // decimal numbers
      if (*endptr) {                // the entire token should be a valid number
        error_message(ERR_UNKNOWNTOEKN);
        printf("%s\n", token);
        continue;
      }

      int i = lv;

      switch (action) {
      case 'd':
        head = delete_node(head, i);
        break;
      case 'a':
      case 'p': {
        node *p;
        p = find_node(head, i);
        if (p != NULL) {
          print_node(p);
        } else {
          p = new_node(i);
          head = (action == 'p') ? prepend(head, p) : append(head, p);
        }
        break;
      }
      default:
        // should not be here.
        break;
      }
    }
    print_list(head);
  }
  head = delete_list(head);
  return 0;
}

void print_help(void) {
  // Example of long strings
  char *helpmsg = "a<n> or <n>    append the number n to the list.\n"
                  "               If n is alrady on the list, print the "
                  "informaton about node.\n"
                  "p<n>           prepend the number n to the list.\n"
                  "               If n is alrady on the list, print the "
                  "informaton about node.\n"
                  "d<n>           delete the number n from the list.\n"
                  "               if n is not found, print \"The number is not "
                  "on the list.\"\n"
                  "reverse or r   reverse the list.\n"
                  "info or i      print the list.\n";
  puts(helpmsg);
}
