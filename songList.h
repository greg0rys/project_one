#include "song.h"

class songList
{
public:
    songList();
    songList(const songList &);
    ~songList();
    void append(const song &);
    void editLikes(int likes, song &);
    void printList();
    void printOrdered();
    songList & operator=(const songList &);
    friend ostream&operator<< (ostream &, const songList &);
private:
    struct node
    {
        song * data;
        node * next,prev;


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

    node * index, tail;
    int size;
};