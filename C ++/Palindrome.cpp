           // LATORRE, JEO D :: BSCS 2C 
// Data Structures and Algorithm || Machine Exercise 2
#include <iostream>             // cout, cin, .ignore
#include <cctype>				// isdigit(), ::tolower
#include <string>				// getline(), .length()
#include <limits> 				// .limit()
#include <algorithm>			// transform()
using namespace std;

// Self-Referential Structures
typedef struct node
{
	char value;
	struct node *next;	
} slot;


// function prototypes
slot *storing_list(string DATA); 					// struct function to store list
void instructions(int command);						// prints instructions specified by command parameter
void compare(string DATA, slot* stored_list);		// executes the main objective 
int ASK(int command);								// function to ask user to continue engaging with the program

int main()
{
	// Variable declarations
	string choice, data;
	int YORN;
		// choice   -> variable storage when asking choice from user
		//   data   -> variable storage for sample to be check if palindrome or not
		//   YORN   -> storage of return value og function "yes_no()" and update variable of main do-while loop
		
	// do-while loop that checks if "choice" on "instruction(3)" is satisfied		
	do
	{
		instructions(0);				// prints line design
		instructions(1);				// prints Header
		instructions(0);				// prints line design
		
		instructions(3);				// prompts menu
			choice = ASK(0);			// function call to ask user to what to perform																			
		
		system("Cls");					// clears terminal screen
		instructions(0);				// prints line design
		instructions(1);				// prints Header
		instructions(0);				// prints line design
		instructions(2);				// prompts sub header
	
		switch(choice[0])
		{
			// executes "command #1" -> "About" 
			case '1': instructions(8);					// prompts "About"
					  break;							// terminates case statement
					  
			// executes "command #2" -> "Start" 
			case '2': {		cout << "\n\t >>>> Start \n\t\t"; 								// prints sub header
					  		for(int i = 0; i < 14; i++)										// loop iterates to print design
								cout << ".";
					  
					  		cout << "\n\t\t   | Please ensure to visit \"About\" to avoid confusion" 								// prints instructions for user
								 << "\n\t\t   | NOTE: You may enter any word, phrase, number, or hybrid input\n\t\t   | ";			// prints design
						   
						   	// asks user the word, phrase, number, or hybrid input
					  		cout << "  ? ";						
							  	// error handling 			
					  			cin.ignore(numeric_limits<streamsize>::max(), '\n');		// 							cin.ignore ->  ignore characters from the input buffer
					  																		// numeric_limits<streamsize>::max()   ->  specify the characters to ignore. which is set to max value, 'streamsize' can hold
					  																		//								  '\n' ->  delimiter character, sets to ignore input buffer up to next line
					  			
					  		getline(cin, data);												// store the useer input to string 'data'
					  	   	transform(data.begin(), data.end(), data.begin(), ::tolower);   // converts "guess" to uppercase
							slot* Main_LIST = storing_list(data);							//  function call to store the value of 'data' to linked list to revert it and store to a pointer variable "*Main_LIST"

							compare(data, Main_LIST);	// FUNCTION CALL TO KNOW IF USER INPUT IS PALINDROME
					  }
					  break;							// terminates case statement
			
			// executes "command #3" -> "Exit" 
		     default: system("Cls");					// clears terminal screen
			 		  instructions(0);					// prints line design
			 		  instructions(7);					// prompts footer
			 		  instructions(0);					// prints line design
		    		  return 0;							// terminates program
		}

		// function call to ask user to continue or not
		YORN = 	ASK(1);					
	}while(YORN == 1);
	
	return 0;			// terminates program
}

// display program instructions to terminal
void instructions(int command)
{
	// when function "instructions" is called check the parameter and enters the case statements
	switch(command)
	{
		// executes "command #1" -> "instructions(1)" 
		case 1: cout << "\n";	
				for(int i = 0; i < 5; i++)
					cout << " ::::" ;
				cout << "\t  P A L I N D R O M E\t  ";
				for(int i = 0; i < 5; i++)
					cout <<  " ::::" ;
					cout << "\n";	
				break;																			// ends case statement	

		// executes "command #2" -> "instructions(2)" 
		case 2: cout << "\n\n";	
				for(int i = 0; i < 4; i++)
					cout << "     " ;
				cout << "\t  Rearwards _____________ Forwards \t  ";
				for(int i = 0; i < 5; i++)
					cout <<  "     " ;
				break;																			// ends case statement	

		// executes "command #3" -> "instructions(3)" 
		case 3: cout << "\n\n\tAbout (press 1)\t   Start (press 2)"
					 << "        \t Exit (press 3)\n";
				break;																			// ends case statement	

		// executes "command #4" -> "instructions(4)" 
		case 4: cout << "\n\n\t\t   Start (press 2)\t~.~.~\t  Exit (press 3)";
				break;																			// ends case statement	
		
		// executes "command #5" -> "instructions(5)" 
		case 5: cout << "\n\n";	
				for(int i = 0; i < 4; i++)
					cout << "     " ;
				cout << "\t   Re - run _____________ Again    \t  ";
				for(int i = 0; i < 5; i++)
					cout <<  "     " ;
				break;																			// ends case statement	

		// executes "command #6" -> "instructions(6)" 
		case 6: cout << "\n\tHOME (press 1)"
					 << "        \t                          "
					 << "\t EXIT (press 2)\n";
				break;																			// ends case statement	
				
		// executes "command #7" -> "instructions(7)" 
		case 7: cout << "\n";	
				for(int i = 0; i < 5; i++)
					cout << " ::::" ;
				cout << "\t  THANK YOU FOR PLAYING\t  ";
				for(int i = 0; i < 5; i++)
					cout <<  " ::::" ;
					cout << "\n";	
				break;																			// ends case statement

		// executes "command #8" -> "instructions(8)" 
		case 8: cout << "\n\t >>>> About\n\t\t"; 
					for(int i = 0; i < 14; i++)
						cout << "." ;
						
				cout << "\n\t\t   |  A Palindrome " 
					 << "is a word, sentence, verse, or even number that\n\t\t   |" 
					 << "  reads the same backward or forward. In this case, you will make" 
					 << "\n\t\t   |  a program that will accept a word, number or hybrid.\n\t\t" ;
					 
					for(int i = 0; i < 14; i++)
						cout << "." ;
				
				cout << "\n\t\t   |  This Program / System will accept an input that the program will " 
					 << "\n\t\t   |  access if it is a palindrome or not. Will identify whether given" 
					 << "\n\t\t   |  string (Only letters and characters), Integers (Numbers), or hybrid"
					 << "\n\t\t   |  (Combination) is a Palindrome or not.\n\t\t" ;
					 
					for(int i = 0; i < 14; i++)
						cout << "." ;
				
				cout << "\n\t\t   |  Upon Checking, only letters and numbers will be compared;" 
					 << "\n\t\t   |  any punctuation, spaces, or capitalizations entered will be"
					 << "\n\t\t   |  ignored (e.g. if you enter \" a**??S A?? \" it reverted to asa";
				break;																			// ends case statement
																						
		// executes "command #0" -> "instructions(0)" 
	   default: for(int i = 0; i < 14; i++)
					cout << " ~.~.~";	
	}
}

// funtion to ask user to continue engaging with the program
int ASK(int command)
{
	// Variable declarations
	string choice;
	int flag;
		// choice   -> variable storage when asking choice from user
		//   flag   -> loop variable update "flag = 1" -> repeats loop and "flag = 0" -> ends loop
		
	// when function "instructions" is called check the parameter and enters the case statements
	switch(command)
	{	
		// executes "command #1" -> "ASK(0)"
		case 0: // do-while loop that checks if "choice" on "instruction(3)" is satisfied	
				do
				{	
					flag = 1;																								// updates loop "flag = 1" -> repeats loop
					cout << "\n\t.... Enter number of choice: ";															// asks user to "1" -> about  or "2" -> start  or "3" -> exit
					cin >> choice;																							// store to string "choice"
				
					char c = choice[0];																						// store the first character of string to char "c"
					if (isdigit(c) && choice.length() == 1 && (c == '1' || c == '2' || c == '3')) 							// checks whether the parameter is met
					{
						flag = 0;																							// updates loop "flag = 0" -> ends loop
						return c;
					}
					else	
					{
						system("Cls");																						// clears the terminal screen
						instructions(0);																					// prints line design
						instructions(1);																					// prints Header
						instructions(0);																					// prints line design
		
						instructions(3);																					// prompts menu
						cout << "\n\t.... INVALID INPUT. Choices are limited from 1-3";										// prompts error
					}
				}while(flag == 1);
				break;
				
		// executes "command #2" -> "ASK(1)"
	   default: // do-while loop that checks if "choice" on "instruction(3)" is satisfied	
	   			instructions(5);														// prints sub header #2
				instructions(6);														// prints menu #2
				do
				{	
					flag = 1;															// updates loop "flag = 1" -> repeats loop
					cout << "\n\t.... Enter number of choice: ";						// asks user to "1" -> about  or "2" -> start  or "3" -> exit
					cin >> 	choice;														// store to string "choice"
				
					char c = choice[0];													// store the first character of string to char "c"
					if (isdigit(c) && choice.length() == 1 && c == '1') 				// checks whether the parameter is met
					{
						flag = 0;														// updates loop "flag = 0" -> ends loop
						system("Cls");													// clears terminal screen
						return 1;
					}
					else if (isdigit(c) && choice.length() == 1 && c == '2') 			// checks whether the parameter is met
					{
						flag = 0;														// updates loop "flag = 0" -> ends loop
						cout << "\n\n";
						instructions(0);												// prints line design
						instructions(7);												// prompts footer
						instructions(0);												// prints line design
						return 0;
					}
					else	
					{
						system("Cls");														// clears the terminal screen
						instructions(0);													// prints line design
						instructions(1);													// prints Header
						instructions(0);													// prints line design
		
						instructions(5);													// prints sub header #2
						instructions(6);													// prints menu #2
						cout << "\n\t.... INVALID INPUT. Choices are limited from 1-2" ;	// prompts error
					}
				}while(flag == 1);	
	}
}

// funtion to store the string user input to self referecial structure in form of linked list
slot *storing_list(string DATA)
{	
	// Variable declarations
	slot *p, *head = NULL;
		//     *p   -> variable pointer storage for head node
		//   *head  -> variable pointer for head node and initialize it to 'NULL' to avoid error
	
	// loop to store the chracters of user input 'DATA' backwards	
	for(int i =  DATA.length(); i >= 0; i--)
	{
		// help allocate memory address for head node
		if(i == DATA.length())
		{
			head = new slot;			// creates a head address
			p = head;					// sets p as temporarty head pointer for traversing list
		}
		// help allocate memory address for other character as next nodes
		else
		{
			p->next = new slot;			// creates memory address for a new node
				  p = p->next; 			// points the previous node to newly created node
		}
		
		p -> value = DATA[i];			// helps to store the chracters or integers from end to beginning of user input
	}
	
	p -> next = NULL;					// after the loop ends the last pointer is set to null to avoid error
	return (head);						// returns the head in order to access the list
}

// compares the user input to the reversed lidt stored on self referencial structure in the form of linked list
void compare(string DATA, slot* stored_list)
{
	// variable declration and initializations
	int i = 0, flag = 0, only_int = 0, only_letter = 0;
		// 		     i -> variable that will be you to access charaters in user input STRING, and initialize it as "i = 0" to indicate beginning
		//        flag -> variable to identify whether the user input and the reversed of it is the same :: "flag == 0" -> palindrome :: "flag == 1" -> not palindrome
		//    only_int -> variable indicator if the user input has integers
		// only_letter -> variable indicator if user input has letters
	
	slot* node = stored_list;		// create new variable pointer of linked list
	node = node -> next;			// moves the address to the next head node
	
	// loop that iterates until the pointer has stored value of NULL or meets the last pointer
	while(node != NULL)
		if(ispunct(node -> value) || ispunct(DATA[i]) || node -> value == ' ' || DATA[i] == ' ')	// if either user input or linked list is SPACE or PUNCTUATION
			if(node -> value == ' ' || ispunct(node -> value))			// if linked list is SPACE or PUNCTUATION
				node = node -> next;									// Move to next pointer
			else														// if linked list is SPACE or PUNCTUATION
				i++;													// increment the offset value
		else									// if either user input or linked list is niether SPACE nor PUNCTUATION
			if(node -> value == DATA[i])		// if user input and linked list is the same
			{
				i++;							// increment the offset value
				node = node -> next;			// Move to next pointer
			}
			else								// if user input and linked list is not the same
			{
				flag = 1;						// updates flag to indicate that it is not a palindrome
				break;							// exits loop
			}	
	
	// loop to check whether the user input has integers and or letters		 
	for(int i = 0; i < DATA.length(); i++)
		if(!ispunct(DATA[i]) || DATA.length() != ' ')		// if character is not a PUNTUATION or SPACE
			if(isdigit(DATA[i]))							// checks character if it is an integer
				only_int = 1;								// updates indicator
			else if(isalpha(DATA[i]))						// checks character if it is a letter
				only_letter = 2;							// updates indicator
	
	// to be use on switch statement adding all indicators	
	int total_base = (flag*10) + only_int + only_letter;
		
		cout << "\t\t";
		for(int i = 0; i < 14; i++)							// loop iterates to print design
			cout << ".";
			cout << "\n\t\t   |"; 							// prints design
	
	// prints respective conclusion base on findings
	switch(total_base)
	{
	// for palindrome set
		case 1: cout << " The Integer input, you entered (" << DATA << ") is a palindrome\n";
				break;																						// terminates case statement
		case 2: cout << " The String input, you entered (" << DATA << ") is a palindrome\n";
	   			break;																						// terminates case statement
		case 3: cout << " The Hybrid input, you entered (" << DATA << ") is a palindrome\n";
				break;																						// terminates case statement
	
	// for not palindrome set
	   case 11: cout << " The Integer input, you entered (" << DATA << ") is not a palindrome\n";
				break;																						// terminates case statement
	   case 12: cout << " The String input, you entered (" << DATA << ") is not a palindrome\n";
	   			break;																						// terminates case statement
	   default: cout << " The Hybrid input, you entered (" << DATA << ") is not a palindrome\n";
	}	
}
