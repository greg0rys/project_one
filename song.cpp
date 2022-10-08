#include "song.h"

song::song(): artistName(nullptr), title(nullptr), length(0.00), numOfLikes(0.00)
{
}

song::song(const song &aCopy):artistName(nullptr), title(nullptr), length(0.00), numOfLikes(0.00)
{
	*this = aCopy;
}

song & song::operator=(const song &aCopy)
{
    if(this == &source)
    {
        return *this;
    }

    delete []artistName;
    delete []title;

    if(!aCopy.title)
    {
        title = nullptr;
    }
    else if(!aCopy.artistName)
    {
        artistName = nullptr;
    }
    else
    {
        setArtist(aCopy.artistName);
        setTitle(aCopy.title);
        setLength(aCopy.length);
        setNumberOfLikes(aCopy.numOfLikes);
    }
    return *this;
}

void song::setArtist(const char * name)
{
    if(artistName)
        delete []artistName;
    artistName = new char[strlen(name) + 1];
    strcpy(artistName, name);
}


void song::setTitle(const char * title)
{
    if(this->title)
        delete []this->title;
    this->title = new char(strlen(title) + 1);
    strcpy(this->title,title);
}

void song::setLength(const float songLength)
{
    length = songLength;
}


void song::setNumberOfLikes(const double likes)
{
    numOfLikes = likes;
}


void song::getArtist(char * artist) const
{
    if(!artist)
        artist = new char[strlen(artistName) + 1];
    else
        delete []artist;
        artist = new char[strlen(artistName) + 1];
    strcpy(artist, artistName);
}


void song::getTitle(char * songTitle) const
{
    if(!songTitle)
    {
        songTitle = new char[strlen(title) + 1];
    }
    else
    {
        delete[]songTitle;
        songTitle = new char[strlen(title) + 1];
    }

    strcpy(songTitle, title);
}

float song::getLength() const
{
    return length;
}

double song::getLikes() const
{
    return numOfLikes;
}

