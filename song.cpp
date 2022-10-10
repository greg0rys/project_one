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




    if(aCopy.artistName && aCopy.title)
    {
        setArtist(aCopy.artistName);
        setTitle(aCopy.title);
        setNumberOfLikes(aCopy.getLikes());
        setLength(aCopy.getLength());
    }
    else
    {
        artistName = nullptr;
        title = nullptr;
        setNumberOfLikes(aCopy.getLikes());
        setLength(aCopy.getLength());
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

void song::setLength(int songLength)
{
    length = songLength;
}


void song::setNumberOfLikes(int likes)
{
    numOfLikes = likes;
}


void song::getArtist(char * artist) const
{


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

int song::getLength() const
{
    return length;
}

int song::getLikes() const
{
    return numOfLikes;
}


ostream& operator<<(ostream &out, const song &aSong)
{
    int mins = (aSong.length / 60);
    int seconds = (aSong.length % 60) * 100;
    out << aSong.artistName << " " << aSong.title
        << " " << mins  << "m " << seconds << "s " << aSong.numOfLikes
        << endl;

    return out;
}



int song::getArtistNameLength() const
{
    return strlen(artistName);
}



bool operator<(const song &songOne, const song &songTwo)
{
    return (songOne.getLikes() < songTwo.getLikes());
}

