#include <stdio.h>
#include <stdlib.h>

double two_d_random(int n) {
    // center of array
    int middle = (2*n+1) / 2;

    // initializing x and y to middle of array
    int x = middle;
    int y = middle;

    // keep track of points visited that are INSIDE the square
    double pointsInside = 1;

    // SPECIAL CASE: when n = 1, we know there can only be one point inside and visited
    if (n == 1) {
        return pointsInside;
    }

    // array to keep track of visited points
    int visited[2*n+1][2*n+1];

    // initalize contents in array to 0
    for (int i = 0; i < 2*n+1; i++) {
        for (int j = 0; j < 2*n+1; j++) {
            visited[i][j] = 0;
        }
    }

    // start at the origin and mark that as a visited point
    visited[middle][middle] = 1;

    // as long as x and y are inside the n x n square, then keep taking steps
    while (1) {
        // generate random number to decide which way to go for next step 
        int r = rand() % 4;

        // based on r, move in the corresponding direction
        switch (r) {
            case 0: // going UP
                y += 1;
                break;
            
            case 1: // going RIGHT
                x += 1;
                break;
            
            case 2: // going DOWN
                y -= 1;
                break;
            
            case 3: // going LEFT
                x -= 1;
                break;
        }

        if ((x <= 0) || (x >= 2*n) || (y <= 0) || (y >= 2*n)) {
            break;
        }

        // if we haven't visited this point before and it's inside square, then increment pointsInside
        if (visited[x][y] == 0) {
            pointsInside += 1;

            // we visited the point, so now we update the visited array with this new point
            visited[x][y] = 1;
        }
    }

    // total number of points in the square
    double totalPoints = (2 * n - 1) * (2 * n - 1);
    
    // walker has reached an edge of the square
    // return the fraction of visited (x, y) coordinates inside (not including) the square
    return (double) pointsInside / totalPoints;
}

//Do not change the code below
int main(int argc, char* argv[])
{
    int trials = 1000;
    int i, n, seed;
    if (argc == 2) seed = atoi(argv[1]);
    else seed = 12345;

    srand(seed);
    for(n=1; n<=64; n*=2)
    {   
        double sum = 0.;
        for(i=0; i < trials; i++)
        {
            double p = two_d_random(n);
            sum += p;
        }
        printf("%d %.3lf\n", n, sum/trials);
    }
    return 0;
}