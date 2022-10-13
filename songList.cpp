/*
 * filename: songList.cpp
 * the implementation file for songList.h it implements the methods of the
 * ADT list allowing the client to perform operations on the list and its
 * contents.
 */


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
    node * curr = index; // the current head of our list.
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
 * Get a pointer to asong in the list based on its title
 * INPUT: the title of the song we wish to search for
 * OUTPUT: a pointer to the song or nullptr if not found.
 */
songList::node * songList::getSongAt(const char *songTitle)
{
    node * curr = index; // the current list head
    node * foundNode = nullptr; // the node we are searching for
    char * currentTitle = nullptr; // the current title of a song
    if(!index)
    {
        return nullptr;
    }

    while(curr)
    {
        if(currentTitle)
        {
            delete []currentTitle;
        }
        currentTitle = new char[curr->data->getTitleLength() + 1];
        curr->data->getTitle(currentTitle);
        if(strcmp(currentTitle, songTitle) == 0)
        {
            foundNode = curr;
        }

        curr = curr->next;


    }

    if(currentTitle)
    {
        delete []currentTitle;
    }

    return foundNode;
}


/*
 * Edit the likes for a song in the list.
 * INPUT: newLikes the likes we want to update the song too - songTitle the
 * title of the song we want to update
 * OUTPUT: true if the node was updated and list sorted false if else.
 */
bool songList::editLikes(int newLikes, const char * songTitle)
{
    node * nodeToEdit = getSongAt(songTitle); // the node to update
    node * curr = index; // the current list head
    songList updatedList; // the newly updated list, resorted.
    if(!nodeToEdit)
    {
        return false;
    }
    else
    {
        // update the nodes likes
        nodeToEdit->data->setNumberOfLikes(newLikes);
        // resort the current list so it displays in order.
        while(curr)
        {
            updatedList.insert(*(curr->data));
            curr = curr->next;
        }

        // set this list to be the newly sorted list.
        *this = updatedList;
        return true;
    }
}


/*
 * Find a song in our list based on its title
 * INPUT: songTitle the title of the song we wish to search for
 * OUTPUT: true if the song was found false if else.
 */
bool songList::findSongTitle(const char * songTitle)
{
    node * searchNode = getSongAt(songTitle); // the song we are searching for

    return (searchNode == nullptr);
}



/*
 * append a new song to the end of the list
 * INPUT: aSong a reference to a song object
 */
void songList::append(const song &aSong)
{
    node * newNode = new node(aSong); // the new node to be added to the list.


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
 * print all of the songs in our list (unsorted)
 * INPUT list a reference to a list
 */
void songList::printList(const songList &list)
{
    if(!isEmpty())
    {
        cout << list << endl;
    }
}

/*
 * print songs in the list for a given artist sorted by likes.
 * INPUT: artName a pointer containing the artist name we wish to print
 */
bool songList::printByArtist(const char * artName)
{
    songList sortedList; // a tempory list based on the artist name.
    song tempSong; // the song to add to our list
    node * curr = index; // the current list head
    int totalFound = 0; // the total number of found matches
    char * currentArtist = nullptr; // the current artist name

    while(curr)
    {
        if(currentArtist)
            delete []currentArtist;

        currentArtist = new char[curr->data->getArtistNameLength() + 1];
        curr->data->getArtist(currentArtist);

        if(strcmp(currentArtist, artName) == 0)
        {

            tempSong = *(curr->data);
            sortedList.insert(tempSong);
            totalFound++;
        }

        curr = curr->next;
    }

    cout << "[ " << totalFound << " ] songs found by " << artName << endl;
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
 * insert a new song to the list sorted descending by total number of likes.
 * INPUT aSong a reference to a song object
 */
void songList::insert(const song &aSong)
{

    node * newNode = new node(aSong); // the new node to add to our list
    node * curr = index; // the current list head.

    if(!index)
    {
        index = newNode;
        size = 1;
    }
    // insert the node at the front of the list
    else if(index->data->getLikes() <= aSong.getLikes())
    {
        newNode->next = index;
        newNode->next->prev = newNode;
        index = newNode;
        size++;
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
        size++;
    }

}


/*
 * remove a song from the list based on the number of likes it has
 * INPUT target an integer containing the number of likes we wish to delete
 * returns true if able to remove the node else returns false.
 */
bool songList::removeByLikes(const int target)
{
    node * curr = index; // current list head
    node * next = nullptr; // the current nodes next node
    int counter = 0; // the total number of nodes removed.

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
    // the list is empty
    if(isEmpty() || !toRemove)
        return false;

    // removing the first node in the list.
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
    int total = 0; // total number of matching nodes
    node * curr = index; // the current list head
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
    fstream file(filename); // the file to open
    song currentSong; // the current song in the file
    const int MAX_CHAR = 101; // the max number of chars for a name or title
    char artistName[MAX_CHAR]; // songs artist name
    char title[MAX_CHAR]; // songs title
    int likes; // songs number of likes
    int length; // songs length
    int totalLoaded = 0; // total number of songs loaded


    if(!file)
    {
        cerr << "Failed to open " << filename << " for reading" << endl;
        return totalLoaded; // allow program to continue without the file data.
    }

    file.get(artistName, MAX_CHAR, ';');

    while(!file.eof())
    {
        file.get(); // throw away the delim
        file.get(title, MAX_CHAR, ';');
        file.get();
        file >> likes;
        file.ignore(MAX_CHAR, ';');
        file >> length;
        file.ignore(MAX_CHAR, '\n');
        song tempSong(artistName,title,length,likes);
        insert(tempSong);
        totalLoaded++;
        file.get(artistName, MAX_CHAR, ';');
    }

    file.close();
    return totalLoaded;

}


/*
 * returns the total size of the list
 * OUTPUT: the total number of items in the list.
 */
int songList::getSize() const
{
    return size;
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

   node * newNode = new node(*(aList.index->data)); // the new node
   index = tail = newNode;
   node * nextSource = aList.index->next; // the next item in the source list
   node * nextDest = index; // the next destination of the current list

   while(nextSource)
   {
       newNode = new node(*(nextSource->data)); // the next node in the
       // source list
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

    songList::node * curr = aList.index; // the head of the parameter list.
    while(curr)
    {
        out << *(curr->data);
        curr = curr->next;
    }



    return out;
}
