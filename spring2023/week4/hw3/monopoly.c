#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//There will be m players in an array
typedef struct Player 
{
	int id;
	int loc;
	long balance;
} TPlayer;

//There will be n properties in an array
typedef struct Property
{
	int id;
	int owner_id;
	int rent;
} TProperty;


//TODO
//Implement the following function
//The player p1 needs to pay the player p2 'amount' of dollars
//If p1 has enough balance, the transaction will be successful
//Otherwise, p1 will pay all of their balance to p2, and the transaction
//is not successful 
//return 1 if the transaction is successful
//Otherwise, return 0
int transaction(TPlayer *p1, TPlayer *p2, int amount)
{
    // p1 can afford to pay p2
    if ((*p1).balance - amount >= 0) {
        (*p1).balance -= amount;
        (*p2).balance += amount;
        return 1;
    }
    // p1 cannot afford to pay p2
    else {
        (*p2).balance += (*p1).balance;
        (*p1).balance = 0;
        return 0;
    }
}

//TODO
//Finish the following function
//If one player cannot pay rent to another player, this function should return 0. 
//The rest of the players will not get chances to play when this happens 

int one_round(int m, int n, TPlayer p[], TProperty prop[])
{
	for(int i = 0; i < m; i++)
	{
		int steps = rand() % 6 + 1 + rand() % 6 + 1;
		//fill in the code below

        // if player i moves past n-1
        if ((p[i].loc + steps) > (n - 1)) {
            // first take steps until the end (n-1)
            int stepsToEnd = n - p[i].loc;
            // then calculate amount of steps remaining
            int stepsRemaining = steps - stepsToEnd;
            // start again from 0
            p[i].loc = 0;
            // whenever a player goes back to property 0, n dollars will be awarded to the player
            p[i].balance += n;
            // and take the remaining steps
            p[i].loc += stepsRemaining;
        }
		// otherwise player i has not passed n-1
		else {
			// player i takes steps forward
			p[i].loc += steps;
		}

		// now check if player i landed on its own property
		if (prop[p[i].loc].owner_id == i) {
			// if so, do nothing
		}
		// or, player m could've landed on an empty property
		else if (prop[p[i].loc].owner_id == -1) {
			// ASSUMES THAT OWNING PROPERTY DOESN'T COST ANYTHING
			prop[p[i].loc].owner_id = i;
		}
		// otherwise, player m landed on another player's property
		else {
			// if player m can afford to pay the other player
			if (transaction(&p[i], &p[prop[p[i].loc].owner_id], prop[p[i].loc].rent) == 1) {
				// then, do nothing
			}
			// otherwise, player m cannot afford to pay the other player
			else {
				// so return 0 because the game ends here
				return 0;
			}
		}
	}
	return 1;
}

//used for printing out results
void print_result(int m, TPlayer p[])
{
	printf("      id    balance\n");
	for(int i = 0; i < m; i++)
	{
		printf("%8d %8ld\n", p[i].id, p[i].balance);
	}
	long sum = 0;
	long max = 0;
	for(int i = 0; i < m; i++)
	{
		sum += p[i].balance;
		if(p[i].balance > max) max = p[i].balance;
	}
	printf("average: %f max: %ld, max/average = %lf\n", (double)sum/m, max, (double)max*m/sum); 
}

//max_rounds is needed because the game may never finish
void monopoly(int m, int n, TPlayer p[], TProperty prop[], int max_rounds)
{
	srand(12345);
	int rounds = 1;
	while(one_round(m, n, p, prop) && rounds < max_rounds)
	{
        rounds ++;
	}

	print_result(m, p);
	printf("after %d rounds\n", rounds);
}

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		printf("Usage: %s m n rounds\n", argv[0]);
		return -1;
	}
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	int rounds = atoi(argv[3]);
	assert(n >= 13);
	assert(m >= 1);
	assert(rounds >= 1);
	
	TPlayer p[m];
	TProperty prop[n];

	for(int i = 0; i < n; i++)
	{
		prop[i].id = i;
		prop[i].owner_id = -1;
		prop[i].rent = i + 1;
	}

	for(int j = 0; j < m; j++)
	{
		p[j].id = j;
		p[j].loc = 0;
		p[j].balance = n;
	}
	monopoly(m, n, p, prop, rounds);
	return 0;	
}