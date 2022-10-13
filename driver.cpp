/*
 * Author: Greg Shenefelt
 * Date: 10/10/2022
 * Class: CS 260 Data Structures
 * Program #1
 * file name: driver.cpp the implementation file for driver.h
 * This module is responsible for allowing the client to interact with the
 * ADT list
 * This program is an interactive menu style program that allows you to
 * manage a list of songs.
 * This allows us to display all songs in the list sorted by likes, allows
 * us to display all songs in the list by a given artist sorted by likes,
 * allows us to add a new song to our list, allows us to update the number
 * of likes of a given song, and allows us to remove songs that have less
 * than a given number of likes.
 */

#include "driver.h"
#include "songList.h"
#include "song.h"


/*
 * the get input function allows us to read in dynamic cstrings from the user
 * INPUT: char *& chars - a pointer that will be used to store the input
 * from the user
 */
void getInput(char *& chars) {
    char *input = nullptr; // store the input from input stream
    char *temp = nullptr; // store a temp copy of the input each time input
    // grows
    int wordSize = 0; // the size of the word we got from input

    while (cin.good() && cin.peek() != EOF) {
        char letter = cin.get(); // grabs the current character in the input

        if (letter == '\n') {
            break;
        }

        if (!input) {
            input = new char[2];
            input[0] = letter;
            input[1] = '\0';
            wordSize = 1;
        } else {
            wordSize = strlen(input);
            // +2 so we can get the letter plus have enough space to append
            // cstrings null node terminator to the end.
            temp = new char[wordSize + 2]{0};
            strcpy(temp, input);
            delete[]input;
            input = temp;
            input[wordSize] = letter;
            input[wordSize + 1] = '\0';
        }

    }


    chars = new char[strlen(input) + 1];
    // copy the users input into the passed in pointer.
    strcpy(chars, input);
    // get rid of our dynamic input pointer.
    delete[]input;
}

/*
 * Get integers from the input stream in a validated way. This method
 * ensures valid input, or requires the user to keep entering until input is
 * valid
 *
 * OUTPUT: a number entered by the user into the input stream.
 */
int getInteger()
{
    int numberIn; // store the number entered by the user.
    cin >> numberIn;

    while(cin.fail())
    {
        cin.clear();
        cin.ignore(101,'\n');
        cerr << "Please enter a whole number as input (EX 100 or 125)" << endl;
        cout << "Please renter your number: ";
        cin >> numberIn;
    }

    cin.ignore(101,'\n');

    return numberIn;
}


/*
 * Interactive menu for the application, calls list operations based on user
 * input.
 */
void menu(songList &list)
{
    int option = 0; // store the current menu choice
    int likesToRemove; // store the number of likes we wish to remove
    int likesToEdit; // the number of likes to update a song too.
    int totalMatches = 0; // the number of songs that match a given search
    char * artistName = nullptr; // the name of an artist
    char * songTitle = nullptr; // the title of a song
    song newSong; // a new song that will be added to our list.

    while(option != 6)
    {

        cout << endl;
        cout << "Menu: \n"
             << "\t1. Print List \n"
             << "\t2. Print Songs By an Artist \n"
             << "\t3. Add a new song to the list \n"
             << "\t4. Remove songs with less than a given number of likes \n"
             << "\t5. Edit the number of likes for a song\n"
             << "\t6. Quit the application\n"
             << endl << endl;
        cout << "Enter an option: ";
        option = getInteger();

        switch(option)
        {
            case 1:
                if(list.isEmpty())
                {
                    cout << "The list is empty! " << endl;
                }
                else
                {
                    list.printList(list);
                }
                break;
            case 2:
                cout << "Enter an artist name to display: ";
                getInput(artistName);
                if(list.printByArtist(artistName))
                {
                    cout << "There are no songs by artist " << artistName <<
                    " in the list" << endl;
                }
                delete []artistName;
                break;
            case 3:
                newSong = getSongInfo();
                list.insert(newSong);
                break;
            case 4:
               cout << "Enter the number of likes you'd like to delete: ";
               likesToRemove = getInteger();
               totalMatches = list.getFrequency(likesToRemove);
                if(list.removeByLikes(likesToRemove))
               {
                   cout << "[ " << totalMatches << " ] songs removed from "
                                                   "the list " << endl;
               }
                else
                {
                    cout << "There were no songs with less than " <<
                    likesToRemove << " likes in the list" << endl;
                }
                break;
            case 5:
                cout << "Enter the title of the song you wish to edit: ";
                getInput(songTitle);
                if(list.findSongTitle(songTitle))
                {
                    cout << "No songs with the title " << songTitle
                         << " were found in the list " << endl;
                }
                else
                {
                    cout << "Enter the number of likes you'd like to set the "
                            "song to (EX 350): ";
                    likesToEdit = getInteger();

                    if(list.editLikes(likesToEdit, songTitle))
                    {
                        cout << "Changed " << songTitle << " likes to: "
                             << likesToEdit << endl;
                    }
                }
                delete []songTitle;
                break;
            case 6:
                break;
            default:
                cerr << option << " is an invalid menu choice" << endl;
                cout << endl;
        }
    }

}


/*
 * gets user inputs to set up the data about a song.
 * @return the new song object created from the inputs.
 * */
song getSongInfo()
{
    song newSong; // the new song we will add
    char * artistName = nullptr; // the artist of the new song
    char * songTitle = nullptr; // the title of the new song
    int  likes; // the number of likes for the new song
    int  length; // the length of the new song
    cout << "Enter the artist of this songs name: ";
    getInput(artistName);
    cout << "Enter the title for this song: ";
    getInput(songTitle);
    cout << "Enter the number of likes for this song: ";
    likes = getInteger();
    cout << "Please enter the length of this song: ";
    length = getInteger();
    newSong.setArtist(artistName);
    newSong.setTitle(songTitle);
    newSong.setNumberOfLikes(likes);
    newSong.setLength(length);


    delete []artistName;
    delete []songTitle;

    return newSong;
}



int main()
{
    cout << "Welcome to the song list database. " << endl << endl;
    songList list; // the list of songs
    char filename[] = "roster.txt"; // the name of the file to load.
    int totalLoaded = list.loadFromFile(filename); // the number of songs
    // loaded from the file.

    if(totalLoaded > 0)
    {
        cout << "[ " << totalLoaded << " ] songs loaded from " << "[ " <<
        filename
        << " ]" << endl;
    }
    else
    {
        cout << "Either the file is empty, or there was an error reading the"
                " file " << filename << endl;
    }

    menu(list);
    cout << "*** [ done ] ***" << endl;
    return 0;


}
