// LATORRE, JEO D
// BSCS 2C :: CASE STUDY 1

#include <iostream>
#include <array>				// array<type, N>
#include <set>					// set();
using namespace std;

// function prototypes
array<int,2> CASE1_check_DUP (int DATA[], int DATA_num);
array<int,2> CASE2_check_DUP (int DATA[], int DATA_num);

int main(void)
{
	//variable declaration and initialization
	int LIST[] = {5, 5, 6, 9, 8, -1};
		//   LIST[]  ->  arrray storage for data 

	int set = sizeof(LIST) / sizeof(LIST[0]);							// formula to identify the number of data stored in the ARRAY
																		// 'sizeof(LIST)' -> It measures the memory occupied by the entire array.	
																		// 'sizeof(LIST[0])' Calculates the size of one element within the array.										
																		// 'sizeof(LIST) / sizeof(LIST[0])' Determines how many elements (of the same type as LIST[0]) are present in the array LIST
	cout << "LIST: ";													// Prints label
	
	for(int i = 0; i < set; i++)										// loop to enable printing the Data stored in array
		if(i != (set-1))												// if i does not represent the last index of the element of array
			cout << LIST[i] << ", ";									
		else															// if i is the last index of the the last element of array
			cout << LIST[i] << "\n";
	
	array<int, 2> CHECKED1 = CASE1_check_DUP (LIST, set);				// variable initialization 'CHECKED1' to be stored by the data returned from function call one CASE1
	array<int, 2> CHECKED2 = CASE2_check_DUP (LIST, set);				// variable initialization 'CHECKED2' to be stored by the data returned from function call one CASE2

	if(CHECKED1[0] == 0)												// if the first data on array CHECKED1 is 0 meaning no duplicate
		cout << "\nCASE1 NO VALUE REPEATED! ";
	else																// if the first data on array CHECKED1 is 1 prints the first duplicte value
		cout << "\nCASE1 First duplicate value: " << CHECKED1[1];		// prints the second data on CHECKED1 array

	if(CHECKED2[0] == 0)												// if the first data on array CHECKED2 is 0 meaning no duplicate
		cout << "\nCASE2 NO VALUE REPEATED! ";
	else																// if the first data on array CHECKED2 is 1 prints the first duplicte value
		cout << "\nCASE2 First duplicate value: " << CHECKED2[1];		// prints the second data on CHECKED1 array

	return 0;															// terminates program
}

// first case to check the first duplicate data 
// has time complexity of Big O(n^2)
//     BEST -> O(1)
//    WORST -> O(n^2)
// AVEARAGE -> O(n^2)
array<int,2> CASE1_check_DUP (int DATA[], int DATA_num)			// parameter gets the array and and the number of data stored
{
	for(int i = 1; i < DATA_num; i++)							// loop that increments until it reach the number of data stored in the array
		for(int j = 0; j < i; j++)								// loop that increments until it reach the value of counter in first loop
			if(DATA[i] == DATA[j])								// enables to compare the first upto last data on array into each and every data on array
				return {1, DATA[i]};							// if data matched meaning duplicate then returns to main function

	return {0, 0};												// returns to main if no values duplicate
}

// first case to check the first duplicate data 
// has time complexity of Big O(n (log n))
//     BEST -> O(1)
//    WORST -> O(n (log n))
// AVEARAGE -> O(n (log n))
array<int,2> CASE2_check_DUP (int DATA[], int DATA_num)			// parameter gets the array and and the number of data stored
{
	set<int> seen;												// creates a hash using set follows 

    for(int i = 0; i < DATA_num; i++)							// Loop that iterates until it reach the number of data stored in array
    {
        if(seen.find(DATA[i]) != seen.end())					// finds the data if it is stored in the set
            return {1, DATA[i]};								// if not stored meaning a duplicate then returns to main function
        seen.insert(DATA[i]);									// if not found in the set meaning its a unique value and store it in set
    }

    return {0, 0};												// returns to main if no value repeated
}