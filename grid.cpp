#include "grid.h"
#include <curses.h>

int calcLivingNbrs(char grid[][WIDTH], int y, int x)
{
  int count = 0;

  // down
  if (y + 1 < HEIGHT && grid[y + 1][x] == '#') {
    ++count;
  }
  // up
  if (y - 1 >= 0 && grid[y - 1][x] == '#') {
    ++count;
  }
  // right
  if (x + 1 < WIDTH && grid[y][x + 1] == '#') {
    ++count;
  }
  // left
  if (x - 1 >= 0 && grid[y][x - 1] == '#') {
    ++count;
  }
  // up-right
  if (y - 1 >= 0 && x + 1 < WIDTH && grid[y - 1][x + 1] == '#') {
    ++count;
  }
  // down-right
  if (y + 1 < HEIGHT && x + 1 < WIDTH && grid[y + 1][x + 1] == '#') {
    ++count;
  }
  // up-left
  if (y - 1 >= 0 && x - 1 >= 0 && grid[y - 1][x - 1] == '#') {
    ++count;
  }
  // down-left
  if (y + 1 < HEIGHT && x - 1 >= 0 && grid[y + 1][x - 1] == '#') {
    ++count;
  }

  return count;
}

bool shouldLive(char grid[][WIDTH], int y, int x)
{
  int livingNbrs = calcLivingNbrs(grid, y, x);
  bool isAlive = grid[y][x] == '#';

  if (isAlive && livingNbrs < 2) {
    return false;
  }
  else if (isAlive && livingNbrs >= 2 && livingNbrs <= 3) {
    return true;
  }
  else if (isAlive && livingNbrs > 3) {
    return false;
  }
  else if (!isAlive && livingNbrs == 3) {
    return true;
  }
  else {
    return false;
  }
}

void advanceState(char grid[][WIDTH])
{
  char futureGrid[HEIGHT][WIDTH];

  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      futureGrid[i][j] = shouldLive(grid, i, j) ? '#' : ' ';
    }
  }

  // Copy contents of futureGrid into grid
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      grid[i][j] = futureGrid[i][j];
    }
  }
}

void toggle(char grid[][WIDTH], int y, int x)
{
  grid[y][x] = (grid[y][x] == '#') ? ' ' : '#';
}

void draw(WINDOW *win, char grid[][WIDTH])
{
  werase(win);
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      waddch(win, grid[i][j]);
    }
    waddch(win, '\n');
  }
}