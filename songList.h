#pragma once
#include "song.h"

class songList
{
private:
    struct node
    {
        song * data;
        node * next;
        node * prev;


        node()
        {
            data = nullptr;
            next = nullptr;
            prev = nullptr;
        }

         node(const song &aSong)
        {
            data = new song(aSong);
            prev = next = nullptr;
        }

        ~node()
        {
            delete data;
            data = nullptr;
            prev = next = nullptr;
        }
    };

    void destroy(); // destroy the pointers in our list


    node * index;
    node * tail;
    int size;

public:
    songList();
    songList(const songList &);
    ~songList();
    void append(const song &); // insert a new song at the end of the list
    void printList(const songList &); // print the list unordered.
    bool printByArtist(const char *); // print an ordered list by artist name.
    bool isEmpty(); // check if this list is empty
    void insert(const song &); // insert into a list sorted
    bool removeByLikes(const int);
    bool remove(node *);
    int getFrequency(const int);
    int getSize() const;
    int loadFromFile(const char *); // load song data from a file.

    songList & operator=(const songList &); // overloaded assignment
    friend ostream&operator<< (ostream &, const songList &); // overloaded stream insertion


};
