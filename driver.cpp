#include "driver.h"



void getInput(char *& chars)
{
    // do dynamic grabbing here.
}

int menu(songList &list)
{
    char option;
    char * artistName = nullptr;
    char * title = nullptr;
    song newSong;
    int likes;
    float length;

    songList unsortedList;
    cout << "Enter a menu option: ";
    cin >> option;
    cin.ignore(101,'n');

    switch(option)
    {
        case 1:
            unsortedList.printList();
            break;
        case 2:
            cout << "Enter an artist name to display: ";
            getInput(artistName);
            unsortedList.printByArtist(artistName);
            delete []artistName;
            break;
        case 3:
	    unsortedList.append(newSong);
	    cout << "Enter an artist name: ";
	    getInput(artistName);
	    cout << "Enter a title for the song: ";
	    getInput(title);
	    cout << "Enter a number of likes for this song: ";
	    while(!cin >> likes)
	    {
		    cout << "Error please enter a whole number for likes" << endl;
		    cin.ignore(101, '\n');
		    cin >> likes;
		    cin.ignore(101,'\n');
	    }
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
