#include "driver.h"

int main()
{
    cout << "Welcome to the song list database. " << endl;
   while(menu() != 'Q')
   {
	   menu();
   }


}

void getInput(char *& chars)
{
    // do dynamic grabbing here.
}

int menu()
{
    char option;
    switch(option)
    {
        case 'D':
            break;
        default:
            cout << "invalid input, please try again " << endl;
    }
}
