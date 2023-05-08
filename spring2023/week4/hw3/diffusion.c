#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//TODO (DONE)
//Implement the below function
//Simulate one particle moving n steps in random directions
//Use a random number generator to decide which way to go at every step
//When the particle stops at a final location, use the memory pointed to by grid to 
//record the number of particles that stop at this final location
//Feel free to declare, implement and use other functions when needed
void one_particle(int *grid, int n)
{
    // initalize the particle to origin
    int x = 0, y = 0, z = 0;

    // make n random steps
    for (int i = 0; i < n; i++) {
        // generate random direction
        int dir = rand() % 6;

        // step in the random direction
        switch(dir) {
            case 0:
                x--;
                break;
            case 1:
                x++;
                break;
            case 2:
                y++;
                break;
            case 3:
                y--;
                break;
            case 4:
                z++;
                break;
            case 5:
                z--;
                break;
        }
    }

    // generate index at the x, y, z
    int index = (x + n) * (2 * n + 1) * (2 * n + 1) + (y + n) * (2 * n + 1) + (z + n);

    // increment the count at the index
    grid[index]++;
}

//TODO
//Implement the following function
//This function returns the fraction of particles that lie within the distance
//r*n from the origin (including particles exactly r*n away)
//The distance used here is Euclidean distance
//Note: you will not have access to math.h when submitting on Mimir
double density(int *grid, int n, double r)
{
    // number of particles <= r*n distance from the origin
    int count = 0;

    // total number of particles in the sphere
    int total = 0;

    // the radius
    double radius = r * n;

    // size of each dimension (x, y, z)
    int size = 2 * n + 1;

    // find all the particles in the sphere
    for (int x = -n; x <= n; x++) {
        for (int y = -n; y <= n; y++) {
            for (int z = -n; z <= n; z++) {
                // generate index at the x, y, z
                int index = (x + n) * size * size + (y + n) * size + (z + n);

                // add particles at the index to total
                total += grid[index];
            }
        }
    }

    // find the particles <= r*n distance from the origin
    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            for (int z = -radius; z <= radius; z++) {
                // generate index at the x, y, z
                int index = (x + n) * size * size + (y + n) * size + (z + n);

                // if the current coordinate^2 is <= radius^2 (to bypass square root)
                if (x*x + y*y + z*z <= radius*radius) {
                    // add the number of points at the coordinate to count
                    count += grid[index];
                }
            }
        }
    }

    // return the proportion of particles in the grid that are within the sphere of rn radius from the origin
    return (double) count / total;
}

//use this function to print results
void print_result(int *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++)
    {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}

//TODO (DONE)
//Finish the following function
//See the assignment decription on Piazza for more details
void diffusion(int n, int m)
{
    // size of one dimension
    int size = 2 * n + 1;

    // coordinates grid
    int *grid = (int*) calloc(size * size * size, sizeof(int));

    // simulate m particles
    for (int i = 0; i < m; i++) {
        one_particle(grid, n);
    }
    
    // print results
    print_result(grid, n);

    // deallocate coordinates grid
    free(grid);
}

int main(int argc, char *argv[])
{
	
	if(argc != 3)
	{
		printf("Usage: %s n m\n", argv[0]);
		return 0; 
	}
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	assert(n >= 1 && n <=50);
	assert(m >= 1 && m <= 1000000);
	srand(12345);
	diffusion(n, m);
	return 0;
}