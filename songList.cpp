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
        delete curr;
        curr = index;
    }

    index = nullptr;
    size = 0;
}


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

}


bool songList::isEmpty()
{
    return (index == nullptr);
}


void songList::insertSorted(const song & aSong)
{
    node * current = index;
    if(!index)
    {
        node * newNode = new node(aSong);
        index = newNode;
        tail = newNode;
    }
    else if(current->data->getLength() < aSong.getLength())
    {
        node * newNode = new node(aSong);
        newNode->next = current;
        newNode->next->prev = newNode;
        index = newNode;
    }
    else
    {
        current = index;

        while(current->next &&
              current->next->data->getLength() < aSong.getLength())
        {
            current = current->next;
        }
        node * newNode = new node(aSong);
        newNode->next = current->next;

        if(current->next)
        {
            newNode->next->prev = newNode;
        }

        current->next = newNode;
        newNode->prev = current;
    }

}


bool songList::removeByLikes(const int target)
{
    bool success = false;
    node * curr = index;
    int counter = 0;
    if(target < 0)
        return success;

    while(curr && curr->next->data->getLikes() > target)
    {
        curr = curr->next;
    }

    if(curr)
    {
        remove(curr);
    }
    else
    {
        return false;
    }

    return success;
}

bool songList::remove(node *& toRemove)
{
    node * curr = index;
    if(!isEmpty())
    {
        while(curr && curr != toRemove)
        {
            curr = curr->next;
        }

        if(curr == index)
        {
            index = toRemove->next;
        }

        if(toRemove->next)
        {
            toRemove->next->prev = toRemove->prev;
        }

        if(toRemove->prev)
        {
            toRemove->prev->next = toRemove->next;
        }

        delete toRemove;
        return true;

    }
    else
    {
        return false;
    }
};

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
