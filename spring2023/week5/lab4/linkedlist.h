#ifndef LINKEDLIST_H
#define LINKEDLIST_H

enum ErrorNumber {
  ERR_OK,
  ERR_NOMEM,
  ERR_NODELETE,
  ERR_NOTFOUND,
  ERR_NOSORT,
  ERR_NOREVERSE,
  ERR_LONGTOKEN,
  ERR_NONUMBER,
  ERR_UNKNOWNTOEKN,
  ERR_END
};

void error_message(enum ErrorNumber errno);

/***** list *****/
typedef struct node_tag {
  int v;
  struct node_tag *next; // A pointer to this type of struct
} node;                  // Define a type. Easier to use.


node *new_node(int v);
node *prepend(node *head, node *newnode);
node *find_node(node *head, int v);
node *find_last(node *head);
node *append(node *head, node *newnode);
node *delete_list(node *head);
void print_list(node *head);
void print_node(node *p);
void print_list_details(node *head);

node *delete_node(node *head, int v);
node *reverse_list(node *head);

#endif
