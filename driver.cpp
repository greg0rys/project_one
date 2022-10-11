#include "driver.h"
#include "songList.h"
#include "song.h"


/*
 * the get input function allows us to read in dynamic cstrings from the user
 * INPUT: char *& chars - a pointer that will be used to store the input
 * from the user
 */
void getInput(char *& chars) {
    char *input = nullptr;
    char *temp = nullptr;
    int wordSize = 0;

    while (cin.good() && cin.peek() != EOF) {
        char letter = cin.get();

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

void menu(songList &list)
{
    int option = 0;
    int likesToRemove;
    char * artistName = nullptr;
    song newSong;

    while(option != 5)
    {

        cout << "Menu: \n"
             << "\t1. Print List \n"
             << "\t2. Print Songs By an Artist \n"
             << "\t3. Add a new song to the list \n"
             << "\t4. Remove songs with less than a given number of likes \n"
             << "\t5. Quit\n"
             << endl << endl;
        cout << "Enter an option: ";
        cin >> option;
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(101,'\n');

            cout << "ERR please enter the number of your menu choice: "
                 << "(EX 1"
                    " to print the list) "
                 << endl;
            cout << "Please enter a menu choice: ";
            cin >> option;
        }
        cin.ignore(101,'\n');

        switch(option)
        {
            case 1:
                list.printList(list);
                break;
            case 2:
                cout << "Enter an artist name to display: ";
                getInput(artistName);
                list.printByArtist(artistName);
                delete []artistName;
                break;
            case 3:
                newSong = getSongInfo();
                list.insert(newSong);
                break;
            case 4:
               cout << "Enter the number of likes you'd like to delete: ";
               cin >> likesToRemove;

               if(cin.fail())
               {
                   cin.clear();
                   cin.ignore(101,'\n');
                   cerr << "Please enter a number of likes (EX 100 or 225)"
                   << endl;
                   cout << "Please reinput the number of likes: ";
                   cin >> likesToRemove;
               }
               cin.ignore(101,'\n');
               list.removeByLikes(likesToRemove);
            case 5:
                break;
            default:
                cout << "invalid input, please try again " << endl;
        }
    }

}


/*
 * gets user inputs to set up the data about a song.
 * @return the new song object created from the inputs.
 * */
song getSongInfo()
{
    song newSong;
    char * artistName = nullptr;
    char * songTitle = nullptr;
    int  likes;
    int  length;
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
        cout << "ERR invalid input please enter a number of likes (EX: 100) "
             << endl;
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
        cout << "Please enter length as a number for this song (EX:4.50) "
             << endl;
        cout << "Enter length of this song: ";
        cin >> length;
    }
    cin.ignore(101,'\n');
    newSong.setArtist(artistName);
    newSong.setTitle(songTitle);
    newSong.setNumberOfLikes(likes);
    newSong.setLength(length);


    delete []artistName;
    delete []songTitle;

    return newSong;
}


void loadFromFile(const char * filename, songList &list)
{
    fstream file(filename);
    song currentSong;
    const int MAX_CHAR = 101;
    char artistName[MAX_CHAR];
    char title[MAX_CHAR];
    int likes;
    int length;


    if(!file)
    {
        cerr << "Failed to open " << filename << " for reading" << endl;
        return; // allow program to continue without the file data.
    }

    file.get(artistName, MAX_CHAR, ';');

    while(!file.eof())
    {
        file.get();
        file.get(title, MAX_CHAR, ';');
        file.get();
        file >> likes;
        file.ignore(MAX_CHAR, ';');
        file >> length;
        file.ignore(MAX_CHAR, '\n');

        song tempSong(artistName,title,length,likes);
        cout << tempSong;
        list.insert(tempSong);
        file.get(artistName, MAX_CHAR, ';');
    }

    file.close();

}

int main()
{
    cout << "Welcome to the song list database. " << endl;
    songList list;
    char filename[] = "roster.txt";
    loadFromFile(filename,list);
    menu(list);
    return 0;


}
