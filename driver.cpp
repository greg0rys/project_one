#include "driver.h"
#include "songList.h"
#include "song.h"



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
    int option;
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
                cout << "Remove less than m likes" << endl;
            default:
                cout << "invalid input, please try again " << endl;
        }
    }

}

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

	delete []artistName;
	delete []songTitle;
    return newSong;
}


void loadFromFile(char filename[], songList &list)
{
    ifstream file(filename);
    song currentSong;
    const int MAX_CHAR = 101;
    char artistName[MAX_CHAR];
    char title[MAX_CHAR];
    int likes;
    int length;


    if(!file)
    {
        cerr << "Failed to open " << filename << " for reading" << endl;
        return;
    }
    else
    {
        cout << filename << " is open";
    }
    file.get(artistName, MAX_CHAR, ';');

    while(!file.eof())
    {
        file.get(); // extract delm from the stream
        file.get(title, MAX_CHAR, ';');
        file >> likes;
        file.ignore(MAX_CHAR, ';');
        file >> length;
        file.ignore(MAX_CHAR, '\n');

        currentSong.setArtist(artistName);
        currentSong.setTitle(title);
        currentSong.setNumberOfLikes(likes);
        currentSong.setLength(length);
        list.insert(currentSong);
        file.get(artistName, MAX_CHAR, ';');
    }

    file.close();

}

int main()
{
    cout << "Welcome to the song list database. " << endl;
    songList list;
    char filename[]="songs.txt\0";
    ifstream in(filename);

    if(!in)
    {
        cout << filename << " error";
        exit(0);
    }

    loadFromFile(filename,list);

    menu(list);


}
