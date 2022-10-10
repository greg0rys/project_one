#include "songList.h"

songList::songList(): index(nullptr), tail(nullptr), size(0)
{}

songList::songList(const songList &source):index(nullptr), tail(nullptr),
size(0)
{
    *this = source;
}


songList::~songList()
{
    destroy();
}

void songList::destroy()
{
    node * curr = index;
    while(curr)
    {
        index = curr->next;
        delete index;
        curr = index;
    }
    size = 0;
}

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

// these may need to be defined in the .h file to avoid this error of no
// type found for *node.
songList::node* songList::getSongAt(const char * songName)
{
    node * curr = index;
    char * currentSongName = nullptr;

    while(curr)
    {
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


void songList::printList(const songList &list)
{

    if(isEmpty())
        cout << "The list is empty!" << endl;
    else
        cout << list;
}


void songList::printByArtist(const char * artName)
{
    songList sortedList;
    node * curr = index;
    char * currentSongName = nullptr;

    while(curr)
    {
        curr->data->getArtist(currentSongName);
        if(strcmp(currentSongName, artName) == 0)
        {
            insertSorted(*curr->data, sortedList);
        }

        curr = curr->next;
    }

    cout << sortedList << endl;

}


bool songList::isEmpty()
{
    return (index == nullptr);
}


void songList::insertSorted(const song & aSong, songList & aList)
{
    node * curr = aList.index;
    node * newNode = nullptr;
    if(!aList.index)
    {
        aList.index = new node(aSong);

    }
    while(curr && curr->data->getLikes() < aSong.getLikes())
    {
        curr = curr->next;
    }

    if(!curr)
    {
        newNode = new node(aSong);
        aList.tail->next = newNode;
        newNode->prev = tail;
        aList.tail = newNode;
    }
    else
    {
        newNode = new node(aSong);
        newNode->prev = curr;
        newNode->next = curr->next;
    }
}


void songList::loadFromFile(const char * filename)
{
    ifstream file;
    song currentSong;

}

songList & songList::operator=(const songList &aList)
{
    if(this == &aList)
        return *this;
    // destroy this list, if it already has data.
    destroy();
    size = aList.size;

    if(!aList.index)
    {
        index = tail = nullptr;
        return *this;
    }

    node * newNode = new node(*aList.index->data);
    index = tail = newNode;
    node * sourceNext = sourceNext->next;
    node * newList = index;

    while(sourceNext)
    {
        newNode = new node(*sourceNext->data);
        newList->next = newNode;
        newNode->prev = newList;
        sourceNext = sourceNext->next;
        newList = newList->next;


    }
    tail = newList;

    return *this;
}


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
