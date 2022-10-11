#pragma once
#include "songList.h"
int main();
void getInput(char *&);
void endApplication();
void menu(songList &);
song getSongInfo();

void loadFromFile(char [], songList &); // load song data from a file.
