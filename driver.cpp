#include "driver.h"



void getInput(char *& chars)
{
    // do dynamic grabbing here.
}

int menu(songList &list)
{
    char option;
    char * artistName = nullptr;
    song newSong;
    songList unsortedList;

    cout << "Enter a menu option: ";
    cin.getline(&option, 101);

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
            newSong = getSongInfo();
            unsortedList.append(newSong);
            break;
        default:
            cout << "invalid input, please try again " << endl;
    }
}

song getSongInfo()
{
    song newSong;
    char * artistName = nullptr;
    char * songTitle = nullptr;
    int likes;
    float length;
    cout << "Enter the artist of this songs name: ";
    getInput(artistName);
    cout << "Enter the title for this song: ";
    getInput(songTitle);
    cout << "Enter the number of likes for this song: ";
    cin >> likes;
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(101,'\n');
        cout << "ERR invalid input please enter a number of likes (EX: 100) " << endl;
        cout << "Enter number of likes for this song: ";
        cin >> likes;
    }
    cin.ignore(101,'\n');
    cout << "Please enter the length of this song: ";
    cin >> length;
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(101,'\n');
        cout << "Please enter length as a number for this song (EX:4.50) " << endl;
        cout << "Enter length of this song: ";
        cin >> length;
    }
    cin.ignore(101,'\n');
    newSong.setArtist(artistName);
    newSong.setTitle(songTitle);
    newSong.setNumberOfLikes(likes);
    newSong.setLength(length);

    return newSong;
}

int main()
{
    cout << "Welcome to the song list database. " << endl;
    while(menu() != 'Q')
    {
        menu();
    }


}
