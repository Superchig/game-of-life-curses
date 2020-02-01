#pragma once

#include <curses.h>

constexpr int WIDTH = 25;
constexpr int HEIGHT = 25;

int calcLivingNbrs(char grid[][WIDTH], int y, int x);
bool shouldLive(char grid[][WIDTH], int y, int x);
void advanceState(char grid[][WIDTH]);
void toggle(char grid[][WIDTH], int y, int x);
void wdraw(WINDOW *win, char grid[][WIDTH]);