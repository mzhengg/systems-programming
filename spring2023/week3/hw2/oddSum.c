#include <stdio.h>
#include <stdlib.h>

int oddSumHelp(int count, int bound, int value)
{
    // maxed out number of odd values to sum to value
    // now, check if value is equal to 0
    // if YES, then the current solution is VALID (because we have found 12 odd positive integers that sum to value): return 1 so that line 37 will also return 1 and end the algorithm
    // if NO, then the current solution is INVALID (because the 12 odd positive integers don't sum to value): return 0 so that function can continue exploring smaller odd integers using line 49 in the hopes a perfect odd integer will be found
    if (count == 0) {
        if (value == 0) {
            return 1; // YES
        }
        else {
            return 0;
        }
    }

    // if bound < 1, then we've gone past the last positive odd integer (1)
    // thus, if this is true, then there are no more valid positive odd integers to use: return 0
    if (bound < 1) {
        return 0;
    }

    // if value < 1, then the last odd number was too big (result in a sum more than value)
    // thus, if this is true, then this bound, or odd, value is not valid: return 0
    if (value < 1) {
        return 0;
    }

    // debugging lines:
    // printf("count: %d\n", count);
    // printf("bound: %d\n", bound);
    // printf("value: %d\n", value);


    // PRIMARY LOGIC:
    // recursively call oddSumHelp on the odd values from the upper bound UNTIL the sum of those values surpasses value
    // ex. ./oddSum 12 50 200
    // NOTE: In oddSum, if bound is even, then it will start as the last closest odd (ex. bound = 50 -> 49)
    // Then, this recurison will yield the bound values, or odd values, of 49, 47, 45, 43, and 41
    // each time the recursion will decrement the value by that bound value (so, 200-49-47-45-43-41=-25)
    // 41 causes the value to be < 1, so line 20 in this function will return 0 and make this if clause "false" and not print the number that made value < 0 (which is 41)
    // this will happen to every odd value passed into here, and each time, the count will be decremented by 1 because if it works, it will be counted towards the total number of odd numbers used for the oddSum.
    if (oddSumHelp(count - 1, bound - 2, value - bound)) {
        printf("%d ", bound);
        return 1;
    }

    // EXPLORATORY LOGIC:
    // recursively call oddSumHelp on the odd values from the upper bound ALL THE WAY until 1
    // ex. ./oddSum 12 50 200
    // will explore values from 49, ..., 1
    // this line ensures that every odd value < bound will be explored
    // those bound, or odd, values will then enter line 36 to determine if its positive odd integer paritions can contribute to the overall solution
    return oddSumHelp(count, bound - 2, value);
}

//Do not change the code below
void oddSum(int count, int bound, int value)
{
    if(value <= 0 || count <= 0 || bound <= 0) return;
    
    if(bound % 2 == 0) bound -= 1;

    if(!oddSumHelp(count, bound, value)) printf("No solutions.\n");
	else printf("\n");
}

int main(int argc, char *argv[])
{
	if(argc != 4) return -1;

	int count = atoi(argv[1]);
	int bound = atoi(argv[2]);
	int value = atoi(argv[3]);

	// oddSum(12,30,200);
	// oddSum(10,20,100);
	// oddSum(20,20,200);
	oddSum(count, bound, value);
	return 0;
}