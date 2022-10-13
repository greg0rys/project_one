/*
 * filename: song.cpp
 * the implementation file for song.h. This module defines all the functions
 * that a song must have.
 */
#include "song.h"


/*
 * default class constructor.
 */
song::song() : artistName(nullptr), title(nullptr), length(0), numOfLikes(0)
{}


/*
 * set a new song object up by passing in the songs information
 * INPUT artist a pointer that contains the songs name, title a pointer that
 * contains the title for the song, length an integer that represents the
 * total number of seconds for this song, numLikes an integer that
 * represents the total number of likes for a song.
 */
song::song(const char *artist, const char *title, int length, int numLikes)
{
    artistName = new char[strlen(artist) + 1];
    strcpy(artistName, artist);
    this->title = new char[strlen(title) + 1];
    strcpy(this->title, title);
    this->length = length;
    numOfLikes = numLikes;
}


/*
 * copy constructor
 */
song::song(const song &aCopy)
        : artistName(nullptr), title(nullptr), length(0), numOfLikes(0)
{
    *this = aCopy;
}


/*
 * class destructor
 */
song::~song()
{
    destroy();
}


/*
 * overloaded assignment operator to avoid shallow copies.
 */
song &song::operator=(const song &aCopy)
{
    if (this == &aCopy) {
        return *this;
    }
    destroy();
    if (!aCopy.artistName && aCopy.title) {
        this->artistName = nullptr;
        this->title = nullptr;
        length = aCopy.length;
        numOfLikes = aCopy.numOfLikes;
    } else if (!aCopy.title) {
        this->title = nullptr;
        length = 0;
        numOfLikes = 0;
    } else if (!aCopy.artistName) {
        this->artistName = nullptr;
        length = 0;
        numOfLikes = 0;
    } else {
        this->artistName = new char[strlen(aCopy.artistName) + 1];
        strcpy(this->artistName, aCopy.artistName);
        this->title = new char[strlen(aCopy.title) + 1];
        strcpy(this->title, aCopy.title);

        this->length = aCopy.length;
        this->numOfLikes = aCopy.numOfLikes;
    }

    return *this;
}


/*
 * sets the artist for this song
 * INPUT: name a pointer that contains the artist name.
 */
void song::setArtist(const char *name)
{
    if (this->artistName) {
        delete[] artistName;
    }
    this->artistName = new char[strlen(name) + 1];
    strcpy(this->artistName, name);
}


/*
 * sets the title for this song
 * INPUT: sTitle a pointer containing the songs title.
 */
void song::setTitle(const char *sTitle)
{

    if (this->title) {
        delete[] this->title;
    }
    this->title = new char[strlen(sTitle) + 1];
    strcpy(this->title, sTitle);
}


/*
 * set the length for this song
 * INPUT: songLength an integer representing the total number of seconds a
 * song is.
 */
void song::setLength(int songLength)
{ length = songLength; }


/*
 * set the number of likes for this song
 * INPUT: likes an integer representing the number of likes for this song.
 */
void song::setNumberOfLikes(int likes)
{ numOfLikes = likes; }


/*
 * returns the artist of a given song
 * input: artist a pointer that we wish to copy the artists name into.
 */
void song::getArtist(char *artist) const
{ strcpy(artist, artistName); }


/*
 * returns the title of a given song
 * INPUT: songTitle a pointer that we wish to copy the songs title into.
 */
void song::getTitle(char *songTitle) const
{

    strcpy(songTitle, title);
}


int song::getTitleLength() const
{
    return static_cast<int>(strlen(title));
}

/*
 * this function is called when a member of this class is destroyed, it will
 * deallocate the dynamic char arrays for artist name and the songs title.
 */
void song::destroy()
{
    if (this->artistName) {
        delete []artistName;
    }
    if (this->title) {
        delete []title;
    }
    this->artistName = nullptr;
    this->title = nullptr;

}


/*
 * returns the length of the current song
 */
int song::getLength() const
{ return length; }


/*
 * returns the number of likes of this song
 */
int song::getLikes() const
{ return numOfLikes; }


/*
 * overloaded stream operator to output all data about a song when it is
 * called by cout << aSong.
 * INPUT: ostream the current output stream, aSong the song we wish to output.
 * OUTPUT: all the information about a given song.
 */
ostream &operator<<(ostream &out, const song &aSong)
{
    unsigned int mins = (aSong.length / 60); // the total # of mins a song is
    unsigned int seconds = (aSong.length % 60); // the total # of seconds a
    // song is
    out << "Artist: " << aSong.artistName << " Title: " << aSong.title
        << " Duration: " << mins << "m " << seconds << "s Likes: "
        << aSong.numOfLikes << endl;

    return out;
}


/*
 * returns the length of the artist name length.
 */
int song::getArtistNameLength() const
{ return strlen(artistName); }


/*
 * compare two song objects return true if songOnes likes are greater than
 * the likes of songTwo
 * else return false.
 */
bool operator<(const song &songOne, const song &songTwo)
{
    return (songOne.getLikes() < songTwo.getLikes());
}
