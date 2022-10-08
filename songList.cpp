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
        index->next = nullptr;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;

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
    node * sourceNext = sourceNext.index->next;
    node * newList = index;

    while(sourceNext)
    {
        newNode = new node(*sourceNext->data);
        newList->next = newnode;
        newnode->prev = newList;
        sourceNext = sourceNext->next;
        newList = newList->next;


    }
    tail = newList;

    return *this;
}
