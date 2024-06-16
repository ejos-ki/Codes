           // LATORRE, JEO D :: BSCS 2C 
// Data Structures and Algorithm || Machine Exercise 1
#include <iostream>             // cout, cin
#include <cstdlib>              // rand(), srand()
#include <ctime>                // time()
#include <cctype>               // toupper
#include <algorithm>            // transform()
using namespace std;

//function prototypes
void prompt(int part);
int checker(string specific[], int instruct, int rndm, int iteration, int subscript);
int YorN(void);

int main()
{
    //variable declarations and initializations
    string type[] = {"CLUBS", "SPADES", "HEARTS", "DIAMONDS"},
           rank[] = {"ACE", "2", "3", "4", "5", "6", "7", "8", "9", "10", "JACK", "QUEEN", "KING"};
    int repeat, rand1, rand2, win;

    do                              // loop for game repetion
    {
        system("cls");
        cout << "\n\t\t\t      ~ LET US PLAY ~\n\n";
        repeat = 0;                 // Variable checker for loop repetion
        srand(time(0));             // function to support rand function
        
        rand1 = rand() % 4;                           // getting random number as index for array "type"
        	win = checker(type, 1, rand1, 2, 4);      // function call for type
        rand2 = rand() % 13; 						  // getting random number as index for array "rank"
		
        if(win == 1)
        	cout << "\n\t\t ~ The card type is " << type[rand1];
		else
		    cout << "\n\t\t ~ The card type is " << rank[rand2] << " of " << type[rand1];
		
		repeat = YorN();   
		
        if(repeat == 1 && win == 1)
        {
             win = checker(rank, 2, rand2, 3, 13);     // function call for rank

        	cout << "\n\t\t ~ The card type is " << rank[rand2] << " of " << type[rand1];
            repeat = YorN();
        }
    } while (repeat == 1);
    return 0;
}

void prompt(int part)
{
    switch(part)
    {
        case 1: cout << "\n\t   Can you guess my card?"                   // question for player
                     << " (CLUBS, SPADES, HEARTS, DIAMONDS)\n"
                     << "\t\t   What is the type of my card? ";
                break;
        case 2: cout << "\n   Can you guess my card?"                  // question for player
                     << " (ACE, 2, 3, 4, 5, 6, 7, 8, 9, 10, JACK, QUEEN, KING)\n"
                     << "\t\t   What is the rank of my card? ";  
                break;
        case 3: cout << "\n\t\t\t      ~ You win ~\n\n";
                break;
        case 4: cout << "\n\t\t      ~ The card type is higher ~\n\n";
                break;
        case 5: cout << "\n\t\t       ~ The card type is lower ~\n\n";
                break;
        case 6: cout << "\n\t\t          ~ You  loss ~\n\n"; 
                break;
       default: for(int i = 0; i < 81; i++)                            // design
                    cout << "_";
    }
}

int checker (string specific[], int instruct, int rndm, int iteration, int subscript)
{
    string guess;
    int counter, repeat = 0;

    do                             //loop repetion on guessing the type of card
        {
            prompt(0);             // function call for instruction 1
            prompt(instruct);      // function call for instruction 2
                cin >> guess;      // storage of the answer of player
            prompt(0);             // function call for instruction 1            
        
            transform(guess.begin(), guess.end(), guess.begin(), ::toupper);         // converts "guess" to uppercase
        
            if(specific[rndm].compare(guess) == 0)              // if answer of player is correct
            {
                prompt(3);                                      // function call for instruction 3        
                return 1;
            }
            else                                                // if answer of player is false
            {
                if(repeat < iteration - 1)                          // checks if loop exceeds 2 iteration
                    for(int i = 0; i < subscript; i++)          // loop to search for array member
                    {   if(specific[i].compare(guess) == 0)     // checks the position of guess of player on array
                        {    
                            if( i < rndm)
                                prompt(4);                      // function call for instruction 5
                            else 
                                prompt(5);                      // function call for instruction 6
                        }
                    }
                else 
                    prompt(6);              // function call for instruction 7
                
                repeat += 1;
                counter = 1;
            }
        } while (repeat < iteration && counter == 1);
        return 0;
}

int YorN(void)
{
    char choice;

    for(int i = 1; ; i++)
    {
        cout << "\n\t <<<< Do you wish to continue playing? (y/n)";
        cin >> choice;

        if(choice == 'y' || choice == 'Y')
            return 1;
        else if(choice == 'n' || choice == 'N')
            return 0;
    }
}
