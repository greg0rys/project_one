CC = g++
CPPFLAGS = -std=c++11 -g -Wall
DEPS = driver.h song.h songList.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

app: driver.o song.o songList.o
	$(CC) -o app driver.o song.o songList.o

.PHONY: clean
clean:
	$(info -- cleaning up --)
	rm -f *.o
	rm -f app
