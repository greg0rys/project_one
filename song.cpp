#include "song.h"

song::song(): artistName(nullptr), title(nullptr), length(0.00), numOfLikes(0.00)
{
}

song::song(const song &aCopy)
{
	artistName = nullptr;
	title = nullptr;
	*this = aCopy;
}

song & song::operator=(const song &aCopy)
{
    if(this == source)
    {
        return *this;
    }

    if(this->artistName && this->title)
    {
        delete []artistName;
        delete []title;
    }
    else if(this->artistName)
    {
        delete []artistName;
    }
    else
    {
        delete []title;
    }
	if(aCopy.artistName && aCopy.title)
	{
		char * artist = new char[aCopy.getArtistLength() + 1];
        char * title = new char[aCopy.getTitleLength() + 1];
        strcpy(artist, aCopy.artistName);
        strcpy(title,aCopy.title);
	}
    else if(aCopy.artistName && !aCopy.title)
    {
        char * artist
    }
}

