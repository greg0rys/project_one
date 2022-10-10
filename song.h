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
		~song();
		song(const song &); // copy constructor
		song & operator=(const song &); // overloaded assignment operator
		void setArtist(const char *);
		void setTitle(const char *);
		void setLength(int);
		void setNumberOfLikes(int);
		void getArtist(char *) const;
		void getTitle(char *) const;
		int getLength() const;
		int getLikes() const;
        int getArtistNameLength() const;
       friend ostream&operator<< (ostream &, const song &);



private:
		char * artistName;
		char * title;
		int length;
		int numOfLikes;




};

bool operator< (const song &, const song&);
