/*
                                                                        CS111-Design and Analysis of Algorithms
                                                                                       2nd  Semester, 2023-2024
                                                                                          Programming Project 1                                                                  
    -----------------------------------------------------------------------------------------------------------
                                    Developeer : Jeo D. Latorre
    -----------------------------------------------------------------------------------------------------------

    >> Perform an empirical analysis on the different sorting algorithms to sort N randomly generated integers
            :: Selection Sort
            :: Bubble Sort
            :: Insertion Sort 
            :: Mergesort
            :: Quicksort
            :: Heapsort
            :: Radix sort 

    >> The project is consists of the following:
            • basic implementation program that sorts the integers using the six algorithms
            • analyzing what you see in terms of performance by measuring the runtime of each algorithm

    -----------------------------------------------------------------------------------------------------------
    Desired Program Behavior:
        [1] User is prompted to enter a value for N (for number of integers) as input

        [2] The program generates N integers which are either
                (a) all integers are picked randomly with a uniform distribution from the range [0,MAXRANGE] 
                        :: (use MAXRANGE of unsigned long int) or
                (b) sorted in the increasing order
                        :: the program should ask an input X (a positive number) from the user 
                        :: set the first element of the array to element to X
                        :: the second 2X,  the third element to 3 X and so on 

        [3] The program sorts these N integers using the different algorithms 
                :: outputs a file with original and sorted values

        [4] The program should also output the computation time T(N) for sorting N integers
                :: Only the computation time and not the time spent 
                        --> interacting with user
                        --> generating the integers
                        --> writing into a file

        [5] programming language for implementation
                :: C 
                :: C++ 

        [6] The different algorithms can be implemented as separate functions
                :: passing the generated array as parameters to these functions

        [7] To calculate time taken by a process or set of operations
                :: use clock() function under time.h
                :: subtract the values, and then divide by CLOCKS_PER_SEC to get processor time

*/

#include <iostream>
#include <string>	    // getline(), .length(), stoi(), .erase(), to_string
#include <random>       // random_device, mt1993(), uniform_int_distribution
#include <limits>       // numeric_limits<>::max()
#include <time.h>       // clock_t, clock(), CLOCKS_PER_SEC
#include <algorithm>    // remove_if(), all_of()	
#include <sstream>		// istringstream()
#include <cctype>		// isdigit(), ::isspace, ::isdigit
#include <vector>       // vector<>, vector<vector<>>, .empty(), .size()
#include <iterator>     // begin(), end()
#include <fstream>
using namespace std;

// aliasing for easy modification of code
using type_class = unsigned long int;

//FUNTION DECLARATION [unsigned long int return type]
type_class ASK(int index);                                                                                      // Function to Ask user inputs and returns once it is valid
type_class getMax(vector<type_class>& array, type_class n);

//FUNTION DECLARATION [long long int return type]
long long Partition(vector<long long>& array, long long start, long long n);                                    // Function to identify the partition value

//FUNTION DECLARATION [int return type]
int heap_sort(vector<type_class>& array, type_class n);                                                         // Heap Sort Function
int radix_sort(vector<type_class>& array, type_class n);
int bubble_sort(vector<type_class>& array, type_class n);                                                       // Bubble Sort Function
int selection_sort(vector<type_class>& array, type_class n);                                                    // Selection Sort Function
int insertion_sort(vector<type_class>& array, type_class n);                                                    // Insertion Sort Function
int quick_sort(vector<long long>& array, long long start, long long n);                                         // Quick Sort Function
int merge_sort(vector<type_class>& array, type_class start, type_class n);                                      // Merge Sort Function
int merge( vector<type_class>& array, type_class start, type_class mid, type_class start_2, type_class n);      // Function that merges and sort the array

//FUNTION DECLARATION [void return type]
void print (int part, int index);                                                                               // Function to Print specific repeated lines in entire code
void swap2(long long *curent_root, long long*end);                                                              // Funtion to swap specific element values of array with 'long long' type
void swap (type_class *curent_root, type_class *end);                                                           // Function to swap specific element values of array with 'unsigned long int' type
void heapify (vector<type_class>& array, type_class n, type_class start);                                       // Function to balance the heapsort
void countingSort(vector<type_class>& array, type_class n, long long place);
void perform_objective(type_class N, int type, vector<vector<double>>& averages, int &length);                  // Function that generates array [sorted and random ] and handles call for computing runtime
void print_ave_runtime( vector<vector<double>> sortedAverages, vector<vector<double>> randomAverages, 
                        vector<vector<type_class>> NArray, int length 
                      );                                                                                        // Function to print average time in table form
void runtimes_to_table( vector<vector<double>> time_per_run, vector<double> runAverages, type_class N, int type);
void OUTPUT_to_FILE(    int run, int type, int sort_type, string sort_func_name,
                        vector<type_class>& Orig_array, vector<type_class>& sort_array1, 
                        vector<long long>& sort_array2, string Filename
                   );

//FUNTION DECLARATION [double return type]
double timeAndSort( int (sortFunction1)(vector<type_class>& array, type_class), 
                    int (sortFunction2)(vector<type_class>& array, type_class, type_class), 
                    int (sortFunction3)(vector<long long>& array, long long, long long),
                    vector<type_class>& rand_array, vector<long long>& rand_array2, 
                    type_class N, long long N_2, type_class begin, long long begin_2, 
                    const string& sortName, int type, int qs  
                  );                                                                                            // Function that helps compute the time of sorting function

int main(void)
{
    // VARIABLE DECLARATION and INITIALIZAATION
    int counter = 0, answer, array_type, length = 14;
        //                       answer     ->  storage of answer of user
        //                  counter = 0     ->  flag variable to enable skipping in parts of code 0 -> read, else -> skip
    type_class N;
        //                            N     ->  storage for Number of integers on array
    string UserInput;
        //                    UserInput     ->  storage for user input to ensure valid input
    vector<vector<double>> sortedAverages;
    vector<vector<double>> randomAverages;
    vector<vector<type_class>> NArray(2);
        //                         NArray   ->  vector matrix storage of different N values
        // sortedAverages, randomAverages   ->  vector matices for storage of the averages of each sorting

    // outer loop enables repetition of code
    while (true)
    {   
        // flag 'counter' cheking to for skipping or executing 
        if(counter == 0) 
        {   
            print(1, 0);                                                                                // Function call, prints header
            print(2, 1);                                                                                // Function call, prints instruction (first choice)
            getline(cin, UserInput);                                                                    // store the userinput to variable storage 'UserInput'
                                                                                                            // getline  -> reads input from the standard input stream until it reads newline character '\n'
            counter--;                                                                                  // update counter flag variable                          
        }

        // loop that reapeats until 'UserInput' is valid input
        while(UserInput.length() != 1 || (UserInput != "1" && UserInput != "2"))                        // repeats if user inputs' length is not 1 and the value is niether 1 nor 2
        {
            system("cls");                                                                              // Function to clear terminal screen for Windows                     
            cout << "\033[2J\033[1;1H";                                                                 // Function to clear terminal screen for Linux
            print(1, 0);                                                                                // Function call, prints header
            print(8, 0);                                                                                // Function call, prints invalid message
            print(2, 1);                                                                                // Function call, prints instruction (first choice)
            getline(cin, UserInput);                                                                    // store the userinput to variable storage 'UserInput'
                                                                                                            // getline  -> reads input from the standard input stream until it reads newline character '\n'
        }
        
        answer = stoi(UserInput);                                                                       // converts validated string 'UserInput' to integer
        counter++;                                                                                      // update counter flag variable 

        if(counter == 0 && answer != 2) 
        {   
            print(2, 0);                                                                                // Function call, prints instruction (first choice)
            getline(cin, UserInput);                                                                    // store the userinput to variable storage 'UserInput'
                                                                                                            // getline  -> reads input from the standard input stream until it reads newline character '\n'
        }

        // loop that reapeats until 'UserInput' is valid input
        while(UserInput.length() != 1 || (UserInput != "1" && UserInput != "2"))                        // repeats if user inputs' length is not 1 and the value is niether 1 nor 2
        {
            system("cls");                                                                              // Function to clear terminal screen for Windows                     
            cout << "\033[2J\033[1;1H";                                                                 // Function to clear terminal screen for Linux
            print(1, 0);                                                                                // Function call, prints header
            print(8, 0);                                                                                // Function call, prints invalid message
            print(2, 0);                                                                                // Function call, prints instruction (first choice)
            getline(cin, UserInput);                                                                    // store the userinput to variable storage 'UserInput'
                                                                                                            // getline  -> reads input from the standard input stream until it reads newline character '\n'
        }
        
        array_type = stoi(UserInput);                                                                   // converts validated string 'UserInput' to integer

        // Checks value of answer and perform unique scenarios
        switch (answer)
        {
             // if value of answer is 1 == 'Exit'
             case 2: if (!NArray.empty())                                                               // checks whether the program run atleast once 
                        print_ave_runtime(sortedAverages,randomAverages, NArray, length);               // if the program runs atleaset once, FUNCTION CALL, to print the average time of each sorting for unique values of N both Random and Sorted ones
                        
                     print(0, 0);                                                                       // Function call, prints footer
                     return 0;                                                                          // Terminates the program
            
            // if value of answer is 2 == 'Start' 
            default: N = ASK(0);                                                                        // Function call to ask value of N from user returns only the valid value
                        
                     if(array_type == 1)
                     {
                        NArray[0].push_back(N);                                                         // Append current value of 'N' to the end first inner vector array
                        perform_objective(N, 2, sortedAverages, length);                                // Function call, to generate Sorted array
                     }
                     else
                     {
                        NArray[1].push_back(N);                                                         // Append current value of 'N' to the end second inner vector array
                        perform_objective(N, 1, randomAverages, length);                                // Function call, to generate Random array
                     }

                     print(9, 0);                                                                       // Function call, ask user if want to continue or not
                     getline(cin, UserInput);                                                           // store the userinput to variable storage 'UserInput'
                                                                                                            // getline  -> reads input from the standard input stream until it reads newline character '\n'

                     // loop that reapeats until 'UserInput' is valid input
                     while(UserInput.length() != 1 || (UserInput != "y" && UserInput != "n"))          // repeats if user inputs' length is not 1 and the value is niether y nor n
                     {
                        system("cls");                                                                 // Function to clear terminal screen for Windows 
                        cout << "\033[2J\033[1;1H";                                                    // Function to clear terminal screen for Linux
                        print(1, 0);                                                                   // Function call, prints header
                        print(8, 0);                                                                   // Function call, prints invalid message
                        print(9, 0);                                                                   // Function call, ask user if want to continue or not
                        getline(cin, UserInput);                                                       // store the userinput to variable storage 'UserInput'
                                                                                                            // getline  -> reads input from the standard input stream until it reads newline character '\n'                            
                     }

                     // if user wants to continue
                     if(UserInput == "y")    
                     {   
                        UserInput = "1";                                                               // Re-initianilization of 'UserInput' to 1 to enable repetition
                        system("cls");                                                                 // Function to clear terminal screen for Windows 
                        cout << "\033[2J\033[1;1H";                                                    // Function to clear terminal screen for Linux
                        print(1, 0);                                                                   // Function call, prints header
                        counter = -1;                                                                  // Re-initianilization of 'counter' to -1 to enable skipping specific part 
                     }
                     // if user wants to exit the program
                     else 
                     {   
                        UserInput = "2";                                                               // Re-initianilization of 'UserInput' to 2 to exit the program                                                               
                        counter = 1;                                                                   // Re-initianilization of 'counter' to 1 to enable skipping specific part 
                     }                                                                      
        }
    }
}

// FUNCTION DEFINITION

// Function that generates array [sorted and random ] and handles call for computing runtime
void perform_objective(type_class N, int type, vector<vector<double>>& averages, int &length)
{
    // VARIABLE DECLARATION and INITIALIZAATION
    vector<vector<double>> time_per_run(7);
    vector<double> runAverages;
    int rand_generated;
    string UserInput;    
    type_class X;
        //                           X  ->  variable storage of first element of array from user  
        //                 runAverages  ->  vector array storage of average runs time of each sorting algorithm
        //                   UserInput  ->  storage for user input to ensure valid input                    
        //              rand_generated  ->  variable storage of the generated random number

    const type_class MAXRANGE = numeric_limits<type_class>::max();
        //                   MAXRANGE   ->  variable storage 
        //             numeric_limits   ->  class name from the <limits> header
        // numeric_limits<type_class>   ->  returns the maximum value representable by the specified type
    random_device rand_seed;
        //                 rand_seed    ->  holds instance of random_device
        //             random_device    ->  helps create seed for number generator
    auto rd_gen = mt19937(rand_seed());
        //                     rd gen   ->  variable storage of generated number
        //                  mt19937()   ->  Pseudo-random number generator (Mersenne Twister engine)
        //       mt19937(rand_seed())   ->  seeds to ensures different sequences of random numbers

    uniform_int_distribution<type_class> rand_num(0, MAXRANGE);
        //                    <int>     ->   Specifies the  type of values to be distributed
        //         rand1(), rand2()     ->   Variable name representing instances of uniform_int_distribution
        //      (1,2),(0, MAXRANGE)     ->   defining the range of distribution
        // uniform_int_distribution     ->   Defines the distribution (uniform)

    double time, s_sort_ave_time = 0, b_sort_ave_time = 0, i_sort_ave_time = 0,
                 m_sort_ave_time = 0, q_sort_ave_time = 0, h_sort_ave_time = 0, r_sort_ave_time = 0;
        //                       time   ->  variable storage of computed cpu time of the sorting function
        //        s_sort_ave_time = 0   ->  variable storage for the sum of 'time' variable for 5 runs of Selection sort
        //        b_sort_ave_time = 0   ->  variable storage for the sum of 'time' variable for 5 runs of Bubble sort
        //        i_sort_ave_time = 0   ->  variable storage for the sum of 'time' variable for 5 runs of Insertion sort
        //        m_sort_ave_time = 0   ->  variable storage for the sum of 'time' variable for 5 runs of Merge sort
        //        q_sort_ave_time = 0   ->  variable storage for the sum of 'time' variable for 5 runs of Quick sort
        //        h_sort_ave_time = 0   ->  variable storage for the sum of 'time' variable for 5 runs of Heap sort

    // Loop that repeats 5 times to generate array
    for(int run = 0; run < 5; run++)
    {      
        // VARIABLE DECLARATION
        long long N_2 = N;
        //                        N_2  ->   Variable storage of copied 'N'for Quicksort function
        vector<type_class> rand_array(N);
        vector<type_class> pass_rand_array(N);
        vector<long long> QS_rand_array(N_2);
        //                 rand_array  ->   vector array with size 'N' storage of generated random numbers
        //            pass_rand_array  ->   vector array with size 'N' storage of copied values of 'rand_array'
        //              QS_rand_array  ->   unique vector array with size 'N_2' storage for Quick Sort function

        // if Random Array
        if(type == 1)
        {    
        	print(5, run+1);                                                                                // Function call, prints prompt for Random array generation

            // loops 'N' times to create values for Random Array 
            for(type_class i = 0; i < N; i++)
            {    
                rand_generated = rand_num(rd_gen);                                                        // Generates random values base on range and store to 'rand_generated'
                rand_array[i] = rand_generated;                                                           // assign 'rand_generated' to vector array rand_arrays' i-th term
                QS_rand_array[i] = rand_array[i];                                                         // copies the values of 'rand_array' to 'QS_rand_array' for Quick sort function
            }
        }
        // if Sorted Array
        else
        {   
            X = ASK(run+1);                                                                               // Function call to ask value of 'X' from user, returns only the valid value

            rand_array[0] = X;                                                                            // sets the first element of 'rand_array' to X
            QS_rand_array[0] = rand_array[0];                                                             // copies the values of 'rand_array' to 'QS_rand_array' for Quick sort function

            // loops 'N' to generate value for Sorted Array
            for(type_class i = 1; i < N; i++)                                                                    
            {
                rand_array[i] = (i+1)*X;                                                                  // sets the consecutive element of 'rand_array' to X multiplied to 1 plus the i-th term
                QS_rand_array[i] = rand_array[i];                                                         // copies the values of 'rand_array' to 'QS_rand_array' for Quick sort function
            }
        }

        pass_rand_array = rand_array;                                                                     // copies the value of 'rand_array' to 'pass_rand_array'
        time = timeAndSort( selection_sort, nullptr, nullptr, pass_rand_array, 
                            QS_rand_array, N, 0, 0, 0, "Selection sort", 1,0);                            // Function call, to compute and handle the Selection sorting
        s_sort_ave_time += time;                                                                          // takes the summation of time stores in 's_sort_ave_time'

        time_per_run[0].push_back(time);                                                                  // Append current value of 'time' to the end first inner vector array
        OUTPUT_to_FILE( run, type, 1, "SelectionSort", rand_array, 
                        pass_rand_array, QS_rand_array, "Selectionsort.txt");

       pass_rand_array = rand_array;                                                                     // copies the value of 'rand_array' to 'pass_rand_array'   
        time = timeAndSort( bubble_sort, nullptr, nullptr, pass_rand_array, 
                            QS_rand_array, N, 0, 0, 0, "Bubblesort", 1,0);                                // Function call, to compute and handle the Bubble sorting
        b_sort_ave_time += time;                                                                          // takes the summation of time stores in 'b_sort_ave_time' 

        time_per_run[1].push_back(time);                                                                  // Append current value of 's_sort_ave_time' to the end second inner vector array

        OUTPUT_to_FILE( run, type, 1, "BubbleSort", rand_array, 
                        pass_rand_array, QS_rand_array, "Bubblesort.txt");

        pass_rand_array = rand_array;                                                                     // copies the value of 'rand_array' to 'pass_rand_array'
        time = timeAndSort( insertion_sort, nullptr, nullptr, pass_rand_array, 
                            QS_rand_array, N, 0, 0, 0, "Insertion sort", 1,0);                            // Function call, to compute and handle the Insertion sorting
        i_sort_ave_time += time;                                                                          // takes the summation of time stores in 'i_sort_ave_time'

        time_per_run[2].push_back(time);                                                                  // Append current value of 's_sort_ave_time' to the end third inner vector array

       OUTPUT_to_FILE( run, type, 1, "InsertionSort", rand_array, pass_rand_array,
                        QS_rand_array, "Insertionsort.txt");
 
        pass_rand_array = rand_array;                                                                     // copies the value of 'rand_array' to 'pass_rand_array'
        time = timeAndSort( nullptr, merge_sort, nullptr, pass_rand_array, 
                            QS_rand_array, N-1, 0, 0, 0, "Merge sort", 2,0);                              // Function call, to compute and handle the Merge sorting
        m_sort_ave_time += time;                                                                          // takes the summation of time stores in 'm_sort_ave_time'

        time_per_run[3].push_back(time);                                                                  // Append current value of 's_sort_ave_time' to the end forth inner vector array

        OUTPUT_to_FILE( run, type, 1, "Merge Sort", rand_array, pass_rand_array, 
                        QS_rand_array, "Mergesort.txt");

        time = timeAndSort( nullptr, nullptr, quick_sort, pass_rand_array, 
                            QS_rand_array, 0, (N_2)-1, 0, 0, "Quick sort", 3,type);                       // Function call, to compute and handle the Quick sorting
        q_sort_ave_time += time;                                                                          // takes the summation of time stores in 'q_sort_ave_time'

        time_per_run[4].push_back(time);                                                                  // Append current value of 's_sort_ave_time' to the end fifth inner vector array
    
        OUTPUT_to_FILE( run, type, 0, "QuickSort",rand_array, pass_rand_array, 
                        QS_rand_array, "Quicksort.txt");

        pass_rand_array = rand_array;                                                                     // copies the value of 'rand_array' to 'pass_rand_array'
        time = timeAndSort( heap_sort, nullptr, nullptr, pass_rand_array, 
                            QS_rand_array, N, 0, 0, 0, "Heap sort", 1,0);                                 // Function call, to compute and handle the Heap sorting
        h_sort_ave_time += time;                                                                          // takes the summation of time stores in 'h_sort_ave_time'

        time_per_run[5].push_back(time);                                                                  // Append current value of 's_sort_ave_time' to the end sixth inner vector array

        OUTPUT_to_FILE( run, type, 1, "HeapSort",rand_array, pass_rand_array, 
                        QS_rand_array, "Heapsort.txt");

        pass_rand_array = rand_array;                                                                     // copies the value of 'rand_array' to 'pass_rand_array'
        time = timeAndSort( radix_sort, nullptr, nullptr, pass_rand_array, 
                            QS_rand_array, N, 0, 0, 0, "Radix sort", 1,0);                                // Function call, to compute and handle the Heap sorting
        r_sort_ave_time += time;  

        time_per_run[6].push_back(time);                                                                  // Append current value of 's_sort_ave_time' to the end seventh inner vector array
        
        OUTPUT_to_FILE( run, type, 1, "RadixSort",rand_array, pass_rand_array, 
                       QS_rand_array, "Radixsort.txt");   
    }

    // Takes the averages after 5 runs of accumulated summation of run time of each sorting
    s_sort_ave_time = s_sort_ave_time / 5;                                                                  // average of 5 runtime Selection sort 
    b_sort_ave_time = b_sort_ave_time / 5;                                                                  // average of 5 runtime Bubble sort 
    i_sort_ave_time = i_sort_ave_time / 5;                                                                  // average of 5 runtime Insertion sort 
    m_sort_ave_time = m_sort_ave_time / 5;                                                                  // average of 5 runtime Merge sort 
    q_sort_ave_time = q_sort_ave_time / 5;                                                                  // average of 5 runtime Quick sort 
    h_sort_ave_time = h_sort_ave_time / 5;                                                                  // average of 5 runtime Heap sort 
    r_sort_ave_time = r_sort_ave_time / 5;                                                                  // average of 5 runtime Heap sort 

    // Initializes the vector array 'runAverages' with the computed average times in 5 runs of each sorting
    runAverages = { s_sort_ave_time, b_sort_ave_time, i_sort_ave_time,
                    m_sort_ave_time, q_sort_ave_time, h_sort_ave_time, r_sort_ave_time
                  };

    
    runtimes_to_table(time_per_run, runAverages, N, type);

    // Appends the values of runAverages to the end of vector array averages
    averages.push_back(runAverages);

    // takes the LONGEST LENGTH and store to 'length' to update the current length value in main function
    if (to_string(N).length() > length) 
        length = to_string(N).length();                                                                   // takes the length of 'N'
    if (to_string(s_sort_ave_time).length() > length) 
        length = to_string(s_sort_ave_time).length();                                                     // takes the length of average runtime of Selection sort
    if (to_string(b_sort_ave_time).length() > length) 
        length = to_string(b_sort_ave_time).length();                                                     // takes the length of average runtime of Bubble sort
    if (to_string(i_sort_ave_time).length() > length) 
        length = to_string(i_sort_ave_time).length();                                                     // takes the length of average runtime of Insertion sort
    if (to_string(m_sort_ave_time).length() > length) 
        length = to_string(m_sort_ave_time).length();                                                     // takes the length of average runtime of Merge sort
    if (to_string(q_sort_ave_time).length() > length) 
        length = to_string(q_sort_ave_time).length();                                                     // takes the length of average runtime of Quick sort
    if (to_string(h_sort_ave_time).length() > length) 
        length = to_string(h_sort_ave_time).length();                                                     // takes the length of average runtime of Heap sort
    if (to_string(r_sort_ave_time).length() > length) 
        length = to_string(r_sort_ave_time).length();                                                     // takes the length of average runtime of Quick sort
}

// Selection Sort Function
int selection_sort(vector<type_class>& array, type_class n)
{
    for(type_class i = 0; i < n-1; i++)
    {
        type_class position = i;

        for(type_class j = i + 1; j < n; j++)
            if(array[position] > array[j])
                position = j;
        
        if(position != i) 
            swap(array[i], array[position]);
    }

    return 1;
}

// Bubble Sort Function
int bubble_sort(vector<type_class>& array, type_class n)
{
    type_class Swap = 0;

    for(type_class i = 1; i < n; i++)
    {    
        for(type_class j = 0; j < (n-i) ; j++)
            if(array[j] > array[j+1])
            {
                swap(array[j], array[j+1]);
                Swap++;
            }

        if(Swap == 0)
            break;
    }

    return 1;
}

// Insertion Sort Function
int insertion_sort( vector<type_class>& array, type_class n)
{
    for (type_class i = 1; i < n; i++)
    {
        long long int key = array[i], j = i - 1;

        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }

        array[j + 1] = key;
    }

    return 1;
}

// Merge Sort Function
int merge_sort( vector<type_class>& array,  type_class start, type_class n)
{
    if(start < n)
    {
        type_class mid = (start + n) / 2;
        merge_sort(array, start, mid);                     //left recursion
        merge_sort(array, mid+1, n);                       //right recursion
        merge(array, start, mid, mid+1, n);                //merging of two sorted sub-arrays
    }

    return 1;
}

// Heap Sort Function
int heap_sort( vector<type_class>& array, type_class n) 
{
    // If array has 1 elements, it's already sorted
    if (n <= 1)                                             
        return 1;

    // Build a max heap
    for (long long int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    // One by one extract an element from heap
    for (long long int i = n - 1; i > 0; i--) 
    {
        // Move current root to end
        swap(&array[0], &array[i]);

        // call max heapify on the reduced heap
        heapify(array, i, 0);
    }

    return 1;
}

// Quick Sort Function
int quick_sort( vector<long long>& array, long long start, long long n) 
{
    if(start < n) 
    {
        long long modified_pivot = Partition(array, start, n);
        quick_sort(array, start, modified_pivot-1);           // left partition
        quick_sort(array, modified_pivot + 1, n);             // right partition
    }

    return 1;
}

// Radix Sort Function
int radix_sort(vector<type_class>& array, type_class n) 
{
    // Get maximum element
    type_class max = getMax(array, n);

    // Apply counting sort to sort elements based on place value.
    for (long long place = 1; max / place > 0; place *= 10)
        countingSort(array, n, place);

    return 1;
}

// Function that merges and sort the array
int merge(  vector<type_class>& array, type_class start, type_class mid, type_class start_2, type_class n)
{
    vector<type_class> temp(n+1);                       //array used for merging
    type_class i = start, j = start_2, k = 0;
        // i = beginning of the first list
        // J = beginning of the second list

    while(i <= mid && j <= n)                           //while elements in both lists
        if(array[i] < array[j])
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];

    while(i <= mid)                                     //copy remaining elements of the first list
        temp[k++] =array [i++];

    while(j <= n)                                       //copy remaining elements of the second list
        temp[k++] =array[j++];
    
    //Transfer elements from temp[] back to array[]
    for(i = start, j = 0; i <= n; i++, j++)
        array[i] = temp[j];

    return 1;
}

// Function to balance the heapsort
void heapify( vector<type_class>& array, type_class n, type_class start) 
{
    type_class largest = start;                            // Initialize largest as root
    type_class left = 2 * start + 1;                       
    type_class right = 2 * start + 1;                      

    // If left child is larger than root
    if (left < n && array[left] > array[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && array[right] > array[largest])
        largest = right;

    // If largest is not root
    if (largest != start) 
    {
        swap(&array[start], &array[largest]);
        heapify(array, n, largest);
    }
}

// Function to identify the partition value
long long Partition(vector<long long>& array,  long long start, long long n) 
{
    // Find the median of first, middle, and last elements
    long long pivot = array[n];
    long long i = start - 1;

    for(long long j = start; j < n; j++)
        if(array[j] < pivot)
        {
            i++;
            swap2(&array[i], &array[j]);
        }

    swap2(&array[i+1], &array[n]);

    return i+1;
}

// Function to get the largest element from an array
type_class getMax(vector<type_class>& array, type_class n) 
{
    type_class max = array[0];
    
    for (long long i = 1; i < n; i++)
        if (array[i] > max)
            max = array[i];

    return max;
}

void countingSort(  vector<type_class>& array, type_class n, long long place ) 
{
    const type_class max = 10;
    type_class output[n];
    type_class count[max];

    for (long long i = 0; i < max; ++i)
        count[i] = 0;

    // Calculate count of elements
    for (long long i = 0; i < n; i++)
        if(place != 0)
            count[(array[i] / place) % 10]++;

    // Calculate cumulative count
    for (long long i = 1; i < max; i++)
        count[i] += count[i - 1];

    // Place the elements in sorted order
    for (long long i = n - 1; i >= 0; i--) 
    {
        output[count[(array[i] / place) % 10] - 1] = array[i];
        count[(array[i] / place) % 10]--;
    }

    for (long long i = 0; i < n; i++)
        array[i] = output[i];
}

// Funtion to swap specific element values of array with 'unsigned long int' type
void swap(type_class *curent_root, type_class *end) 
{
    type_class temp = *curent_root;
       *curent_root = *end;
               *end = temp;
}

// Funtion to swap specific element values of array with 'long long int' type
void swap2(long long *curent_root, long long*end) 
{
    long long temp = *curent_root;
       *curent_root = *end;
               *end = temp;
}

// Function that helps compute the time of sorting function
double timeAndSort( int (sortFunction1)(vector<type_class>& array, type_class), 
                    int (sortFunction2)(vector<type_class>& array, type_class, type_class), 
                    int (sortFunction3)(vector<long long>& array, long long, long long),
                    vector<type_class>& rand_array, 
                    vector<long long>& rand_array2, 
                    type_class N, 
                    long long N_2, 
                    type_class begin, 
                    long long begin_2,
                    const string& sortName, 
                    int type, int qs   
                )
{
    // VARIABLE DECLARATION 
    clock_t start, end;
    //       clock_t    ->  data type used to store processor time 
    //         start    ->  storage variable for the start of processor time
    //           end    ->  storage variable for the end of processor time
    double cpu_time_used;
    // cpu_time_used    ->  variable storage of computed runtime of soting function

    // if passed vector array has 2 parameters
    if(type == 1)
    {
        start = clock();                                                                                            // records the starting processor time before the sorting function execution            
        sortFunction1(rand_array, N);                                                                               // Function call, to execute specified sorting function
        end = clock();                                                                                              // records the starting processor time after the sorting function execution
                                                                                                                            // clock()  ->  returns the amount of processor time that the program has used
    }
    // if passed vector array has 3 parameters and 'unsigned long int' type
    else if(type == 2)
    {
        start = clock();                                                                                            // records the starting processor time before the sorting function execution 
        sortFunction2(rand_array, begin, N);                                                                        // Function call, to execute specified sorting function
        end = clock();                                                                                              // records the starting processor time after the sorting function execution
                                                                                                                            // clock()  ->  returns the amount of processor time that the program has used    
    }
    //if passed vector array has 3 parameters and 'long long int' type
    else
        if(N_2 > 10000 && qs == 2)
        {
            start = clock();                                                                                         // records the starting processor time before the sorting function execution 
            sortFunction3(rand_array2, begin, N);                                                                    // Function call, to execute specified sorting function
            end = clock();                                                                                           // records the starting processor time after the sorting function execution
                                                                                                                            // clock()  ->  returns the amount of processor time that the program has used
        }   
        else
        {
            start = clock();                                                                                         // records the starting processor time before the sorting function execution 
            sortFunction3(rand_array2, begin_2, N_2);                                                                // Function call, to execute specified sorting function
            end = clock();                                                                                           // records the starting processor time after the sorting function execution
                                                                                                                            // clock()  ->  returns the amount of processor time that the program has used
        }
        
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;                                                       //  helps to convert the processor time from clock ticks to seconds
                                                                                                                            //  (end - start)   ->  the value of processor time in clock ticks
                                                                                                                            // CLOCKS_PER_SEC   ->  the value of clock ticks per seconds
    return cpu_time_used;                                                                                           //  return the computed cpu time or run time of the sorting function
}

// Function to Ask user inputs and returns once it is valid
type_class ASK(int index)
{
	// VARIABLE DECLARATION and INITIALIZAATION
	unsigned long int toINT;
    string UserInput;
		//       toInt  ->  variable storage when string "UserInput" is converted to int
        // 	 UserInput  ->  variable storage for user input
    
    // Checks value of index and perform unique scenarios
    switch(index)
    {
         // block of code to ask for value of 'N'
         case 0: print(3, 0);                                                                                       // Function call, prints instruction

                 do
                 {
                     getline(cin, UserInput);                                                                       // store the userinput to variable storage 'UserInput'
                                                                                                                        // getline  -> reads input from the standard input stream until it reads newline character '\n'                                                                    

                     UserInput.erase(remove_if(UserInput.begin(), UserInput.end(), ::isspace), UserInput.end());	// helps remove spaces from input
                                                                                                                    // 	     remove_if -> shifts non-white space characters to the left, overwriting the white space characters.
                                                                                                                    // 	 	   isspace -> checks for white spaces
                                                                                                                    // UserInput.end() ->  second argument to indicate the end of the string after the removal operation. 
                     
                     // if UserInput contains only integer and not empty
                     if (!UserInput.empty() && all_of(UserInput.begin(), UserInput.end(), ::isdigit))               // checks whether user input is not empty, and the string is all digit from beginning to end
                     {
                         toINT = stoll(UserInput);                                                                  // Convert string to long long integer and store to variable 'toINT'

                         // if 'toINT' is positive number
                         if (toINT > 0) 
                            return toINT;                                                                           // returns VALIDATED value of 'toINT' to main
                         // if 'toINT' is 0 or negative number
                         else 
                             print(4,0);                                                                            // Function call, prints invalid message
                     } 
                     // if UserInput is not pure integers
                     else 
                         print(4,0);                                                                                // Function call, prints invalid message                                                                                
                    
                     cin.clear();                                                                                   // helps clears and reset any error in input stream
                     print(3, 0);                                                                                   // Function call, prints instruction
                 }while(true);                                                                                      // repeats until false
                 break;                                                                                             // terminates case statement

        // block of code to ask for value of 'X'
        default: print(6, index);                                                                                   // Function call, prints instruction
                 do
                 {
                     getline(cin, UserInput);                                                                       // store the userinput to variable storage 'UserInput'
                                                                                                                        // getline  -> reads input from the standard input stream until it reads newline character '\n' 

                     UserInput.erase(remove_if(UserInput.begin(), UserInput.end(), ::isspace), UserInput.end());	// helps remove spaces from input
                                                                                                                    // 	     remove_if -> shifts non-white space characters to the left, overwriting the white space characters.
                                                                                                                    // 	 	   isspace -> checks for white spaces
                                                                                                                    // UserInput.end() ->  second argument to indicate the end of the string after the removal operation. 
                     
                     // if UserInput contains only integer and not empty
                     if (!UserInput.empty() && all_of(UserInput.begin(), UserInput.end(), ::isdigit))               // checks whether user input is not empty, and the string is all digit from beginning to end
                     {
                         toINT = stoll(UserInput);                                                                  // Convert string to long long integer and store to variable 'toINT'

                         // if 'toINT' is positive number
                         if (toINT > 0) 
                             return toINT;                                                                          // returns VALIDATED value of 'toINT' to main
                         // if 'toINT' is 0 or negative number
                         else 
                         {    
                             print(4,0);                                                                            // Function call, prints invalid message
                             cin.clear();                                                                           // helps clears and reset any error in input stream
                         }
                     } 
                     // if UserInput is not pure integers
                     else 
                     {    
                         print(4,0);                                                                                // Function call, prints invalid message
                         cin.clear();                                                                               // helps clears and reset any error in input stream
                     }
                    
                     print(6, index);                                                                               // Function call, prints instruction
                 }while(true);
    }

    return 0;
}

void OUTPUT_to_FILE(    int run, 
                        int type, 
                        int sort_type,
                        string sort_func_name,
                        vector<type_class>& Orig_array, 
                        vector<type_class>& sort_array1, 
                        vector<long long>& sort_array2,
                        string Filename
                )
{
    ofstream file(Filename, ios::app); 

    if(file.is_open())
    {
        if(type == 1)
        {    
            file << "\n\n\nRUN " << run+1 << "...\n\t\tRandom array Before sorting:\n\t\t";
            for (const auto& elem : Orig_array) 
                file << elem << " ";
            
            file << "\n\n\t\tRandom array after sorting (" << sort_func_name << ")\n\t\t";

            if(sort_type == 1)
                for (const auto& elem : sort_array1) 
                    file << elem << " ";
            else
                for (const auto& elem : sort_array2)
                    file << elem << " ";

            file << "\n";
            
            if((run+1) == 5)
                for(int i = 0; i < 100; i++)
                    file << "--";

            file.close();
        }
        else
        {

            file << "\n\n\nRUN " << run+1 << "...\n\t\tSorted array Before sorting:\n\t\t";
            for (const auto& elem : Orig_array) 
                file << elem << " ";
            
            file << "\n\n\t\tSorted array after sorting (" << sort_func_name << ")\n\t\t";

            if(sort_type == 1)
                for (const auto& elem : sort_array1) 
                    file << elem << " ";
            else
                for (const auto& elem : sort_array2) 
                    file << elem << " ";

            file << "\n";

            if((run+1) == 5)
                for(int i = 0; i < 100; i++)
                    file << "--";
        }

        file.close();
    }
}

void runtimes_to_table( vector<vector<double>> time_per_run, vector<double> runAverages, type_class N, int type)
{
    string sort_algo[]= { "Selection Sort", "Bubble Sort","Insertion Sort",
                                  "Mergesort", "QuickSort", "Heapsort", "Radix Sort"
                        };

    for(int k = 0; k < 7; k++)
    {        
        if(type == 1)
        {    
            cout << "\n\n\n\n\t\t\t\t\t\t              ";
            cout << "T(n) for the different runs of " 
                 << sort_algo[k] 
                 << " on random input array";

            print(10,0);
            for(int i = 0; i < 38; i++)                                                                                 // prints design
                cout << ".";
            
            print(10,0);
            printf("|   %15s | %15lu |", "N", N);

            print(10,0);
            for(int i = 0; i < 39; i++)                                                                                 // prints design
                cout << ".";

            for(int i = 0; i < 5; i++)
            {    
                print(10,0);
                printf("| %15s %i | %15f |", "Run", i+1, time_per_run[k][i]);
            }

            print(10,0);
            for(int i = 0; i < 39; i++)                                                                                 // prints design
                cout << ".";

            print(10,0);
            printf("|   %15s | %15f |", "Average", runAverages[k]);

            print(10,0);
            for(int i = 0; i < 39; i++)                                                                                 // prints design
                cout << ".";
        }
        else
        {
            cout << "\n\n\n\n\t\t\t\t\t\t              ";
            cout << "T(n) for the different runs of " 
                 << sort_algo[k] 
                 << " on sorted input array";

            print(10,0);
            for(int i = 0; i < 38; i++)                                                                                 // prints design
                cout << ".";
            
            print(10,0);
            printf("|   %15s | %15lu |", "N", N);

            print(10,0);
            for(int i = 0; i < 39; i++)                                                                                 // prints design
                cout << ".";

            for(int i = 0; i < 5; i++)
            {    
                print(10,0);
                printf("| %15s %i | %15f |", "Run", i+1, time_per_run[k][i]);
            }

            print(10,0);
            for(int i = 0; i < 39; i++)                                                                                 // prints design
                cout << ".";

            print(10,0);
            printf("|   %15s | %15f |", "Average", runAverages[k]);

            print(10,0);
            for(int i = 0; i < 39; i++)                                                                                 // prints design
                cout << ".";
        }
    }
}

// Function to print average time in table form
void print_ave_runtime( vector<vector<double>> sortedAverages, 
                        vector<vector<double>> randomAverages, 
                        vector<vector<type_class>> NArray, 
                        int length
                      )
{
    // VARIABLE DECLARATION AND INITIALIZATION
    int repeat = ((length+4)*7) + length + 18;
    // repeat   ->  variable storage for the length of the table

    if(!sortedAverages.empty())
    {        
        printf("\n\n\t\t\t%*s\n\t\t\t", (repeat-50), "Average Running Time for an Input Array that is Sorted");         //  Prints Table name

        for(int i = 0; i < repeat; i++)                                                                                 // prints design
            cout << "-";

        printf("\n\t\t\t| %*s |%*s |%*s |%*s |%*s |%*s |%*s |%*s |\n\t\t\t",                         
                        length, "N", length+4, "Selection Sort", length+4, "Bubble Sort", length+4, 
                        "Insertion Sort", length+4, "Mergesort", length+4, "Quicksort", 
                        length+4, "Heapsort", length+4, "Radix sort");                                                  // prints row values

        for(int i = 0; i < repeat; i++)                                                                                 // prints design
            cout << "-";

        // loops to access row of 'sortedAverages' vector array until the last element
        for (int i = 0; i < sortedAverages.size(); ++i)                                                         
        {
            printf("\n\t\t\t| %*lu |", length, NArray[0][i]);                                                           // prints the specific value on table

            // loops to access the column of 'sortedAverages' vector array until the last element
            for (int j = 0; j < sortedAverages[i].size(); ++j) 
                if(j == (sortedAverages[i].size() - 1))                                                                 
                    printf("%*f sec |\n\t\t\t", length, sortedAverages[i][j]);                                          // prints the specific value on table  
                else 
                    printf("%*f sec |", length, sortedAverages[i][j]);                                                  // prints the specific value on table

                // if last row is printed
                if(i == sortedAverages.size() -1)                                                                       
                {
                    for(int i = 0; i < repeat; i++)                                                                     // prints design
                        cout << "-";
                    printf("\n");                                                         
                }
        } 
    }

    if(!randomAverages.empty())
    {               
        printf("\n\n\t\t\t%*s\n\t\t\t", (repeat-50), "Average Running Time for an Input Array that is Random");         // Prints Table name

        for(int i = 0; i < repeat; i++)                                                                                 // prints design  
            cout << "-";
                                
            printf("\n\t\t\t| %*s |%*s |%*s |%*s |%*s |%*s |%*s |%*s |\n\t\t\t", 
                        length, "N", length+4, "Selection Sort", length+4, "Bubble Sort", 
                        length+4, "Insertion Sort", length+4, "Mergesort", length+4, 
                        "Quicksort", length+4, "Heapsort", length+4, "Radix sort");                                     // prints row values

        for(int i = 0; i < repeat; i++)                                                                                 // prints design
            cout << "-";

        // loops to access row of 'randomAverages' vector array until the last element
        for (int i = 0; i < randomAverages.size(); ++i) 
        {
            printf("\n\t\t\t| %*lu |", length, NArray[1][i]);                                                         // prints the specific value on table

            // loops to access the column of 'sortedAverages' vector array until the last element
            for (int j = 0; j < randomAverages[i].size(); ++j) 
                if(j == (randomAverages[i].size() - 1)) 
                    printf("%*f sec |\n\t\t\t", length, randomAverages[i][j]);                                        // prints the specific value on table
                else 
                    printf("%*f sec |", length, randomAverages[i][j]);                                                // prints the specific value on table

                // if last row is printed
                if(i == randomAverages.size() -1)                                                                     // .size()  ->  counts how many elements are currently stored in the vector array 'sortedAverages'
                {
                    for(int i = 0; i < repeat; i++)                                                                   // prints design  
                        cout << "-";
                    
                    printf("\n");
                }
        }
    }
}

// Function to Print specific repeated lines in entire code
void print(int part, int index)                                                                                       // Prints the neccessary information to be prompted on terminal PARAMETER serves as the line to be printed
{
    switch(part)                                                                                                      // reads the parameter
    {
		  case 1: for(int i = 1; i <= 50; i++)
                     switch(i)
                     {
                           case 1: cout << "\n\n\t";
                                   break;
                           case 2:
                           case 3:
                           case 5:
                           case 6:
                           case 8:
                          case 10: 
                          case 11:
                          case 17:
                          case 20:
                          case 23:
                          case 26:
                          case 29:
                          case 32:
                          case 35:
                          case 38:
                          case 41:
                          case 48: print(20, 0);
                                   break;
                           case 4: cout << "#####   Bicol University   ########";
                                   break;
                           case 7: 
                          case 15:
                          case 18: 
                          case 21: 
                          case 24: 
                          case 27: 
                          case 30: 
                          case 33: 
                          case 36: 
                          case 39: 
                          case 44: print (21, 0);
                                   break;
                           case 9: cout << "#     College of Science     ######";
                                   break;
                          case 12: 
                          case 14:
                          case 42:
                          case 43:
                          case 49:
                          case 50: print(22, 0);
                                   break;
                          case 13: cout << "\n\t###         #####          " 
                                        << "######            ######          #####" 
                                        << "           #######       #######        ###" 
                                        << "       ###       ####       ####     ###   " 
                                        << " ########  ####            ####"
				                        << "\n\t###   ######  ###   #######  ###   ########" 
                                        << "   ###   #########  ###   #######  ###   ########" 
                                        << "   ###    ####  ####    ###    ####  #####   ####" 
                                        << "     ###    ##  ####  ###   ########   ###"
     			                        << "\n\t###   ######  ###   #######  ###   ########" 
                                        << "   ###   #########  ###   #######  ###   ########" 
                                        << "   ###    ####  ####    ###    ####  #####   ####"
                                        << "     ###    ###  ###  ###   ########   ###"
  				                        << "\n\t###   ######  ###   #######  ###   ########" 
                                        << "   ###   ##############   #######  ###   ########" 
                                        << "   ###    ####  ####    ###    ####  #####   ####" 
                                        << "     ###    ####      ###   ##############"
    	 			                    << "\n\t###           ###        #######   ########" 
                                        << "   ###   #####     ####          #####         " 
                                        << "     ###    ##########    ###    ###########   ####" 
                                        << "     ###    #####     ###   #####     ####"
                 	 			        << "\n\t###   ###########   #####   ####   ########   ###" 
                                        << "   #######   ####   #####   ####   ########   ###    " 
                                        << "##########    ###    ###########   ####     ###    ######" 
                                        << "    ###   #######   ####"
			                            << "\n\t###   ###########   #####   ####   ########   ###   " 
                                        << "#######   ####   #####   ####   ########   ###    ##########" 
                                        << "    ###    ###########   ####     ###    #######   ###   " 
                                        << "#######   ####\n\t###   ###########   #####   ####   ########" 
                                        << "   ####  ######   #####   #####   ####   ########   ###    " 
                                        << "##########    ###    ###########   ####     ###    ########  " 
                                        << "###    #####    ####\n\t###   ###########   #####   #####    " 
                                        << "        ######         ######   #####   ####   ########   ###" 
                                        << "    ##########    ###    ###########   ####     ###    " 
                                        << "######### ####          ######";
                                   break;
                          case 16: cout << "          #####" 
                                        << "           #######" 
                                        <<"          #####" 
                                        << "              ###" 
                                        << "           ####" 
                                        << "         ####" 
                                        << "             ###";
                                   break;
                          case 19: cout << "   ######  ####   ########  ####  ########  #########" 
                                        << "    ########   ############   ######  #######   ########";
                                   break;
                          case 22: cout << "   ######  ####   ########  ####  ########  #########    " 
                                        << "########   ############   ######  #######   ########";
                                   break;
                          case 25: cout << "   ######  ####   ########  ####  ########  #########    " 
                                        << "########   ############   ###############   ########";
                                   break;
                          case 28: cout << "           ####         ########  ########  #########    " 
                                        << "########          #####   ###############   ########";
                                   break;
                          case 31: cout << "   ############   #######   ####  ########  ###   ###    " 
                                        << "########   ############   ###############   ########";
                                   break;
                          case 34: cout << "   ############   #######   ####  ########  ###   ##     " 
                                         << "########   ############   ######  #######   ########";
                                   break;
                          case 37: cout << "   ############   #######   ####  ########  ####  ##    " 
                                        << "#########   ############   ######  #######   ########";
                                   break;
                          case 40: cout << "   ############   #######   #####          ######  #   " 
                                        << "##########          #####         #########   ########";
                                   break;
                          case 46: cout << " Developers: Baile | Balares | Bellen | Latorre | Solano | ";
                                   break;
                          default: for(int i = 0; i < 25; i++)   
                                     cout << "#";  
                     }
                  break; 
          case 2: for(int i = 1; i <= 34; i++)
                    switch (i)
                    {
                         case 1: cout << "\n";
                                 break;
                         case 2: 
                         case 5: 
                         case 9: 
                        case 13: 
                        case 15: 
                        case 17: 
                        case 19: 
                        case 21: 
                        case 23: 
                        case 25: 
                        case 29: 
                        case 33: print(23, 0);
                                 break;
                         case 3: cout << "  ";
                                 break;
                         case 4: for(int i = 0; i < 30; i++)
                                    cout << "_ ";
                                 break;
                         case 6: cout << "|  "; 
                                 break;
                         case 7: for(int i = 0; i < 29; i++)
                                    cout << "_ ";
                                 break;
                         case 8: cout << " | ";
                                 break;
                        case 10: cout << "| |";
                                 break;
                        case 11: for(int i = 0; i < 56; i++)  
                                    cout << " ";  
                                 break;
                        case 12: cout << "|  | ";
                                 break;
                        case 14: 
                        case 18:
                        case 20: 
                        case 24: print(24, 0);
                                 break;
                        case 16: if(index == 1)
                                    cout << "| |             " 
                                         << "Press | 1 | to start the program" 
                                         << "           |  | ";
                                 else
                                    cout << "| |             " 
                                         << "Press | 1 | to create Sorted array" 
                                         << "         |  | ";
                                 break;
                        case 22: if(index == 1)
                                    cout << "| |             " 
                                         << "Press | 2 | to end the program"  
                                         << "             |  | ";
                                 else
                                    cout << "| |             " 
                                         << "Press | 2 | to create random arrray"  
                                         << "        |  | ";
                                 break;
                        case 26: cout << "| |"; 
                                 break;
                        case 27: for(int i = 0; i < 28; i++)
                                    cout << "_ ";
                                 break;
                        case 28: cout << "|  | ";
                                 break;
                        case 30: cout << "| ";
                                 break;
                        case 31: for(int i = 0; i < 30; i++)
                                    cout << "_ ";
                                 break;
                        case 32: cout << "| \n\n\t   ";
                                 break;
                        default: cout << "\t     Enter the number of your choice: ";
                    }
                  break;
          case 3: cout << "\n";
                  print(23, 0);
                  cout << "Enter the number/s of integer you'd like to generate: ";
                  break;
          case 4: for (int i = 1; i <= 22; i++)
                    switch (i)
                    {
                      case 1: cout << "\n";
                              break;
                      case 2: 
                      case 5: 
                      case 9: 
                     case 13: 
                     case 15: 
                     case 19: print(23, 0);
                              break;
                      case 3: cout << " ";
                              break;
                      case 4:
                     case 21: for(int i = 0; i < 30; i++)
                                if(i == 29)
                                    cout << "_";
                                else 
                                    cout << "_ ";
                              break;
                      case 6: cout << "|  ";
                              break;
                      case 7: 
                     case 17: for(int i = 0; i < 28; i++)
                                if(i == 27)
                                    cout << "_";
                                else 
                                    cout << "_ ";
                              break;
                      case 8: cout << "  | ";
                              break;
                     case 10: cout << "| |";
                              break;
                     case 11: for(int i = 0; i < 55; i++)
                                cout << " ";
                              break;
                     case 12: 
                     case 16: 
                     case 18: cout << "| |";
                              break;
                     case 14: cout << "| |        The value should be a positive integers        | | ";
                              break;
                     default: cout << "|";
                    }
                  break;
          case 5: for(int i = 1; i <= 23; i++)
                    switch(i)
                    {
                         case 1: cout << "\n";
                                 break;
                         case 2: 
                         case 6: 
                        case 10: 
                        case 14: 
                        case 16: 
                        case 20: print(23, 0);
                                 break;
                         case 3: 
                         case 5: cout << " ";
                                 break;
                         case 4: 
                        case 22: for(int i = 1; i <= 31; i++)
                                    if(i == 31)
                                        cout << "_";
                                    else
                                        cout << "_ ";
                                 break;
                         case 7: cout << "|  ";
                                 break;
                         case 8: 
                        case 18: for (int i = 0; i < 29; i++)
                                    if(i == 28)
                                        cout << "_";
                                    else
                                        cout << "_ ";
                                 break;
                         case 9: cout << "  | ";
                                 break;
                        case 11: 
                        case 13: 
                        case 17: 
                        case 19: cout << "| |";
                                 break;
                        case 12: for(int i = 0; i < 57; i++)
                                    cout << " ";
                                 break;
                        case 15: cout << "| |      The program is generating the random array # " << index << "     | | ";
                                 break;
                        default: cout << "|";
                    }
                  break;
          case 6: for(int i = 1; i <= 23; i++)
                    switch(i)
                    {
                         case 1: cout << "\n";
                                 break;
                         case 2: 
                         case 6: 
                        case 10: 
                        case 14: 
                        case 16: 
                        case 20: print(23, 0);
                                 break;
                         case 3: 
                         case 5: cout << " ";
                                 break;
                         case 4: 
                        case 22: for(int i = 1; i <= 31; i++)
                                    if(i == 31)
                                        cout << "_";
                                    else
                                        cout << "_ ";
                                 break;
                         case 7: cout << "|  ";
                                 break;
                         case 8: 
                        case 18: for (int i = 0; i < 29; i++)
                                    if(i == 28)
                                        cout << "_";
                                    else
                                        cout << "_ ";
                                 break;
                         case 9: cout << "  | ";
                                 break;
                        case 11: 
                        case 13: 
                        case 17: 
                        case 19: cout << "| |";
                                 break;
                        case 12: for(int i = 0; i < 57; i++)
                                    cout << " ";
                                 break;
                        case 15: cout << "| |	 The program is generating the sorted array # " << index << "     | | ";
                                 break;
                        default: cout << "|";
                    }

                    cout << "\n";
                    print(23, 0);
                    cout << "To generate please enter first element: ";
                  break;
          case 7: cout << "\n\n\t\t\t\t\t\t\tAverage Time taken after five runs to sort using ";
                  break;
          case 8: cout << "\n";
                  print(23, 0);
                  cout << "    !! ERROR DETECTED: Please Strictly follow the rules !! ";
                  break;
          case 9: cout << "\n\n";
                  print(23, 0);
                  cout << "\t   Want to try another set ( y / n )? ";
                  break;
         case 10: cout << "\n\t\t\t\t\t\t\t                  ";
                  break;
         case 20: for(int i = 0; i < 37; i++)
                    cout << "#";
                  break;
         case 21: cout << "\n\t";
                  print(20, 0);
                  break;
         case 22: cout << "\n\t";
                  for(int i = 0; i < 183; i++)
                    cout << "#";
                  break;
         case 23: cout << "\n";
                  for(int i = 0; i < 8; i++)
                    cout << "\t";
                  break;
         case 24: cout << "| |";

                  for(int i = 0; i < 19; i++)
                    cout << " ";

                  cout << "-----";

                  for(int i = 0; i < 32; i++)
                    cout << " ";

                  cout << "|  | ";
                  break;
         default: for(int i = 1; i <= 22; i++)
                    switch (i)
                    {
                         case 1: cout << "\n";
                                 break;
                         case 2: 
                         case 5: 
                         case 9: 
                        case 13: 
                        case 15: 
                        case 19: print(23, 0);
                                 break;
                         case 3: cout << " "; 
                                 break;
                         case 4: 
                        case 21: for(int i = 0; i < 31; i++)
                                    if(i == 30)
                                        cout << "_";
                                    else 
                                        cout << "_ ";
                                 break;
                         case 6: cout << "|  ";
                                 break;
                         case 7: 
                        case 17: for(int i = 0; i < 29; i++)
                                    if(i == 28)
                                        cout << "_";
                                    else 
                                        cout << "_ ";
                                 break;
                         case 8: cout << "  | ";
                                 break;
                        case 10: 
                        case 12:
                        case 16:
                        case 18: cout << "| |";
                                 break;
                        case 11: for(int i = 0; i < 57; i++)
                                    cout << " ";
                                 break;
                        case 14: cout << "| | 	          Thank you, have a nice day!               | | ";
                                 break;
                        default: cout << "|";
                                 break;
                    }
    }
}