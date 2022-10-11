#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

class song
{
public:
    song();
    song(const char *, const char *, int, int);
    ~song();
    song(const song &); // copy constructor
    song & operator=(const song &); // overloaded assignment operator
    void setArtist(const char *);
    void setTitle(const char *);
    void setLength(int);
    void setNumberOfLikes(int);
    void getArtist(char *) const;
    void getTitle(char *) const;
    unsigned int getLength() const;
    unsigned int getLikes() const;
    unsigned int getArtistNameLength() const;
    friend ostream&operator<< (ostream &, const song &);



private:
    char * artistName;
    char * title;
    unsigned int length;
    unsigned int numOfLikes;
    void destroy();




};

bool operator< (const song &, const song&);