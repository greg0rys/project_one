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
    node * curr = head;
    while(curr)
    {
        head = curr->next;
        delete head;
        curr = head;
    }
    size = 0;
}

void songList::append(const song &aSong)
{
    node * newNode = new Node(aSong);

    if(!head)
    {
        head = newNode;
        head->next = nullptr;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;

}


list & songList::operator=(const songList &aList)
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