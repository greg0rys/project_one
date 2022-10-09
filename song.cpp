#include "song.h"

song::song(): artistName(nullptr), title(nullptr), length(0.00), numOfLikes(0.00)
{
}

song::song(const song &aCopy):artistName(nullptr), title(nullptr), length(0.00), numOfLikes(0.00)
{
	*this = aCopy;
}

song::~song()
{
    if(artistName)
        delete []artistName;
    else if(title)
        delete []title;
    artistName = nullptr;
    title = nullptr;
}

song & song::operator=(const song &aCopy)
{
    if(this == &aCopy)
    {
        return *this;
    }

    if(artistName)
        delete []artistName;
    if(title)
        delete []title;

    if(!aCopy.artistName && !aCopy.title)
    {
        artistName = nullptr;
        title = nullptr;
        setLength(aCopy.length);
        setNumberOfLikes(aCopy.numOfLikes);
    }
    else if(!aCopy.artistName && aCopy.title)
    {
        artistName = nullptr;
        setTitle(aCopy.title);
        setLength(aCopy.length);
        setNumberOfLikes(aCopy.numOfLikes);
    }
    else if(aCopy.artistName && !aCopy.title)
    {
        setArtist(aCopy.artistName);
        title = nullptr;
        setLength(aCopy.length);
        setNumberOfLikes(aCopy.numOfLikes);
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

void song::setLength(float songLength)
{
    length = songLength;
}


void song::setNumberOfLikes(int likes)
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

int song::getLikes() const
{
    return numOfLikes;
}

