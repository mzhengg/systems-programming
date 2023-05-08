// Linked list demo program in CSE 3100
// The APIs may not be the best

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

// print an error message by an error number, and return
// the function does not exit from the program
// the function does not return a value
void error_message(enum ErrorNumber errno) {
  char *messages[] = {
      "OK",
      "Memory allocaton failed.",
      "Deleting a node is not supported.",
      "The number is not on the list.",
      "Sorting is not supported.",
      "Reversing is not supported.",
      "Token is too long.",
      "A number should be specified after character d, a, or p.",
      "Token is not recognized.",
      "Invalid error number."};

  if (errno < 0 || errno > ERR_END)
    errno = ERR_END;
  printf("linkedlist: %s\n", messages[errno]);
}

node *new_node(int v) {
  node *p = malloc(sizeof(node)); // Allocate memory
  if (p == NULL) {
    error_message(ERR_NOMEM);
    exit(-1);
  }

  // Set the value in the node.
  p->v = v; // you could do (*p).v
  p->next = NULL;
  return p; // return
}

node *prepend(node *head, node *newnode) {
  newnode->next = head;
  return newnode;
}

node *find_node(node *head, int v) {
  while (head != NULL) {
    if (head->v == v)
      return head;
    head = head->next;
  }
  return head;
}

node *find_last(node *head) {
  if (head != NULL) {
    while (head->next != NULL)
      head = head->next;
  }
  return head;
}

node *append(node *head, node *newnode) {
  node *p = find_last(head);

  newnode->next = NULL;
  if (p == NULL)
    return newnode;
  p->next = newnode;
  return head;
}

node *delete_list(node *head) {
  while (head != NULL) {
    node *p = head->next;
    free(head);
    head = p;
  }
  return head;
}

void print_list(node *head) {
  printf("[");
  while (head) {
    printf("%d, ", head->v);
    head = head->next;
  }
  printf("]\n");
}

void print_node(node *p) {
    printf("%p: v=%-5d next=%p\n", p, p->v, p->next);
}

void print_list_details(node *head) {
  while (head) {
    print_node(head);
    head = head->next;
  }
}

// functions that have not been implemented

node *delete_node(node *head, int v) {
    // if the head is null, list is empty and value cannot be found
    if (head == NULL) {
        error_message(ERR_NOTFOUND);
        return head;
    }

    // if the head node is the one to delete, return the next node as the new head
    if (head->v == v) {
        node * newHead = head->next;
        free(head);
        return newHead;
    }

    // else, search for the node to delete

    // keep track of previous node
    node * previousNode = head;

    // keep track of current node
    node * currentNode = head->next;

    // iterate through the linked list
    while (currentNode != NULL) {
        // if the current node equals the value v
        if (currentNode->v == v) {
            // set the previous node's next pointer to the current node's next node
            previousNode->next = currentNode->next;

            // free up memory used by the deleted node
            free(currentNode);

            // return the head
            return head;
        }

        // if value v has not yet been found

        // set the previous node to current node for next iteration
        previousNode = currentNode;
        
        // set the current node to the next node for next iteration
        currentNode = currentNode->next;
    }

    // if the value was not found, print error message
    error_message(ERR_NOTFOUND);
    return head;
}

/*
 * Given a pointer to the head node of an acyclic list, change the
 * next links such that the nodes are linked in reverse order.
 * Allocating new nodes or copying values from one node to another
 * is not allowed, but you may use additional pointer variables.
 * Return value is a pointer to the new head node.
 */
node *reverse_list(node *head) { 
    // to keep track of previous node
    node * previousNode = NULL;

    // to keep track of current node
    node * currentNode = head;

    // to keep track of next node
    node * nextNode = NULL;

    // iterate through the nodes in the list
    while (currentNode != NULL) {
        nextNode = currentNode->next;
        currentNode->next = previousNode;
        previousNode = currentNode;
        currentNode = nextNode;
    }

    return previousNode;
}