#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

/******* 		
  			LATORRE, JEO DOMASIG
******/

// structure 
typedef struct 
{
	char location[MAX];	 												// STRUCTURE MEMBER storage of locations
}MANUAL;

// User structure 
struct User 
{
    char name[50];														// STRUCTURE MEMBER storage of name
    char password[20];													// STRUCTURE MEMBER storage of password
    int accountNumber;													// STRUCTURE MEMBER storage of account number
    float balance;														// STRUCTURE MEMBER storage of cash balance
};

struct User users[MAX];													// Array to store user data

// prototypes
void instructions(int command);											// prints instructions specified by command parameter
int array_sub(int checker, int location, int vehicle_type);
int execute(int account, int counter);									// executes the main objective 
float fare(int ORIGIN, int DESTINATION, int DISCOUNT, int vehicle);		// computes the fare
int registerUser(int counter);											// registers account
int login(int counter);													// logins' account

int main(void)
{
	// variable declarations
	int choice, flag = 1, subscript, i;
		//    choice   -> variable storage when asking choice from user
		//      flag   -> loop variable update "flag = 1" -> repeats loop and "flag = 0" -> end loop
		// subscript   -> offset for structure account
		//         i   -> counter for variable for loop
	
	instructions(0);						// prints header
	instructions(1);						// prints first set of choices
		printf(" enter chosen number: ");	// instruction to get the choice number of user
		scanf("%d", &choice);				// stores choice at variable "choice"
	
	// while loop that checks if "choice" on "instruction(1)" is satisfied
	while(flag == 1)
	{
		switch(choice)
		{
			// executes "choice #1" -> "About"
			case 1: system("CLS");							// clears terminal	// prints header
					instructions(0);						// prints header	
					instructions(2);						// prints "About"
					instructions(1);						// prints first set of choices
						printf(" enter chosen number: ");	// instruction to get the choice number of user
						scanf("%d", &choice);				// stores choice at variable "choice"
					flag = 1;								// updates loop "flag = 1" -> repeats loop
					break;									// ends case statement
					
			// executes "choice #2" -> "Quick view"
			case 2:	system("CLS");							// clears terminal
					instructions(0);						// prints header
					instructions(3);						// prints "Quick view"
							int option;						// option as variable choice
							do								// do-while loop that checks if stored int in option is 1 || 2 only
							{
								printf(" ------ Do you wish to create account and avail ticket? \n\t Press 1 if yes \n\t Press 2 if no");		// asks user to "y" -> continue  or "n" -> end
								printf("\n\t ? ");
								scanf("%d", &option);

								system("CLS");							// clears terminal
								instructions(0);						// prints header
							}	
							while(option != 1 && option != 2);
								
								// option is 1
								if(option == 1)		
								{
									flag = 1;				// updates loop "flag = 1" -> repeats loop	
									choice = 3;				// when while loop is repeats choice is set as 3 to enter case 3
								}
								
								//option is 2
								else
								{
									flag = 1;				// updates loop "flag = 1" -> repeats loop
									choice = 4;				// when while loop is repeats choice is set as 4 to enter case 4
								}
					break;									// ends case statement

			// executes "choice #3" -> "Create account / Log in"	
			case 3: system("CLS");							// clears terminal
        			instructions(0);						// prints header
        			
        			FILE *read;
						read = fopen("account.txt", "r");	// open input file pointer
        			
					fscanf(read,"%d", &subscript);			// scans the first input value as number of current account
					
					for(i = 0; i < subscript; i++)			// scans account record and stores in array of structure
						fscanf(read,"%s %s %d %f", users[i].name, users[i].password, &users[i].accountNumber, &users[i].balance);
							
						do
        				{
        					instructions(4);															// prints second set of choice
        					printf(" Enter your choice: ");												// instruction to get the choice number of user
        					scanf("%d", &choice);														// stores choice at variable "choice"
        					
							switch (choice) 
							{
								// executes "choice #1" -> "Register"
            					case 1:	system("CLS");													// clears terminal 
            							instructions(0);												// prints header
										registerUser(subscript);													// function call to execute register account
					                	break;															// ends case statement
					                	
					            // executes "choice #2" -> "Login"
					            case 2:	system("CLS");													// clears terminal
										instructions(0);												// prints header 
										login(subscript);												// function call to execute Login account4
					    				break;															// ends case statement
					    				
					    		// executes "choice #3" -> "Exit"
            					case 3:	puts("\n\t >>>>>> THANK YOU FOR CHECKING OUR SERVICE.\n");		// prints footer
										return 0;														// terminates program
										
								// executes when user entered 1 > choice > 3
           					   default:	system("CLS");													// clears terminal 
           					   			instructions(0);												// prints header	
								  		puts(" >>>>>> invalid choice.\n");								// prints instruction
        					}
        				}while (choice < 1 || choice > 3);												// repeats loop if alue of choice is not satisfied												
						
					flag = 0;	// updates loop "flag = 0" -> ends loop
					break;		// ends case statement
	
			// executes "choice #4" -> "Exit"		
			case 4: puts("\n\t >>>>>> THANK YOU FOR CHECKING OUR SERVICE.\n");		// prints footer
					return 0;														// terminates program
			
			// executes when user entered 1 > choice > 4
	   	   default:	system("CLS");								// clears terminal 
					instructions(0);							// prints header
					puts(" >>>>>> invalid choice.\n");			// prints instruction
	   	  				flag = 1;								// updates loop "flag = 1" -> repeats loop	
						instructions(1);						// prints first set of choices
							printf(" enter chosen number: ");	// instruction to get the choice number of user
							scanf("%d", &choice);				// stores choice at variable "choice"
		}
	}
	return 0;		// terminates program
}

// display program instructions to user
// parameter "command" sets instruction #
void instructions(int command)
{
	// when function "instructions" is called check the parameter and enters the case statements
	switch(command)
	{
		// executes "command #1" -> "instructions(1)" 
		case 1: puts(" How can we help you?"
						"\n\t [1] About"
						"\n\t [2] Quick view"
						"\n\t [3] Create account / Log in"
						"\n\t [4] Exit");
				break;																			// ends case statement	

		/// executes "command #2" -> "instructions(2)" 
		case 2: puts("  >>>>>> These is a prototype program designed to"
						"\n\t compute the transport fare (BUS and VAN)\n"
						
						"\n\t ----------- BUS fare system -----------"
					"\n     Fare is based on distance with minumum fare of"
					"\n     PHP 10.00 and adds PHP 10.00 per additional KM"
					"\n     20%Discount to students / PWD / senior citizen"
						"\n\t ---------------------------------------\n"
						
						"\n\t ----------- VAN fare system -----------"
					"\n     Fare is point-point basis with minumum fare of"
					"\n     PHP 120.00 maximum not exceeding to PHP 360.00"
					"\n     20%Discount to students / PWD / senior citizen"
						"\n\t ---------------------------------------\n");
				break;																			// ends case statement
				
		// executes "command #3" -> "instructions(3)" 
		case 3:     printf("\n\t\t     >>>>> We proudly offer our services <<<<<");
				    printf("\n\t ***** Pay as you ride or in advance for a secured seat *****");
				
				    printf("\n\n\t---------------------------------------------------------------------");
				    printf("\n\t| %-20s | %-10s | %-13s | %-13s |", "Route", "Vehicle", "Duration", "Price");
				    printf("\n\t---------------------------------------------------------------------");
				    printf("\n\t| %-20s | %-10s | %-13s | %-13s |", "Sorsogon - Legazpi", "Van", "1 hour", "PHP 96 - 120");
				    printf("\n\t| %-20s | %-10s | %-13s | %-13s |", "and vice versa", "BUS", "2 - 3 hours", "PHP 80 - 100");
				    printf("\n\t---------------------------------------------------------------------");
				    printf("\n\t| %-20s | %-10s | %-13s | %-13s |", "Sorsogon - Casiguran", "Van", "1 hour", "PHP 96 - 120");
				    printf("\n\t| %-20s | %-10s | %-13s | %-13s |", "and vice versa", "", "", "");
				    printf("\n\t---------------------------------------------------------------------");
				    printf("\n\t| %-20s | %-10s | %-13s | %-13s |", "Casiguran - Gubat", "Van", "1 hour", "PHP 96 - 120");
				    printf("\n\t| %-20s | %-10s | %-13s | %-13s |", "and vice versa", "", "", "");
				    printf("\n\t---------------------------------------------------------------------");
				    printf("\n\t| %-20s | %-10s | %-13s | %-13s |", "Legazpi - Casiguran", "Van", "2 hours", "PHP 192 - 240");
				    printf("\n\t| %-20s | %-10s | %-13s | %-13s |", "and vice versa", "", "", "");
				    printf("\n\t---------------------------------------------------------------------");
				    printf("\n\t| %-20s | %-10s | %-13s | %-13s |", "Gubat - Sorsogon", "Van", "2 hours", "PHP 192 - 240");
				    printf("\n\t| %-20s | %-10s | %-13s | %-13s |", "and vice versa", "", "", "");
				    printf("\n\t---------------------------------------------------------------------");
				    printf("\n\t| %-20s | %-10s | %-13s | %-13s |", "Gubat - Legazpi", "Van", "1 - 2 hours", "PHP 288 - 360");
				    printf("\n\t| %-20s | %-10s | %-13s | %-13s |", "and vice versa", "", "", "");
				    printf("\n\t---------------------------------------------------------------------\n\n");
				    
				break;																			// ends case statement
				
		// executes "command #4" -> "instructions(4)" 
		case 4: puts(" How can we help you? "
					 	"\n\t [1] Register"
        			 	"\n\t [2] Login"
        			 	"\n\t [3] Exit");
				break;																			// ends case statement	
				
		// executes "command #5" -> "instructions(5)" 
		case 5: puts("\n\t [1] for VAN"	
					 "\n\t [2] for BUS"
				   	 "\n\t [3] to exit");
				break;																			// ends case statement
				
		// executes "command #6" -> "instructions(6)" 
		case 6:	printf("\n\t\t %-5s | %-15s \n", "POINT", "LOCATION");
				puts("\t\t----------------------");
				break;																			// ends case statement
				
		// executes "command #7" -> "instructions(7)" 
		case 7: puts("\n .....Please only indicate point(specified on the table):");
				break;																			// ends case statement
				
		// executes "command #8" -> "instructions(8)" 
		case 8:	puts("\n Do you wish to avail discounts ?" 
					"\n\t [1] Student 20% less"
					"\n\t [2] Senior Citizen 20% less"
					"\n\t [3] PWD 20% less"
					"\n\t [4] None of the above");
				break;																			// ends case statement
		
		// executes "command #0" -> "instructions(0)" 
	   default: printf("  *******************************************************\n");
				printf("  *\t\t\t\t\t\t        *\n");
				printf("  *\t\t  T  R  A  N  S  G  O\t\t        *\n");
			 	printf("  *\t    online transport fare system\t        *\n");
				printf("  *\t\t\t\t\t\t        *\n");
				printf("  *******************************************************\n\n");		
	}
}

// executes the main objective
int execute(int account, int counter)
{ 
	FILE *read, *out;		// File pointer
	MANUAL data[MAX];		// Structure type
	
	// Variable declarations
	int choice, offset, offset1, num_DATA, flag = 1, indicator;
		//    choice   -> variable storage when asking choice from user
		//    offset   -> variable used for loop
		//   offset1   -> variable used for loop
		//      flag   -> loop variable update "flag = 1" -> repeats loop and "flag = 0" -> end loop
		//  num_DATA   -> variable storage for number of points/ kilometers in input file
		// indicator   -> variable checker "indicator = 1" -> "VAN" and "indicator = 2" -> "BUS"
		
	system("CLS");														// clears terminal
	instructions(0);													// prints header
	printf("\n %s please enter vehicle type: ", users[account].name);	// prints instruction
	instructions(5);													// prints third set of choices
		printf(" enter chosen number: ");								// instruction to get the choice number of user
		scanf("%d", &choice);											// stores choice at variable "choice"
	
	// while loop that checks if "choice" on "instruction(5)" is satisfied
	while(flag == 1)
	{
		switch(choice)
		{ 
			// executes "command #1" -> "VAN" 
			case 1:	puts("\n************ online transport fare system VAN ************\n");
					indicator = 1;																	// checker "indicator" set as "1" or "VAN"
						read = fopen("VAN.txt", "rt");												// open input read pointer
	
					instructions(6);																// prints table header
						
					fscanf(read,"%i", &num_DATA);													// scans input file "VAN.txt" to know the number of points / kilometers
    				for (offset=0; offset < num_DATA; offset++)										// loop to read the rest of the contents of input file "VAN.txt"
					{ 					
        				fscanf(read, "%s", data[offset].location);						// stores at the variables of structure
        				printf("\t\t %-5d | %-15s\n", offset+1, data[offset].location);	// prints the scanned files
					}
					
					flag = 0;		// updates loop "flag = 0" -> ends loop
					break;			// ends case statement
					
			// executes "command #2" -> "BUS" 
			case 2:	puts("\n************ online transport fare system BUS ************\n");
					indicator = 2;																	// checker "indicator" set as "2" or "BUS"
						read = fopen("BUS.txt", "rt");												// open input read pointer
					
					instructions(6);																// prints table header
						
					fscanf(read,"%i", &num_DATA);													// scans input file "VAN.txt" to know the number of points / kilometers
    				for (offset=0; offset < num_DATA; offset++)										// loop to read the rest of the contents of input file "VAN.txt"
					{ 					
        				fscanf(read, "%s", data[offset].location);						// stores at the variables of structure
        				printf("\t\t %-5d | %-15s\n", offset+1, data[offset].location);	// prints the scanned files
					}
					
					flag = 0;		// updates loop "flag = 0" -> ends loop
					break;			// ends case statement
					
			// executes "command #3" -> "exit" 
			case 3: puts("\n\t >>>>>> THANK YOU FOR CHECKING OUR SERVICE.\n");			// prints footer
					return 0;															// terminates program
					
			// executes when user entered 1 > choice > 3
	   	  default:	system("CLS");														// clears terminal
	   	  			instructions(0);													// prints header
			 		puts(" >>>>>> invalid choice.");									// prints instruction
			 		printf("\n %s please enter vehicle type: ", users[account].name);	// prints imstruction
					instructions(5);													// prints third set of choices
					printf(" enter chosen number: ");									// instruction to get the choice number of user
					scanf("%d", &choice);												// stores choice at variable "choice"
					flag = 1;															// updates loop "flag = 1" -> repeats loop
		}
	}
	
	puts("\n <<<<<<<<< Kindly fill out the information below >>>>>>>>>");
	
	// Variable declaration
	int p1, p2;
		// p1 -> ORIGIN
		// p2 -> DESTINATION
	
		printf(" %17s (point):  ", "*ORIGIN");						// prints instruction to ask ORIGIN of client
			scanf("%d", &p1); 									// stores it in p1
				while(p1 < 1 || p1 > num_DATA)							// while loop to re-ask if entered value is 1 > p1 > num_DATA
				{
					instructions(7);									// prints instruction
					printf(" %17s (point):  ", "ORIGIN");					// prints instruction to ask ORIGIN of client
					scanf("%d", &p1);									// stores it in p1
				}
				
		printf(" %17s (point):  ", "*DESTINATION");				// prints instruction to ask DESTINATION of client
			scanf("%d", &p2); 									// stores it in p2
				while(p2 < 1 || p2 > num_DATA)							// while loop to re-ask if entered value is 1 > p2 > num_DATA
				{
					instructions(7);									// prints instruction
					printf(" %17s (point):  ", "*DESTINATION");			// prints instruction to ask DESTINATION of client
					scanf("%d", &p2);									// stores it in p2
				}
	
	system("CLS");							// clears terminal
	instructions(0);						// prints header
	
	float x = fare(p1,p2,0,indicator);											// computes fare 
		printf("\n %s your fare is PHP %.2f\n", users[account].name, x);		// prints computed fare
		instructions(8);														// prints 4th set of choices
	
	printf(" enter chosen number: ");											// instruction to get the choice number of user
	scanf("%d", &choice);														// stores choice at variable "choice"
	
	while(choice < 1 || choice > 4)												// while loop to repeat if 1 > choice > 4
	{
		system("CLS");															// clears terminal
		instructions(0);														// prints header
		
		printf("\n %s your fare is PHP %.2f\n", users[account].name, x);		// prints computed fare
		instructions(8);														// prints 4th set of choices
		printf(" enter chosen number: ");										// instruction to get the choice number of user
		scanf("%d", &choice);													// stores choice at variable "choice"
	}

		system("CLS");						// clears terminal
		instructions(0);					// prints header
			
	int opt;		// variable storage for choice
	// if choice is 1 or 2 or 3 computes for discount
	if(choice >= 1 && choice <= 3)			
	{
		float y = fare(p1,p2,choice, indicator);								// function call to compute discount and stores in variable y
		x = y;
		printf("\n %s your new fare is PHP %.2f\n", users[account].name ,y);	// prints discounted fare
	
		// loop that repeats to check if balance is sufficient
		float add_deposit;
		while(flag == 0)
		{
			// if insufficient
			if((users[account].balance - y) < 1)
			{	
				do 
				{
					printf(" ...... Insufficient balance. current balance is %.2f \n\t ***** Deposit cash to account? ", users[account].balance);	// instruct user
					printf("\n\t\t Press 1 if yes \n\t\t Press 2 if no \n\t ? ");			// ask users if wants to deposit or not
					scanf("%d", &opt);				// scans value and stores in opt
			
					system("CLS");					// clears terminal
					instructions(0);				// prints header
				}while(opt != 1 && opt != 2);		// repeats if value of opt is not satisfied
		
				// if yes
				if(opt == 1)
				{
					printf(" Enter cash deposit: PHP ");							// asks user to provide cash balance on account
					scanf("%f", &add_deposit);										// scans for additional balance and stores in variable add_deposit
					
					    while (add_deposit < 0)										// Validate the input
						{									
					        printf(" Please enter a positive amount: PHP ");
					        scanf("%f", &add_deposit);
					    }
    
					users[account].balance = users[account].balance + add_deposit;	// adds additional balance to current balance
				}
				
				// if no
				else
				{
					printf(" ...... You've unsuccesfully booked!");						
					printf("\n >>>>>> RESERVATION  CANCELLED");	
			
					puts("\n\n\t >>>>>> THANK YOU FOR CHECKING OUR SERVICE.\n");	// prints footer
					return 0;
				}	
				flag = 0;		// repeats while loop
			}
			
			// if sufficient
			else 
				flag = 1;		// exits while loop
		}
		
		do
		{	
			printf(" >>>>>> %s your current account balance is PHP %.2f deducted by computed fare %.2f\n", users[account].name, users[account].balance, y);		// shows user the computed fare and current ammount balance 
			printf(" ------ Do you wish to continue? \n\t Press 1 if yes \n\t Press 2 if no \n\t ? ");			// ask users to continue availing ticket		
			scanf("%d", &opt);				// scans value and stores in opt
			
			system("CLS");					// clears terminal
			instructions(0);				// prints header
		}while(opt != 1 && opt != 2);		// repeats if value of opt is not satisfied
		
		if(opt == 1)
		{
			users[account].balance = users[account].balance - y;															// deducts the computed fare on current ammount balance
			printf(" >>>>>> %s your current account balance is PHP %.2f \n", users[account].name, users[account].balance);	// displays the new cash amount balance
			printf(" ...... You've succesfully booked! Your ticket is to be printed on \"ticket.txt\" ");
		}
		else
			printf("\n >>>>>> RESERVATION  CANCELLED");			
	}
	
	// if choice is 4 no discount
	else
	{	
		printf("\n %s your fare is PHP %.2f\n", users[account].name, x);			// prints Undiscounted fare
		
		float add_deposit;
		// loop that repeats to check if balance is sufficient
		while(flag == 0)
		{
			// if insufficient
			if((users[account].balance - x) < 1)
			{	
				do 
				{
					printf(" ...... Insufficient balance. current balance is %.2f \n\t ***** Deposit cash to account? ", users[account].balance);	// instruct user
					printf("\n\t\t Press 1 if yes \n\t\t Press 2 if no \n\t ? ");			// ask users if wants to deposit or not
					scanf("%d", &opt);				// scans value and stores in opt
			
					system("CLS");					// clears terminal
					instructions(0);				// prints header
				}while(opt != 1 && opt != 2);		// repeats if value of opt is not satisfied
		
				// if yes
				if(opt == 1)
				{
					printf(" Enter cash deposit: PHP ");							// asks user to provide cash balance on account
					scanf("%f", &add_deposit);										// scans for additional balance and stores in variable add deposit
					
						while (add_deposit < 0)										 // Validate the input
						{									
					        printf(" Please enter a positive amount: PHP ");
					        scanf("%f", &add_deposit);
					    }
					    
					users[account].balance = users[account].balance + add_deposit;	// adds additional balance to current balance
				}
				
				// if no
				else
				{
					printf(" ...... You've unsuccesfully booked!");						
					printf("\n >>>>>> RESERVATION  CANCELLED");	
			
					puts("\n\n\t >>>>>> THANK YOU FOR CHECKING OUR SERVICE.\n");	// prints footer
					return 0;
				}	
				flag = 0;		// repeats while loop
			}
			
			// if sufficient
			else 
				flag = 1;		// exits while loop
		}
		
		do
		{	
			printf(" >>>>>> %s your current account balance is PHP %.2f deducted by computed fare %.2f\n", users[account].name, users[account].balance, x);		// shows user the computed fare and current ammount balance 
			printf(" ------ Do you wish to continue? \n\t Press 1 if yes \n\t Press 2 if no \n\t ? ");			// ask users to continue availing ticket		
			scanf("%d", &opt);				// scans value and stores in opt
			
			system("CLS");					// clears terminal
			instructions(0);				// prints header
		}while(opt != 1 && opt != 2);		// repeats if value of opt is not satisfied
		
		if(opt == 1)
		{
			users[account].balance = users[account].balance - x;																// deducts the computed fare on current ammount balance
			printf(" >>>>>> %s your current account balance is PHP %.2f \n", users[account].name, users[account].balance);		// displays the new cash amount balance
			printf(" ...... You've succesfully booked! Your ticket is to be printed on \"ticket.txt\" ");						
		}
		else	
			printf("\n >>>>>> RESERVATION  CANCELLED");
	}
	
	puts("\n\n\t >>>>>> THANK YOU FOR CHECKING OUR SERVICE.\n");		// prints footer
	
	out = fopen("account.txt", "wt");		// opens input write pointer
		fprintf(out,"%d\n", counter);		// prints on file the current amount of user
			int j;							// variable for loop
			for(j = 0; j < counter; j++)	// loops to print the account information
				fprintf(out,"%s %s %d %.2f\n", users[j].name, users[j].password, users[j].accountNumber, users[j].balance);	
		
	if(opt == 1)
	{
		offset1 = array_sub(0, p1, indicator);
		offset  = array_sub(1, p2, indicator);
		
		out = fopen("ticket.txt", "wt");		// open input write pointer
		
		int i;
		for(i = 0; i < 53; i ++)
			fprintf(out,"-");
			fprintf(out,"\n> > > > >  %20s  < < < < <\n", "T    R    A    N    S    G    O");
		for(i = 0; i < 53; i ++)
			fprintf(out,"-");
			
		// prints ticket if type of vehicle is VAN
		if(indicator == 1)
		{
			fprintf(out,"\n %29s: %s \n %29s: %d \n", "Passenger", users[account].name, "Account number", users[account].accountNumber);	
			fprintf(out," %29s: VAN", "Vehicle reservation");
			fprintf(out,"\n %29s: %s \n %29s: %s \n %29s: %.2f\n", "Origin", data[offset1].location, "Destination", data[offset].location, "FARE", x);		
		}
	
		// prints ticket if type of vehicle is BUS
		else
		{
			fprintf(out,"\n %29s: %s \n %29s: %d \n", "Passenger", users[account].name, "Account number", users[account].accountNumber);	
			fprintf(out," %29s: BUS", "Vehicle reservation");
			fprintf(out,"\n %29s: %s \n %29s: %s \n %29s: %.2f\n", "Origin", data[offset1].location, "Destination", data[offset].location, "FARE", x);	
		}
		
		for(i = 0; i < 53; i ++)
			fprintf(out,"-");
	}
	
	fclose(read), (out);	//close input read and write pointer			
	return 0;												
}

// counts the fare of client
float fare(int ORIGIN, int DESTINATION, int DISCOUNT, int vehicle)
{
	// Variable declarations
	int distance;
	float fare, discounted_fare;
	
	// course of action without discount
	if(DISCOUNT == 0)
	{
		// initialized the value of distance
		distance = ORIGIN - DESTINATION;
		
		// if "distance = 0 or minimum distance" returns the corresponding minimum fare
		if(distance == 0)
		{
			// "vehicle = 1" or VAN
			if(vehicle == 1)
				return 120;
				
			// "vehicle = 0" or BUS
			else 
				return 10;
		}
		
		// if "distance is more than minimum distance" returns the corresponding fare
		else
		{
			// "vehicle = 1" or VAN
			if(vehicle == 1)
				return fare = (abs(distance))* 120;
			
			// "vehicle = 0" or BUS
			else 
				return fare = (abs(distance) +1)* 10;
		}
	}
	
	// course of action if discount is to be applied
	else
	{
		// initialized the value of distance
		distance = ORIGIN - DESTINATION;
		
		// if "distance = 0 or minimum distance" returns the corresponding minimum fare
		if(distance == 0)
		{
			// "vehicle = 1" or VAN
			if(vehicle == 1)
			{
				discounted_fare = ((120) * (.20)) - 120;
				return discounted_fare = abs(discounted_fare);;
			}
			
			// "vehicle = 0" or BUS
			else 
			{
				discounted_fare = ((10) * (.20)) - 10;
				return discounted_fare = abs(discounted_fare);;
			}
		}
		
		// if "distance is more than minimum distance" returns the corresponding fare
		else
		{
			// "vehicle = 1" or VAN
			if(vehicle == 1)
			{
				distance = abs(distance);
				fare = (distance) * 120;
				discounted_fare = (fare* .20) - fare;
		
				return discounted_fare = abs(discounted_fare);;
			}
			
			// "vehicle = 0" or BUS
			else 
			{
				distance = abs(distance);
				fare = (distance+1) * 10;
				discounted_fare = (fare* .20) - fare;
		
				return discounted_fare = abs(discounted_fare);;
			}
		}
	}
}

// Function to register a new user
int registerUser(int counter) 
{
    printf(" REGISTER\n Enter your name: ");								// asks name of user
    scanf("%s", users[counter].name);										// scans value and store in structure user member name

    printf(" Enter your password: ");										// asks password of user
    scanf("%s", users[counter].password);									// scans value and store in structure user member password

	printf(" Enter cash deposit: PHP ");									// asks user to provide cash balance on account
	scanf("%f", &users[counter].balance);									// scans value and stores in structure user member balance
	
	    
    while (users[counter].balance < 0)										 // Validate the input
	{									
        printf(" Please enter a positive amount: PHP ");
        scanf("%f", &users[counter].balance);
    }
	
    users[counter].accountNumber = 1000 + counter; 							// Generate unique account number
	
	system("CLS");															// clears terminal	// prints header	
	instructions(0);														// prints header
    printf("\n Registration successful!\n");								// prints message
    printf(" Your account number is: %d\n", users[counter].accountNumber);	// prints message

    login(counter+1);														// calls fucnction login to check user
}

// Function to log in a user
int login(int counter) 
{
	// Variable declarations
    int accountNumber, i, j;
    char password[20];
    	// accountnumber -> storage of account number to be checked for successful login
    	//      password -> storage of password to be checked for successful login
    	//             i -> offset
	
    printf(" LOGIN\n Enter your account number: ");							// asks for account number to be checked for succesful login			
    scanf("%d", &accountNumber);											// stores in accountnumber

    printf(" Enter your password: ");										// asks for password to be checked for succesful login
    scanf("%s", password);													// stores in password
	
	// if numUser is zero account has not been made yet
	if(counter == 0)							
	{
		system("CLS");														// clears terminal
		instructions(0);													// prints header
		puts(" >>>>>> Account is not registered yet, "
				"first get your account number in registration");			// prints instruction
		registerUser(counter);												// calls registerUser function 
	}
	
	// account has been made
	else
	{
		// loop to check user account 
		for (i = 0; i < counter; i++) 
			if (users[i].accountNumber == accountNumber && strcmp(users[i].password, password) == 0) 		// checks if password and account number inputed are on account record
			{
				FILE *out;								// FILE pointer
					out = fopen("account.txt", "wt");	// open input write pointer
	
					fprintf(out,"%d\n", counter);		// outputs on file the current number of account registered
					for(j = 0; j < counter; j++)		// loops to print the account information on file
						fprintf(out,"%s %s %d %.2f\n", users[j].name, users[j].password, users[j].accountNumber, users[j].balance);
				
				fclose (out);			// close input write pointer
				
				puts("\t\t    W  E  L  C  O  M  E\n  ************ online transport fare system ************\n");
				execute(i, counter);	// function call to execute main objective
							
				return 1;				// returns to main function 
			}

		system("CLS");																	// clears terminal	
		instructions(0);																// prints header
    	printf(" >>>>>> invalid account number or password. Please try again.\n");		// prints instruction
    	login(counter);																	// recall itself if login information is wrong
	}
}

int array_sub(int checker, int location, int vehicle_type)
{
	int offset, offset1;
	if(checker == 0)
	{
		if(vehicle_type == 1)
			switch(location)
			{
				case 1:	offset1 = 0;			
						break;
				case 2: offset1 = 1;	
						break;
				case 3: offset1 = 2;
						break;
			   default: offset1 = 3;
			}
		else
			switch(location)
			{
				case 1:	offset1 = 0;
						break;
				case 2:	offset1 = 1;
						break;
				case 3:	offset1 = 2;
						break;
				case 4:	offset1 = 3;
						break;
				case 5:	offset1 = 4;
						break;
				case 6:	offset1 = 5;
						break;
				case 7:	offset1 = 6;
						break;
				case 8:	offset1 = 7;
						break;
				case 9:	offset1 = 8;
						break;
			   default:	offset1 = 9;
			}
		return offset1;
	}
	else
	{
		if(vehicle_type == 1)
			switch(location)
			{
				case 1:	offset = 0;			
						break;
				case 2: offset = 1;	
						break;
				case 3: offset = 2;
						break;
			   default: offset = 3;
			}
		else
			switch(location)
			{
				case 1:	offset = 0;
						break;
				case 2:	offset = 1;
						break;
				case 3:	offset = 2;
						break;
				case 4:	offset = 3;
						break;
				case 5:	offset = 4;
						break;
				case 6:	offset = 5;
						break;
				case 7:	offset = 6;
						break;
				case 8:	offset = 7;
						break;
				case 9:	offset = 8;
						break;
			   default:	offset = 9;
			}
		return offset;
	}
}
