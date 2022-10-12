#include "songList.h"

/*
 * default constructor
 */
songList::songList(): index(nullptr), tail(nullptr), size(0)
{}

/*
 * copy constructor
 */
songList::songList(const songList &source):index(nullptr), tail(nullptr),
size(0)
{
    *this = source;
}

/*
 * class destructor
 */
songList::~songList()
{
    destroy();
}

/*
 * deallocates the pointers for the class and sets them to nullptr
 */
void songList::destroy()
{
    node * curr = index;
    while(curr)
    {
        index = curr->next;
        delete curr;
        curr = index;
    }

    index = nullptr;
    size = 0;
}

/*
 * insert a new song into the list
 * INPUT aSong a reference to a song object
 */
bool songList::insert(const song &aSong)
{
    node * curr = index;
    node * newNode = new node(aSong);

    if(!index)
    {
        index = newNode;
        tail = newNode;
    }
    else
    {
        delete newNode;
        append(aSong);
    }
}

/*
 * append a new song to the end of the list
 * INPUT: aSong a reference to a song object
 */
void songList::append(const song &aSong)
{
    node * newNode = new node(aSong);


    if(!index)
    {
        index = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;

}

/*
 * Get a given artist node from the list
 * INPUT: artName a pointer containing the artist name
 * OUTPUT: node * a pointer to the located node.
 */
songList::node* songList::getArtistAt(const char * artName)
{
    node * curr = index;
    char * artistName = nullptr;
    while(curr)
    {
        curr->data->getArtist(artistName);
        if(strcmp(artistName,artName) == 0)
        {
            break;
        }
        curr = curr->next;
    }

    return curr;
}

/*
 * Get a given song node from the list based on song title
 * INPUT: songName a pointer containing the songs name
 * OUTPUT: node * a pointer to the located node.
 */
songList::node* songList::getSongAt(const char * songName)
{
    node * curr = index;
    char * currentSongName = nullptr;

    while(curr)
    {
        if(currentSongName)
            delete []currentSongName;

        curr->data->getTitle(currentSongName);
        if(strcmp(songName, currentSongName) == 0)
        {
            break;
        }
        curr = curr->next;
    }

    return curr;
}

/*
 * @param likes the number of likes the user would like to change too.
 * @param name the name of the song the user wants to edit.
 * @return success true if likes were updated false if else.
 */
bool songList::editLikes(int likes, const char * name)
{
    node * nodeToEdit = getSongAt(name);
    song songToEdit;
    bool success = false;

    if(nodeToEdit)
    {
        songToEdit = *(nodeToEdit->data);
        songToEdit.setNumberOfLikes(likes);
        success = true;
    }

    return success;
}

/*
 * print all of the songs in our list (unsorted)
 * INPUT list a reference to a list
 */
void songList::printList(const songList &list)
{

    if(isEmpty())
        cout << "The list is empty!" << endl;
    else
        cout << list;
}

/*
 * print songs in the list for a given artist sorted by likes.
 * INPUT: artName a pointer containing the artist name we wish to print
 */
bool songList::printByArtist(const char * artName)
{
    songList sortedList;
    song tempSong;
    node * curr = index;
    char * currentArtist = nullptr;

    while(curr)
    {
        if(currentArtist)
            delete []currentArtist;

        currentArtist = new char[curr->data->getArtistNameLength() + 1];
        curr->data->getArtist(currentArtist);

        if(strcmp(currentArtist, artName) == 0)
        {

                tempSong = *(curr->data);
                sortedList.insertSorted(tempSong);
        }

        curr = curr->next;
    }

    cout << sortedList << endl;

    if(currentArtist)
        delete []currentArtist;

    return (sortedList.index == nullptr);

}

/*
 * Check to see if the list is empty
 * returns true if the list is empty false if else.
 */
bool songList::isEmpty()
{
    return (index == nullptr);
}

/*
 * insert a new song to the list sorted by likes
 * INPUT aSong a reference to a song object
 */
void songList::insertSorted(const song & aSong)
{

    node * newNode = new node(aSong);
    node * curr = index;

    if(!index)
    {
        index = newNode;
    }
    else if(index->data->getLikes() <= aSong.getLikes())
    {
        newNode->next = index;
        newNode->next->prev = newNode;
        index = newNode;
    }
    else
    {
        while(curr->next && curr->next->data->getLikes() > aSong.getLikes())
        {
            curr = curr->next;
        }
        newNode->next = curr->next;

        if(curr->next)
        {
            newNode->next->prev = newNode;
        }

        curr->next = newNode;
        newNode->prev = curr;
    }

}


/*
 * remove a song from the list based on the number of likes it has
 * INPUT target an integer containing the number of likes we wish to delete
 * returns true if able to remove the node else returns false.
 */
bool songList::removeByLikes(const int target)
{
    node * curr = index;
    node * next = nullptr;
    int counter = 0;

    if(!index)
        return false;


    while(curr)
    {
        if(curr->data->getLikes() < target)
        {
            next = curr->next;
            if(remove(curr))
                counter++;
            curr = next;
        }
        else
        {
            curr = curr->next;
        }
    }

    return (counter > 0);
}

/*
 * remove a node from the list
 * INPUT toRemove a reference to the node pointer we wish to delete
 * returns true if deleted false if else.
 */
bool songList::remove(node * toRemove)
{
    if(isEmpty() || !toRemove)
        return false;

    if(index == toRemove)
    {
        index = toRemove->next;
    }

    // removing a node in the middle of the list.
    if(toRemove->next)
    {
        toRemove->next->prev = toRemove->prev;
    }

    // removing a node at the end of our list.
    if(toRemove->prev)
    {
        toRemove->prev->next = toRemove->next;
    }

    delete toRemove;

    return true;
}

/*
 * Get the number of songs that have less than the target amount of likes
 * INPUT: target the number of likes the song must be >= to
 * OUTPUT: total an integer containing the total number of songs that have
 * less than target likes.
 */
int songList::getFrequency(const int target)
{
    int total = 0;
    node * curr = index;
    if(!index || target < 0)
    {
        return total;
    }

    while(curr)
    {
        if(curr->data->getLikes() < target)
        {
            total++;
        }
        curr = curr->next;
    }

    return total;
}


/*
 * Load data in from a file. Add a new song object for each line of song
 * data in the file.
 */
int songList::loadFromFile(const char * filename)
{
    fstream file(filename);
    song currentSong;
    const int MAX_CHAR = 101;
    char artistName[MAX_CHAR];
    char title[MAX_CHAR];
    int likes;
    int length;
    int totalLoaded = 0;


    if(!file)
    {
        cerr << "Failed to open " << filename << " for reading" << endl;
        return totalLoaded; // allow program to continue without the file data.
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
        insertSorted(tempSong);
        totalLoaded++;
        file.get(artistName, MAX_CHAR, ';');
    }

    file.close();
    return totalLoaded;

}



/*
 * overloaded assignment operator
 */
songList & songList::operator=(const songList &aList)
{
   if(this == &aList)
   {
       return *this;
   }
   destroy();
   size = aList.size;

   if(!aList.index)
   {
       index = tail = nullptr;
       return *this;
   }

   node * newNode = new node(*(aList.index->data));
   index = tail = newNode;
   node * nextSource = aList.index->next;
   node * nextDest = index;

   while(nextSource)
   {
       newNode = new node(*(nextSource->data));
       nextDest->next = newNode;
       newNode->prev = nextDest;
       nextSource = nextSource->next;
       nextDest = nextDest->next;
   }
   tail = nextDest;

   return *this;
}



/*
 * overloaded output stream operator
 */
 ostream& operator<<(ostream & out, const songList & aList)
{

    songList::node * curr = aList.index;
    while(curr)
    {
        out << *(curr->data);
        curr = curr->next;
    }



    return out;
}
