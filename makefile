CC = g++
CPPFLAGS = -Wall -g -std=c++11

app:			driver.o songList.o song.o driver.o

driver.o:			songList.h song.h driver.h

songList.o:		songList.h

song.o:	song.h


.PHONY: clean	
clean:			# clean the directory
			$(info -- cleaning the directory --)
			rm -f *.o
			rm -f app
