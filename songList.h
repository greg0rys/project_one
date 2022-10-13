/*
 * filename: songList.h
 * the header file for songList.cpp this file defines the ADT songList and
 * the data members it must have while also defining the operations that
 * are allowed on this ADT
 */

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

    node * getSongAt(const char *); // get a pointer to a node by song title

    node * index; // the list head
    node * tail; // the end of the list
    int size; // the size of the list

public:
    songList();
    songList(const songList &);
    ~songList();
    void append(const song &); // insert a new song at the end of the list
    void printList(const songList &); // print the list unordered.
    bool printByArtist(const char *); // print an ordered list by artist name.
    bool isEmpty(); // check if this list is empty
    void insert(const song &); // insert into a list sorted
    bool removeByLikes(const int); // remove a song with less than m likes
    bool editLikes(int, const char *); // edit the likes of a song
    bool remove(node *); // remove a node from the list
    int getFrequency(const int); // the number of songs with less than m likes
    bool findSongTitle(const char *); // see if a song with a title is in
    // the list
    int getSize() const; // get the size of the list.
    int loadFromFile(const char *); // load song data from a file.

    songList & operator=(const songList &); // overloaded assignment
    friend ostream&operator<< (ostream &, const songList &); // overloaded stream insertion


};
