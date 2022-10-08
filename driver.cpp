#include "driver.h"



void getInput(char *& chars)
{
    // do dynamic grabbing here.
}

int menu(songList &list)
{
    char option;
    char * artistName = nullptr;
    cout << "Enter a menu option: ";
    cin >> option;
    cin.ignore(101,'n');

    switch(option)
    {
        case '1':
            list.printList();
            break;
        case 2:
            cout << "Enter an artist name to display: ";
            getInput(artistName);
            list.printByArtist(artistName);
            delete []artistName;
            break;
        case 3:
            break;
        default:
            cout << "invalid input, please try again " << endl;
    }
}

int main()
{
    cout << "Welcome to the song list database. " << endl;
    while(menu() != 'Q')
    {
        menu();
    }


}
