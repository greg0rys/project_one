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
		void setLength(const float);
		void setNumberOfLikes(const double);
		void getArtist(char *) const;
		void getTitle(char *) const;
		float getLength() const;
		double getLikes() const;
	private:
		char * artistName;
		char * title;
		float length;
		double numOfLikes;

		int getArtistLength() const
		{
			return strlen(artistName);
		}
		int getTitleLength() const
		{
			return strlen(title);
		}
};
