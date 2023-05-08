#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[])
{
	int n;
	if(argc < 2) n = 1000;
	else n = atoi(argv[1]);

	assert(n <= 10000);
	int i;
	int acc[16] = {0}; 
	for(i = 0; i< n; i++)
	{
		//add a few lines of code below
        int val = i * i;
        // printf("0x%x\n", val);
	}
	//Do not change the rest of the code	
	for(i=0; i<16; i++)
	{
		printf("%x: %d\n", i, acc[i]);
	}
	return 0;
}