#include "grid.h"
#include <curses.h>

int main(int argc, char **argv)
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);

  char grid[HEIGHT][WIDTH];
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      grid[i][j] = ' ';
    }
  }

  grid[0][1] = '#';
  grid[1][1] = '#';

  int x = 0;
  int y = 0;

  draw(stdscr, grid);
  move(y, x);

  while (int ch = getch()) {
    switch (ch) {
    case 'q':
      goto exit;
      break;

    case 'l':
    case KEY_RIGHT:
      if (x < WIDTH) {
        move(y, ++x);
      }
      break;
    case 'h':
    case KEY_LEFT:
      if (x > 0) {
        move(y, --x);
      }
      break;
    case 'j':
    case KEY_DOWN:
      if (y < HEIGHT) {
        move(++y, x);
      }
      break;
    case 'k':
    case KEY_UP:
      if (y > 0) {
        move(--y, x);
      }
      break;

    case 't':
      toggle(grid, y, x);
      break;
    case 'n':
      advanceState(grid);
    }

    draw(stdscr, grid);
    move(y, x);
  }

exit:
  endwin();

  return 0;
}