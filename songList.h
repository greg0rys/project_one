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
            next = nullptr;
            prev = nullptr;
        }

        ~node()
        {
            delete data;
            data = nullptr;
            next = nullptr;
            prev = nullptr;
        }
    };

    void destroy();
    node * getArtistAt(const char *);
    node * getSongAt(const char *);

    node * index;
    node * tail;
    int size;

public:
    songList();
    songList(const songList &);
    ~songList();
    void append(const song &);
    bool editLikes(int likes, const char *);
    void printList(const songList &);
    void printByArtist(const char *); // will take an artists name;
    bool isEmpty();
    void insertSorted(const song &, songList &);
    void loadFromFile(const char *);
    songList & operator=(const songList &);
    friend ostream&operator<< (ostream &, const songList &);

};
