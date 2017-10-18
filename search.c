#include <stdio.h>

//Scans 10 sorted numbers from the user (ensure no certain number is repeated)
//Return the index which is equal to A[i]

//The exhaustive method
int linearSearch( int A[ ] ){

	//search for i == A[i]
	for (int j = 0; j < 9; j++){
		if (A[j] == j){
			return j;
		}
	}
	return -1;
}

//The better, "more efficient" method
//Note "high" must be no. of items - 1 (e.g. instead of 10, accept 9)
int binarySearch( int A[ ], size_t low, size_t high ){
	int middle = 0;

	while ( low < high ){
		middle = (low + high) / 2;

		if ( A[middle] == middle ){
			return middle;
		} else if ( A[middle] > middle ){
			high = middle;
		} else{
			low = middle + 1;
		}
	}
	
	return -1;

}

int main( ){
	int A[10];

	//some test cases
	// int AB[10] = {-10, -3, -1, 3, 7, 9, 10, 11, 12, 14};
	// int CD[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	// int ED[10] = { -20, -6, -3, 0, 2, 3, 6, 8, 9, 10 };
	// int FG[10] = { 8, 10, 17, 18, 20, 21, 30, 31, 90, 100};
	
	//scans 10 sorted numbers from the user
	printf("%s\n", "Enter 10 sorted numbers: ");
	for (int i = 0; i < 10; i++){
		scanf("%d", &A[i]);
	}

	printf("%d\n", linearSearch( A ) );
	printf("%d\n", binarySearch( A, 0, 9 ));
	return 0;
}
