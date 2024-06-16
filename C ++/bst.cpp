           // LATORRE, JEO D :: BSCS 2C 
// Data Structures and Algorithm || Machine Exercise 2

/*
		~ ::	FEATURES	:: ~ 
		
	1. Tree Selection
			>> Choose between AVL trees and binary search trees (BSTs) for your operations.
	2. AVL Tree Balancing
			>> Exclusive AVL tree support ensures balanced and efficient tree structures.
	3. Insertion
	4. Deletion
	5. Tree Visualization: 
			>> TRAVERSING
				 ... In order			
				 ... Pre order
				 ... Post order
	6. Switching Trees
			>> Switch between AVL and BSTs (note: switching erases the current tree's contents).
	7. User Interface
	8. Repetition
	9. Error Handling
				 	
		~ ::	FEATURES	:: ~ 
*/
#include <iostream>             // cout, cin, .ignore
#include <cctype>				// isdigit(), isalpha, ::isspace
#include <string>				// getline(), .length(), .erase
#include <limits> 				// (numeric_limits<streamsize>::max()
#include <algorithm>			// remove_if()	
#include <sstream>				// istringstream()
using namespace std;

// Self-Referential Structures
typedef struct BSTnode
{
	int data;
	struct BSTnode *left;			
	struct BSTnode *right;		
	int height;
} slot;


// function prototypes
slot *storing_list(int DATA);						// Declares and initialize new node with the 'DATA' passed as user input
slot* insert(slot* node, int DATA);					// inserts new node and initialize it with the new 'DATA' passed as user input
slot *INSERT(slot *list, int DATA);
slot* ROTATE_left(slot* TEMP);
slot* LOWEST(slot* list);							// checks for the minimum value on the list 
slot* DELETE_data(slot* list, int DATA);			// function to delete specified 'data' on list
slot* ROTATE_right(slot* list);

void VIEW_inorder(slot *list);						// prints data using IN ORDER TRAVERSAL from root node
void VIEW_preorder(slot *list);						// prints data using PRE ORDER TRAVERSAL from root node
void VIEW_postorder(slot *list);					// prints data using POST ORDER TRAVERSAL from root node
void instructions(int command);						// prints instructions specified by command parameter

int input_NUM(string word);							// asks user for input
int ASK(int command, int specific);								// function to ask user to continue engaging with the program
int DUPLICATION(slot *list, int DATA); 				// function to check for duplication, return 1 if duplicated return 0 if not
int MAX(int num1, int num2);
int HEIGHT(slot* list);
int BAL_factor(slot* list);

int main()
{		
	// Variable declarations
	slot *MAINlist = NULL;
	int choice, DATA, YORN, show = 1, show2 = 1, show3 = 1, index = 1, DUP, opt = 1;
		// *MAINlist -> variable pointer for linked list, initialized as 'NULL' to avoid error
		//    choice -> variable storage when asking choice from user
		//      YORN -> storage of return value og function "yes_no()" and update variable of main do-while loop
		//      show -> variable indicator that enables to read or skip the first part of do while loop, initialized as 1 to read block
		//     show2 -> variable indicator that enables to read or skip the first part of case 2 on switch statement, initialized as 1 to read block
		//	    DATA -> variable storage of user input as value to be inserted in the linked list
		//     index -> variable for node printing, initialized as 1 to start index at 1
		//		 DUP -> variable storage for duplication
		
	// do-while loop that checks if "YORN" on "ASK(1)" is true	
	do
	{
		if(show == 1)						// helps to skip or read block when loop repeats
		{
			instructions(11);				// prints header
			
			instructions(3);				// prompts menu
				choice = ASK(0, 0);			// function call to ask user to what to perform																			
			
			instructions(11);				// prints header
			instructions(2);				// prompts sub header
		}
		
		int task; 	  
		switch(choice)
		{
			// executes "command #1" -> "About" 
			case 1: instructions(8);					// prompts "About"
					  YORN = ASK(1, 0);					// function call to ask user to continue or not
					  show = 0;							// skips first part of the loop
					  choice = 2;						// pre defines the variable for switch statement
					  break;							// terminates case statement
					  
			// executes "command #2" -> "Start" 
			case 2: { int tree_type, decision;		
					  if(show2 == 1)
					  {
					  	instructions(11);					// prints header
					  	cout << "\n\n\t >>>> Start \n\t\t"; // prints sub header
					  	instructions(6);	 				// prints design
					  	
					  	tree_type = ASK(2,0);					// function call that ask what kind of tree to be used
					  }
					  else
					  {
					  		cout << "\n\t\t"; 			// prints sub header
					  		instructions(6);	 		// prints design
					  		if(opt == 1)
					  			decision = ASK(3, 1);			// function call that ask what kind of tree to be used
					  		else
					  			decision = ASK(3, 0);			// function call that ask what kind of tree to be used
					  			
					  	switch(decision)
					  	{
					  		case 1: if(opt == 1)
								  	{
									  	tree_type = 2;				// pre define tree type
						  				show2 = 1;					// enables reading a block of code
						  				index = 1;					// initialize index back to one
						  				
						  				MAINlist = NULL;		// sets list to null
						  			}
						  			else
						  			{
						  				tree_type = 1;				// pre define tree type
						  				show2 = 1;					// enables reading a block of code
						  				index = 1;					// initialize index back to one
						  				
						  				MAINlist = NULL;		// sets list to null
									}
							  		break;
							case 2: if(opt == 1)
								  		tree_type = 1;				// pre define tree type
						  			else
						  				tree_type = 2;				// pre define tree type
									task = 1;						// pre define the task
							  		break;	
							case 3: if(opt == 1)
								  		tree_type = 1;				// pre define tree type
						  			else
						  				tree_type = 2;				// pre define tree type
									task = 2;						// pre define the task
							  		break;
							case 4: if(opt == 1)
								  		tree_type = 1;				// pre define tree type
						  			else
						  				tree_type = 2;				// pre define tree type
									task = 3;						// pre define the task
							  		break;	
						   default: tree_type = 0;					// pre define tree type
						}
					  }
					  
					  if(tree_type == 0)			// if zero repeats loop and predefine variables to enter switch statement 'default'
					  {
					  		YORN = 1;				// repeats loop
					    	show = 0;				// skips first part of the loop
					  		choice = 3;				// pre defines the variable for switch statement
		    		  }
			   		  else							// if returned value is not zero
					  {
							instructions(11);		// prints header
							instructions(2);		// prompts sub header					
							switch(tree_type)
							{								
								case 1: {	cout << "\n\t >>>> BST (Binary Search Tree)\n\t\t";
								
											if(show2 == 1)
												do
												{	
													instructions(9);										// prints instruction
													task = input_NUM("(0 - 4)");							// asks user for integer input, stores the return value wgich is the user input
													instructions(11);										// prints header
													instructions(2);										// prompts sub header
													cout << "\n\t >>>> BST (Binary Search Tree)\n\t\t"; 	// prints subheader	
												}while(task < 1 && task > 4);
												
											switch(task)
											{
												case 1:	instructions(6);	 																// prints design
														cout << "\n\t\t   | Input #" << index << ": ";										// prints ask
														DATA = input_NUM(" ");																// asks user for integer input, stores the return value which is the user input, passes space
															
														DUP = DUPLICATION(MAINlist, DATA);
														if(DUP == 0)		
														{
															MAINlist = insert(MAINlist, DATA);												// insert list through linked list 
															index++;
														}
														else
														{
															cout << "\t\t";
															instructions(6);	 															// prints design
															cout << "\n\t\t     !! DUPLICATION: Input " << DATA <<" already exist\n\t\t";	// prints ask
														}
														
														YORN = 1;							// repeats loop
														show = 0;							// skips first part of the loop
														choice = 2;							// pre defines the variable for switch statement
														show2 = 0;							// skips first part of the loop	
														opt = 1;							
														break;
														
												case 2:	instructions(6);	 																// prints design
														cout << "\n\t\t   | Delete data: ";													// prints ask
														DATA = input_NUM(" ");																// asks user for integer input, stores the return value which is the user input, passes space
															
														DUP = DUPLICATION(MAINlist, DATA);
														if(DUP == 1)		
														{
															MAINlist = DELETE_data(MAINlist, DATA);												// delete list through linked list 
															cout << "\t\t";
															instructions(6);	 																// prints design
															cout << "\n\t\t     !! DELETION: Input " << DATA <<" was removed from list\n\t\t";	// prints ask
															index--;
														}
														else
														{
															cout << "\t\t";
															instructions(6);	 															// prints design
															cout << "\n\t\t     !! NOT FOUND: Input " << DATA <<" don't exist\n\t\t";		// prints ask
														}
														
														YORN = 1;							// repeats loop
														show = 0;							// skips first part of the loop
														choice = 2;							// pre defines the variable for switch statement
														show2 = 0;							// skips first part of the loop
														opt = 1;
														break;
														
											  case 3:	instructions(11);											// prints header
														cout << "\n\n\t >>>> BST (Binary Search Tree)\n\t\t"; 		// prints subheader	
	
														int task;
														do
														{	
															instructions(10);										// prints instr	uction
															task = input_NUM("(0 - 4)");							// asks user for integer input, stores the return value wgich is the user input
															instructions(11);										// prints header
															instructions(2);										// prompts sub header
															cout << "\n\t >>>> BST (Binary Search Tree)\n\t\t"; 	// prints subheader	
														}while(task < 0 && task > 4);
															
														switch(task)
														{
															case 1: instructions(6);	 			
																	cout << "\n\t\t   | PRE ORDER: Current list: ";
																	cout << "\n\t\t   	[]";
																	VIEW_preorder(MAINlist);
																	
																	cout << "\n";
																	YORN = 1;				// repeats loop
													 	   			show = 0;				// skips first part of the loop
								  									choice = 2;				// pre defines the variable for switch statement
								  									show2 = 0;				// skips first part of case 2 of switch statement
								  									opt = 1;
																	break;
																	
															case 2: instructions(6);	 			
																	cout << "\n\t\t   | IN ORDER: Current list: ";
																	cout << "\n\t\t   	[] ";
																	VIEW_inorder(MAINlist);
																	
																	YORN = 1;				// repeats loop
													 	   			show = 0;				// skips first part of the loop
								  									choice = 2;				// pre defines the variable for switch statement
								  									show2 = 0;				// skips first part of case 2 of switch statement
								  									opt = 1;
																	break;
															case 3: instructions(6);	 			
																	cout << "\n\t\t   | POST ORDER: Current list: ";
																	cout << "\n\t\t   	[] ";
																	VIEW_postorder(MAINlist);
																	
																	YORN = 1;				// repeats loop
													 	   			show = 0;				// skips first part of the loop
								  									choice = 2;				// pre defines the variable for switch statement
								  									show2 = 0;				// skips first part of case 2 of switch statement
								  									opt = 1;
																	break;
														   default: YORN = 1;				// repeats loop
													 	   			show = 0;				// skips first part of the loop
								  									choice = 3;				// pre defines the variable for switch statement
														}
														break;
											   default: YORN = 1;				// repeats loop
											   			show = 0;				// skips first part of the loop
					  									choice = 3;				// pre defines the variable for switch statement
											}
										}
										break;
											
							   default: {	cout << "\n\t >>>> AVL (Adelson-Velsky and Landis)\n\t\t"; 	
							   				if(show2 == 1)
												do
												{	
													instructions(13);											// prints instruction
													task = input_NUM("(0 - 4)");								// asks user for integer input, stores the return value wgich is the user input
													instructions(11);											// prints header
													instructions(2);											// prompts sub header
													cout << "\n\t >>>> AVL (Adelson-Velsky and Landis)\n\t\t"; 	// prints subheader	
												}while(task < 1 && task > 4);
												
											switch(task)
											{
												case 1:	instructions(6);	 																// prints design
														cout << "\n\t\t   | Input #" << index << ": ";										// prints ask
														DATA = input_NUM(" ");																// asks user for integer input, stores the return value which is the user input, passes space
														
														DUP = DUPLICATION(MAINlist, DATA);
														if(DUP == 0)		
														{
															MAINlist = INSERT(MAINlist, DATA);												// insert list through linked list 
															index++;
														}
														else
														{
															cout << "\t\t";
															instructions(6);	 															// prints design
															cout << "\n\t\t     !! DUPLICATION: Input " << DATA <<" already exist\n\t\t";	// prints ask
														}
													
														YORN = 1;							// repeats loop
														show = 0;							// skips first part of the loop
														choice = 2;							// pre defines the variable for switch statement
														show2 = 0;							// skips first part of the loop
														opt = 2;
														break;
														
												case 2:	instructions(6);	 																// prints design
														cout << "\n\t\t   | Delete data: ";													// prints ask
														DATA = input_NUM(" ");																// asks user for integer input, stores the return value which is the user input, passes space
															
														DUP = DUPLICATION(MAINlist, DATA);
														if(DUP == 1)		
														{
															MAINlist = DELETE_data(MAINlist, DATA);												// delete list through linked list 
															cout << "\t\t";
															instructions(6);	 																// prints design
															cout << "\n\t\t     !! DELETION: Input " << DATA <<" was removed from list\n\t\t";	// prints ask
															index--;
														}
														else
														{
															cout << "\t\t";
															instructions(6);	 															// prints design
															cout << "\n\t\t     !! NOT FOUND: Input " << DATA <<" don't exist\n\t\t";		// prints ask
														}
														
														YORN = 1;							// repeats loop
														show = 0;							// skips first part of the loop
														choice = 2;							// pre defines the variable for switch statement
														show2 = 0;							// skips first part of the loop
														opt = 2;
														break;
														
												case 3:	instructions(11);											// prints header
														cout << "\n\t >>>> AVL (Adelson-Velsky and Landis)\n\t\t"; 	// prints subheader	
														int task;
														do
														{	
															instructions(10);											// prints instr	uction
															task = input_NUM("(0 - 4)");								// asks user for integer input, stores the return value wgich is the user input
															instructions(11);											// prints header
															instructions(2);											// prompts sub header
															cout << "\n\t >>>> AVL (Adelson-Velsky and Landis)\n\t\t"; 	// prints subheader	
														}while(task < 0 && task > 4);
															
														switch(task)
														{
															case 1: instructions(6);	 			
																	cout << "\n\t\t   | PRE ORDER: Current list: ";
																	cout << "\n\t\t   	[]";
																	VIEW_preorder(MAINlist);
																	
																	cout << "\n";
																	YORN = 1;				// repeats loop
													 	   			show = 0;				// skips first part of the loop
								  									choice = 2;				// pre defines the variable for switch statement
								  									show2 = 0;				// skips first part of case 2 of switch statement
								  									opt = 2;
																	break;
																	
															case 2: instructions(6);	 			
																	cout << "\n\t\t   | IN ORDER: Current list: ";
																	cout << "\n\t\t   	[] ";
																	VIEW_inorder(MAINlist);
																	
																	YORN = 1;				// repeats loop
													 	   			show = 0;				// skips first part of the loop
								  									choice = 2;				// pre defines the variable for switch statement
								  									show2 = 0;				// skips first part of case 2 of switch statement
								  									opt = 2;
																	break;
															case 3: instructions(6);	 			
																	cout << "\n\t\t   | POST ORDER: Current list: ";
																	cout << "\n\t\t   	[] ";
																	VIEW_postorder(MAINlist);
																	
																	YORN = 1;				// repeats loop
													 	   			show = 0;				// skips first part of the loop
								  									choice = 2;				// pre defines the variable for switch statement
								  									show2 = 0;				// skips first part of case 2 of switch statement
								  									opt = 2;
																	break;
														   default: YORN = 1;				// repeats loop
													 	   			show = 0;				// skips first part of the loop
								  									choice = 3;				// pre defines the variable for switch statement
														}
														break;
														
											   default: YORN = 1;				// repeats loop
											   			show = 0;				// skips first part of the loop
					  									choice = 3;				// pre defines the variable for switch statement
											}
							   			}
							}
					   }
					}
				    break;							// terminates case statement
			
			// executes "command #3" -> "Exit" 
		  default: system("Cls");					// clears terminal screen
			  	   instructions(0);					// prints line design
			 	   instructions(7);					// prompts footer
			  	   instructions(0);					// prints line design
		     	   return 0;							// terminates program
		}				
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
				cout << "\t  T R E E H O U S E\t  ";
				for(int i = 0; i < 5; i++)
					cout <<  " ::::" ;
					cout << "\n";	
				break;																			// ends case statement	

		// executes "command #2" -> "instructions(2)" 
		case 2: cout << "\n\n\t Exploring Tree Data Structures: A Comprehensive Implementation Guides";
				break;																			// ends case statement	

		// executes "command #3" -> "instructions(3)" 
		case 3: cout << "\n\n\tAbout (press 1)\t\t   Start (press 2) \t    Exit (press 3)\n";
				break;																			// ends case statement	

		// executes "command #4" -> "instructions(4)" 
		case 4: cout << "\n\n\n\tStart (press 1)  ";
					 for(int i = 0; i < 5; i++)
						cout << " ~.~.~";
				cout << "  Exit (press 2)";
				break;																			// ends case statement	
		
		// executes "command #4" -> "instructions(5)" 
		case 5: instructions(6);	  		
				cout << "\n\t\t   | What do you prefer? (Kindly enter number of choice)"	
					 << "\n\t\t   	   [1] BST (Binary search tree)"		
					 << "\n\t\t   	   [2] AVL Tree (Adelson-Velsky and Landis)"
					 << "\n\t\t   	   [3] EXIT ";	
				break;																			// ends case statement	
		
		// executes "command #4" -> "instructions(6)" 
		case 6: for(int i = 0; i < 14; i++)										
					cout << ".";
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
				instructions(6);	 
				cout << "\n\t\t   |  TREE HOUSE your home for mastering binary tree structures" 
					 << "\n\t\t   |  a versatile and intuitive tool designed to help you explore" 
					 << "\n\t\t   |  the world of binary trees effortlessly\n\t\t" ;
					 
				instructions(6);	 
				cout << "\n\t\t   |  PLEASE NOTE that all inputs in this Program / System are limited" 
					 << "\n\t\t   |  to INTEGERS(positive whole numbers), whether inserting or performing" 
					 << "\n\t\t   |  other operations, our focus remains on the simplicity and elegance"
					 << "\n\t\t   |  of integer-based data\n\t\t" ;
					 
				instructions(6);	 
				cout << "\n\t\t   |  Upon Switching from BST to AVL and vise versa, inputs or list" 
					 << "\n\t\t   |  will be deleted and pointer will be set as null";
				
				cout << "\n\n Enjoy your journey through the world of binary trees, where positive integers reign supreme";
				break;																			// ends case statement
		
		// executes "command #9" -> "instructions(9)"
		case 9: instructions(6);	 						
				cout << "\n\t\t   | The following are the system's features under BST:"							
		 		 	 << "\n\t\t     	[ 1 ] Insert"			
					 << "\n\t\t     	[ 2 ] Delete"
					 << "\n\t\t     	[ 3 ] View list"
					 << "\n\t\t     	[ 4 ] Exit\n\t\t";
					 
				instructions(6);	 			
				cout << "\n\t\t   | Number of choice: ";													
				break;																			// ends case statement	

		// executes "command #0" -> "instructions(10)" 
		case 10:instructions(6);	 						
				cout << "\n\t\t   | What do you prefer to Use to view list"							
		 		 	 << "\n\t\t     	[ 1 ] Pre order Traversal"			
					 << "\n\t\t     	[ 2 ] In order Traversal"
					 << "\n\t\t     	[ 3 ] Post order traversal"
					 << "\n\t\t     	[ 4 ] Exit\n\t\t";		
				
				instructions(6);	 			
				cout << "\n\t\t   | Number of choice: ";	
				break;																			//ends case statement
		
		// executes "command #0" -> "instructions(11)" 
		case 11: system("Cls");										
				 instructions(0);										
				 instructions(1);										
				 instructions(0);										
			 	 break;																			// ends case statement	
		
		// executes "command #0" -> "instructions(12)" 
		case 12: instructions(6);	  		
				cout << "\n\t\t   | What do you prefer? (Kindly enter number of choice)"	
					 << "\n\t\t   	   [1] SWITCH to AVL Tree (Adelson-Velsky and Landis)"		
					 << "\n\t\t   	   [2] Insert again"
					 << "\n\t\t   	   [3] Delete"		
					 << "\n\t\t   	   [4] View list"
					 << "\n\t\t   	   [5] EXIT ";	
				break;																			// ends case statement	
		
		// executes "command #0" -> "instructions(13)" 
		case 13:instructions(6);	 						
				cout << "\n\t\t   | The following are the system's features under AVL:"							
		 		 	 << "\n\t\t     	[ 1 ] Insert"			
					 << "\n\t\t     	[ 2 ] Delete"
					 << "\n\t\t     	[ 3 ] View list"
					 << "\n\t\t     	[ 4 ] Exit\n\t\t";	
				
				instructions(6);	 			
				cout << "\n\t\t   | Number of choice: ";	
				break;																			//ends case statement

		// executes "command #0" -> "instructions(14)" 
		case 14: instructions(6);	  		
				 cout << "\n\t\t   | What do you prefer? (Kindly enter number of choice)"	
					 << "\n\t\t   	   [1] SWITCH to BST Tree (Binary Search Tree)"		
					 << "\n\t\t   	   [2] Insert again"
					 << "\n\t\t   	   [3] Delete"		
					 << "\n\t\t   	   [4] View list"
					 << "\n\t\t   	   [5] EXIT ";	
				break;																			//ends case statement 	
																											
		// executes "command #0" -> "instructions(0)" 
	   default: for(int i = 0; i < 14; i++)
					cout << " ~.~.~";	
	}
}

// funtion to ask user to continue engaging with the program
int ASK(int command, int specific)
{
	// Variable declarations
	int flag, choice;
	switch(command)
	{	
		// executes "command #1" -> "ASK(0)"
		case 0: // do-while loop that checks if "choice" on "instruction(3)" is satisfied	
				do
				{	
					flag = 0;
					cout << "\n\t\t   | Enter number of choice: ";							// asks user to "1" -> about  or "2" -> start  or "3" -> exit
					
					choice = input_NUM("(1 - 3)");											// function call to get number
					
					if(choice != 1 && choice != 2 && choice != 3)
					{
						flag = 1;
						instructions(11);													// prints header
			
						instructions(3);													// prompts menu
						cout << "\n\t.... INVALID INPUT. Choices are limited from 1-3";		// prompts error
					}
				}while(flag == 1);
				return choice;
				break;
				
		// executes "command #2" -> "ASK(1)"
	   	case 1: // do-while loop that checks if "choice" on "instruction(3)" is satisfied	
				instructions(4);															// prints menu #2
				do
				{	
					flag = 1;																// updates loop "flag = 1" -> repeats loop
					cout << "\n\t\t   | Enter number of choice: ";							// asks user to "1" -> start  or "2" -> exit 
					choice = input_NUM("(1 & 2)");													// function call to get number
					
					if (choice == 1) 														// checks whether the parameter is met
					{
						instructions(11);													// prints header	
						cout << "\n";					
						return 1;
					}
					else if (choice == 2) 													// checks whether the parameter is met
					{
						cout << "\n\n";
						instructions(0);													// prints line design
						instructions(7);													// prompts footer
						instructions(0);													// prints line design
						return 0;
					}
					else	
					{
						instructions(11);													// prints header
						instructions(4);													// prints menu #2
						cout << "\n\n\t.... INVALID INPUT. Choices are limited from 1-2" ;	// prompts error
					}
				}while(flag == 1);	
				break;	
				
		// executes "command #3" -> "ASK(2)"
	   	case 2: // do-while loop that checks if "choice" on "instruction(3)" is satisfied	
				instructions(5);							// prints menu #5
				do
				{	
					flag = 1;											// updates loop "flag = 1" -> repeats loop
					cout << "\n\t\t";
					instructions(6);	 
					cout << "\n\t\t   | Enter number of choice: ";		// asks user to "1" -> BST  or "2" -> AVL  or "3" -> exit
					choice = input_NUM("(1 - 3)");						// function call to get number
					
					if (choice == 1) 									// checks whether the parameter is met
						return 1;
					else if (choice == 2) 								// checks whether the parameter is met
						return 2;
					else if (choice == 3) 								// checks whether the parameter is met
						return 0;
					else	
					{
						instructions(11);								// prints header
						instructions(2);								// prints menu #2						
						cout << "\n\n\t\t";
						
						instructions(5);								// prints menu #5
						
						cout << "\n\n\t.... INVALID INPUT. Choices are limited from 1-3" ;	// prompts error
					}
				}while(flag == 1);	
				break;	
				
	  // executes "command #4" -> "ASK(3)"		
	  default: // do-while loop that checks if "choice" on "instruction(3)" is satisfied	
				if(specific == 1)
					instructions(12);									// prints menu #12
				else
					instructions(14);									// prints menu #14
				do
				{	
					flag = 1;											// updates loop "flag = 1" -> repeats loop
					cout << "\n\t\t";
					instructions(6);	 
					cout << "\n\t\t   | Enter number of choice: ";		// asks user to "1" -> BST  or "2" -> AVL  or "3" -> exit
					choice = input_NUM("(1 - 5)");						// function call to get number
					
					switch(choice)
					{
						case 1: return 1;
						case 2: return 2;
						case 3: return 3;
						case 4: return 4;
						case 5: return 5;
					   default: instructions(11);						// prints header
								instructions(2);						// prints menu #2						
								cout << "\n\n\t\t";
						
								if(specific == 1)
									instructions(12);									// prints menu #12
								else
									instructions(14);									// prints menu #14
						
								cout << "\n\n\t.... INVALID INPUT. Choices are limited from 1-5" ;	// prompts error
					}
				}while(flag == 1);	
				break;	
	}
}

// ask integer input from user
int input_NUM(string word)
{
	// variable declration and initialization
	int flag = 0, toINT;
		//  flag -> update variable of do while loop :: "flag == 0" -> repeats loop :: "flag == 1" -> terminates loop
		// toInt -> variable storage when string "UserInput" is extracted to int

								   												
	do
	{
		// variable declration and initialization
		string UserInput;
		int flag = 0, only_int = 0, only_letter = 0, punct = 0, checker;
		// only_letter -> variable indicator if user input has letters
		// 	 UserInput -> variable storage for user input
		//    only_int -> variable indicator if the user input has integers
		//     checker -> variable storage of the sum of indicators
		//		 punct -> variable indicator if user input has punctuations
		//        flag -> initialize "flag == 0" to enable repetition
													  			
		getline(cin, UserInput);									// store the useer input to string 'UserInput'

		UserInput.erase(remove_if(UserInput.begin(), UserInput.end(), ::isspace), UserInput.end());		// helps remove spaces from input
																										// 	     remove_if -> shifts non-white space characters to the left, overwriting the white space characters.
																										// 	 	   isspace -> checks for white spaces
																										// UserInput.end() ->  second argument to indicate the end of the string after the removal operation. 
		// enables to check the characters of the user input																									
		for(int i = 0; i < UserInput.length(); i++)
			if(isdigit(UserInput[i]))						// checks character if it is an integer
				only_int = 1;									// updates indicator
			else if(isalpha(UserInput[i]))					// checks character if it is a letter
				only_letter = 2;								// updates indicator
			else											// checks character if it is a punctuation
				punct = 10;										// updates indicator
		
		// summation of indicators			
		checker = only_int + only_letter+ punct;
		
		if(checker == 1)
		{
			istringstream(UserInput) >> toINT;			// cextract the integer from input stored in string container
			return toINT;		// returns the user input
		}
		else
		{
			instructions(11);				// prints header
			cout << "\n\t\t"; 								
				for(int i = 0; i < 15; i++)					// loop iterates to print design
					cout << ".";
					
			cout << "\n\t    .... INVALID INPUT .... " 		// prompts error
				 << "\n\t\t   | NOTE: Your input must be an integer " << word << "\n\t\t   | "			// prints design
				 << "  ? ";	
		}
	}while(flag == 0);
}

slot* insert(slot* node, int DATA)
{
	if(node == NULL)									// if pointer is empty or NULL
		node = storing_list(DATA);						// allocates address for inserted data
	else if(DATA <= node -> data)						// checks if pointer value is lessthan the data to be inserted
		node -> left = insert(node -> left, DATA);		// recursion till it meet the end, stores it to the left pointer
	else												// if pointer value is greater than the data to be inserted
		node -> right = insert(node -> right, DATA);	// recursion till it meet the end, stores it to the right ponter 
	return node;										// return list
}

slot *storing_list(int DATA)
{	
	slot* tmp = new slot();						// allocates or create new memory address
	tmp -> data = DATA;							// stores the data on the address
	tmp -> left = tmp -> right = NULL;			// sets the left and right pointer of data to null
	
	return tmp;			// return created address or memory
}

void VIEW_inorder(slot *list)
{
    if (list == NULL)
        return;

    VIEW_inorder(list->left);
    cout << list->data << " ";
    VIEW_inorder(list->right);
}

void VIEW_preorder(slot *list)
{
    if (list == NULL)
        return;

    cout << list -> data << " ";
    VIEW_preorder(list -> left);
    VIEW_preorder(list -> right);
}

void VIEW_postorder(slot *list)
{
    if (list == NULL)
        return;

    VIEW_postorder(list -> left);
    VIEW_postorder(list -> right);
    cout << list -> data << " ";
}

int DUPLICATION(slot *list, int DATA) 
{
    if (list == NULL) 
        return 0;
    
    if (DATA == list -> data) 
        return 1;
    else if (DATA < list -> data) 
        return DUPLICATION(list -> left, DATA);
    else 
        return DUPLICATION(list -> right, DATA);
}

slot* DELETE_data(slot* list, int DATA)
{
    if (list == NULL)
        return list;

    if (DATA < list -> data)
        list -> left = DELETE_data(list -> left, DATA);
    else if (DATA > list -> data)
        list -> right = DELETE_data(list -> right, DATA);
    else
    {
        if (list -> left == NULL)
        {
            slot* temp = list -> right;
            delete list;
            return temp;
        }
        else if (list -> right == NULL)
        {
            slot* temp = list -> left;
            delete list;
            return temp;
        }

        slot* temp = LOWEST(list -> right);
        list -> data = temp -> data;
        list -> right = DELETE_data(list -> right, temp -> data);
    }
    return list;
}

slot* LOWEST(slot* list)
{
    slot* head = list;
    
    while (head && list -> left != NULL)
        head = head -> left;
        
    return head;
}

int MAX(int num1, int num2) 
{
    return (num1 > num2) ? num1 : num2;		// simplified if else statement, if num1 is greater than 2 returns num1, else return num2
}

int HEIGHT(slot* list) 
{
    if (list == NULL)			// if pointer address is NULL 
        return 0;				// return zero
        
    return list -> height;		// returns height of list
}

int BAL_factor(slot* list) 
{
    if (list == NULL)			// if pointer address is NULL 
        return 0;				// return zero
        
    return HEIGHT(list -> left) - HEIGHT(list -> right);		// uses the formula to calculate balance factor
}

slot* ROTATE_right(slot* list) 
{
    slot* temp = list -> left;
    slot* p = temp -> right;

    temp -> right = list;
    list -> left = p;

    list -> height = 1+ MAX (HEIGHT (list -> left), HEIGHT (list -> right)) ;
    temp -> height = 1+ MAX (HEIGHT (temp -> left), HEIGHT (temp -> right)) ;

    return temp;
}

slot* ROTATE_left(slot* TEMP) 
{
    slot* list = TEMP -> right;
    slot* p = list -> left;

    list -> left = TEMP;
    TEMP -> right = p;

    TEMP -> height = 1+ MAX (HEIGHT (TEMP -> left), HEIGHT (TEMP -> right)) ;
    list -> height = 1+ MAX (HEIGHT (list -> left), HEIGHT (list -> right));

    return list;
}

slot *INSERT(slot *list, int DATA)
{
    if (list == NULL)
        return storing_list(DATA);
        
    if (DATA < list -> data)
        list -> left = INSERT(list -> left, DATA);
    else if (DATA > list -> data)
        list -> right = INSERT(list->right, DATA);
    else
        return list;

	list -> height = 1 + MAX (HEIGHT(list->left), HEIGHT(list->right));		// initializes the height of list
	
	// Get the balance factor for this node
    int BAL = BAL_factor(list);												// function call for BAL_factor to compute using the formula
        

        // Perform rotations as needed to balance the tree
        // Left-Left case
        if (BAL > 1 && DATA < list->left->data)
            return ROTATE_right(list);

        // Right-Right case
        if (BAL < -1 && DATA > list -> right -> data)
            return ROTATE_left(list);

        // Left-Right case
        if (BAL > 1 && DATA > list -> left -> data)
        {
            list -> left = ROTATE_left(list -> left);
            return ROTATE_right(list);
        }

        // Right-Left case
        if (BAL < -1 && DATA < list -> right -> data)
        {
            list->right = ROTATE_right(list->right);
            return ROTATE_left(list);
        }

    return list;
}
