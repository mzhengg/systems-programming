#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// types of hosts (GOOD)
enum TYPE {S, I, R};

//TODO: Implement idx (GOOD)
//idx returns an integer to be used for hashing
//this integer should be unique for every x, y pair in your grid
int idx(int x, int y, int k)
{
    return (x * k + y);
}

// host variables (GOOD)
typedef struct Host
{
    int id;
    int x, y;
    int t;
    enum TYPE type;
} THost;

// node information (GOOD)
typedef struct node_tag {
   THost host;              
   struct node_tag *next;
} node;

//create a node whose value is a specific host (GOOD)
//return a pointer to the created node 
node *create_node(THost host) 
{
    node *newnode = malloc(sizeof(node));
    newnode->host = host;
    newnode->next = NULL;
    return newnode;
}

//add_first() should add to the beginning of a linked list (GOOD)
//note the type: 'node **head'
//note that it does not return a value 
void add_first(node **head, node *newnode)
{
    newnode->next = *head;
    *head = newnode;
}

//remove the first node from the list (GOOD)
//note the type: 'node **head'
//return a pointer to the removed content
node *remove_first(node **head) 
{
    node *removed = *head;

    if (removed != NULL) {
        *head = removed->next;
    }

    return removed;
}

//remove all the nodes in the list (GOOD)
//and free all the allocated memory
void remove_all(node **head)
{
    node *current = *head;

    while (current != NULL) {
        node *next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

//location_match checks whether a linked list contains (GOOD)
//one or more hosts in the same location as 'host'
//return 1 if there is a match, 0 if not
int location_match(node *head, THost host)
{
    node *current = head;

    while (current != NULL) {
        if (current->host.x == host.x && current->host.y == host.y) {
            return 1;
        }

        current = current->next;
    }

    return 0;
}

//hash function included for your convenience :) (GOOD)
unsigned hash(unsigned a)
{
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a;
}

//summary prints out the proportions of different host types. (GOOD)
//It returns 1 if the number of infected hosts is not 0. 
int summary(THost hosts[], int m)
{   
    int S_n, I_n, R_n;
    
    S_n = I_n = R_n = 0;
    for(int i = 0; i < m; i++)
    {   
        S_n += (hosts[i].type == S);
        I_n += (hosts[i].type == I);
        R_n += (hosts[i].type == R);
    }
    // printf("    S        I        R\n");
    // printf("%lf %lf %lf\n", (double)S_n/(S_n + I_n + R_n), 
    // (double)I_n/(S_n + I_n + R_n), (double)R_n/(S_n + I_n + R_n));
    if(I_n == 0)
    {
        printf("    S        I        R\n");
        printf("%lf %lf %lf\n", (double)S_n/(S_n + I_n + R_n), 
        (double)I_n/(S_n + I_n + R_n), (double)R_n/(S_n + I_n + R_n));
    }
    return I_n > 0;
}

// one_round (ISSUE)
int one_round(THost *hosts, int m, node *p_arr[], int n_arr, int k, int T)
{
    // convert S -> I and I -> R based on where the hosts currently are located
    for (int i = 0; i < m; i++) {
        if (hosts[i].type == S) {
            int index = hash(idx(hosts[i].x, hosts[i].y, k)) % n_arr;

            if (location_match(p_arr[index], hosts[i])) {
                hosts[i].type = I;
                hosts[i].t = 0;
            }
        }
        
        else if (hosts[i].type == I) {
            if (hosts[i].t == T - 1) {
                hosts[i].type = R;
            }

            else {
                hosts[i].t++;
            }
        }
    }

    // reset linked list because infected hosts may have changed so the current list is inaccurate
    for (int i = 0; i < n_arr; i++) {
        remove_all(&p_arr[i]);
    }

    // update locations for all hosts
    for (int i = 0; i < m; i++) {
        int r = rand() % 4;

        // 0: up, 1: right, 2: down, 3: left
        switch (r) {
            case 0:
                if (hosts[i].y < k) {
                    hosts[i].y += 1;
                } else {
                    hosts[i].y = -k;
                }
                break;
            case 1:
                if (hosts[i].x < k) {
                    hosts[i].x += 1;
                } else {
                    hosts[i].x = -k;
                }
                break;
            case 2:
                if (hosts[i].y > -k) {
                    hosts[i].y -= 1;
                } else {
                    hosts[i].y = k;
                }
                break;
            case 3:
                if (hosts[i].x > -k) {
                    hosts[i].x -= 1;
                } else {
                    hosts[i].x = k;
                }
                break;
        }

        // rebuild linked list for I hosts only
        if (hosts[i].type == I) {
            node *r = create_node(hosts[i]);
            int index = hash(idx(hosts[i].x, hosts[i].y, k)) % n_arr;
            add_first(&(p_arr[index]), r);
        }
    }

    return summary(hosts, m);
}

int main(int argc, char *argv[]) // (GOOD)
{

    if(argc != 5)
    {
        printf("Usage: %s k m T N\n", argv[0]);
        return 0;
    }

    int k = atoi(argv[1]);
    int m = atoi(argv[2]);
    int T = atoi(argv[3]);
    int N = atoi(argv[4]);

    assert(k >= 0 && k <= 1000);
    assert(m >= 1 && m <= 100000);
    assert(T >= 1);
    assert(N > 0 && N <= 100000);
    srand(12345);

    //initialize hosts
    THost hosts[m];

    hosts[0].id = 0;
    hosts[0].x = 0;
    hosts[0].y = 0;
    hosts[0].t = 0;
    hosts[0].type = I;

    for(int i = 1; i < m; i ++)
    {
        hosts[i].id = i;
        hosts[i].x = rand() % (2*k + 1) - k;
        hosts[i].y = rand() % (2*k + 1) - k;
        hosts[i].t = 0;
        hosts[i].type = S;
    }

    //initialize linked lists
    node *p_arr[N];

    for(int i = 0; i < N; i++)
    {
        p_arr[i] = NULL;
    }
    node *r = create_node(hosts[0]);
    int index = hash(idx(hosts[0].x, hosts[0].y, k)) % N;
    add_first(&(p_arr[index]), r);

    //simulation
    while(one_round(hosts, m, p_arr, N, k, T));

    return 0;
}