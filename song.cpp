#include "song.h"

song::song() : artistName(nullptr), title(nullptr), length(0), numOfLikes(0) {}

song::song(const char *artist, const char *title, int length, int numLikes) {
    artistName = new char[strlen(artist) + 1];
    strcpy(artistName, artist);
    this->title = new char[strlen(title) + 1];
    strcpy(this->title, title);
    this->length = length;
    numOfLikes = numLikes;
}

song::song(const song &aCopy)
        : artistName(nullptr), title(nullptr), length(0), numOfLikes(0) {
    *this = aCopy;
}

song::~song() {
    if (artistName)
        delete[] artistName;
    else if (title)
        delete[] title;
    artistName = nullptr;
    title = nullptr;
}

song &song::operator=(const song &aCopy) {
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

void song::setArtist(const char *name) {
    if (this->artistName) {
        delete[] artistName;
    }
    this->artistName = new char[strlen(name) + 1];
    strcpy(this->artistName, name);
}

void song::setTitle(const char *title) {

    if (this->title) {
        delete[] this->title;
    }
    this->title = new char(strlen(title) + 1);
    strcpy(this->title, title);
}

void song::setLength(int songLength) { length = songLength; }

void song::setNumberOfLikes(int likes) { numOfLikes = likes; }

void song::getArtist(char *artist) const { strcpy(artist, artistName); }

void song::getTitle(char *songTitle) const {
    if (!songTitle) {
        songTitle = new char[strlen(title) + 1];
    } else {
        delete[] songTitle;
        songTitle = new char[strlen(title) + 1];
    }

    strcpy(songTitle, title);
}

void song::destroy() {
    if (artistName) {
        delete[] artistName;
    }
    if (title) {
        delete[] title;
    }

    artistName = nullptr;
    title = nullptr;
    length = 0;
    numOfLikes = 0;
}

int song::getLength() const { return length; }

int song::getLikes() const { return numOfLikes; }

ostream &operator<<(ostream &out, const song &aSong) {
    int mins = (aSong.length / 60);
    int seconds = (aSong.length % 60) * 100;
    out << aSong.artistName << " " << aSong.title << " " << mins << "m "
        << seconds << "s " << aSong.numOfLikes << endl;

    return out;
}

int song::getArtistNameLength() const { return strlen(artistName); }

bool operator<(const song &songOne, const song &songTwo) {
    return (songOne.getLikes() < songTwo.getLikes());
}
