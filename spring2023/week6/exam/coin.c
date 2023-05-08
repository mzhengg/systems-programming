#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node_tag {
	int n;
	int count;
	struct node_tag * next;
} node;

node* create_node(int n);
node* update_list(node* head, int n);
void free_list(node* head);
void print_result(node* head, int trials);
double random_double();
int one_trial(double p);
void simulation(double p, int m);

/*
 * Dynamically allocate space for a node
 * Initialize its fields as appropriate
 */
node* create_node(int n) {
	node* p = malloc(sizeof(node));
	assert(p != NULL);
	
	// Initialize values
	p->n = n;
	p->count = 1;
	p->next = NULL;

	return p;
}

/*
 *** Add a new trial to the linked list
 *
 * - If the node already exists, increment its count
 * - If the node is not in the list,
 *   insert it in the correct (sorted) place
 * 
 * Return the head of the modified list
 */
node* update_list(node* head, int n) {
	
	if(head == NULL || n < head->n) {
		
		//fill in a few lines of code below
        node *new_node = create_node(n);

        (*new_node).next = head;

        head = new_node;

        return head;
	}

	node* p = head;
	while(p!=NULL) {

		if(n == p->n) {	
			//fill in a few lines of code below
            p->count += 1;
            break;
		}

		if(p->next == NULL) {
			//fill in a few lines of code below
            node *new_node = create_node(n);

            p->next = new_node;
            break;
		}

		if(n < p->next->n) {
			//fill in a few lines of code below
            node *new_node = create_node(n);

            (*new_node).next = p->next;

            p->next = new_node;
            break;
		}
		p = p->next;
	}
	// Control flow shouldn't reach here
	return head;
}

//implement the function
void free_list(node* head) {
  while (head != NULL) {
    node *p = head->next;
    free(head);
    head = p;
  }
}

void print_result(node* head, int m) {
	node* p = head;
	printf("n\tcount\tfrequency\n");
	while(p!=NULL) {
		double freq = (double)p->count / m;
		printf("%d\t%d\t%lf\n", p->n, p->count, freq);
		p = p->next;
	}
}

double random_double() {
	return (double) rand() / RAND_MAX;
}

int one_trial(double p) {
	int n = 0;
	while(1) {
		n++;
		if(random_double() < p) {
			return n;
		}
	}

	// Control flow should never reach here
	return -1;
}

// Run n trials with probability p
// Ensure each result is reflected in a linked list
// Print the results at the end
void simulation(double p, int m) {

	node* head = NULL;

	for(int i = 0; i < m; i++)
		head = update_list(head, one_trial(p));

	printf("%d Trials with Probability %.2f\n", m, p);
	print_result(head, m);

	free_list(head);
}

int main(int argc, char* argv[]) {
	if(argc < 3) {
		printf("Usage: %s p m\n", argv[0]);
		return 1;
	}
	double p = atof(argv[1]);
	int m = atoi(argv[2]);
	srand(3100);
	simulation(p, m);
	return 0;
}