#include "grid.h"
#include <curses.h>

int main(int argc, char **argv)
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);

  WINDOW *lifeOuter = newwin(HEIGHT + 2, WIDTH + 2, 0, 0);
  box(lifeOuter, 0, 0);
  WINDOW *lifeInner = derwin(lifeOuter, HEIGHT, WIDTH, 1, 1);

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

  wdraw(lifeInner, grid);
  wmove(lifeInner, y, x);
  refresh();
  wrefresh(lifeOuter);
  wrefresh(lifeInner);

  while (int ch = getch()) {
    switch (ch) {
    case 'q':
      goto exit;
      break;

    case 'l':
    case KEY_RIGHT:
      if (x < WIDTH - 1) {
        ++x;
      }
      break;
    case 'L':
      if (x < WIDTH - 10) {
        x += 10;
      }
      break;
    case 'h':
    case KEY_LEFT:
      if (x > 0) {
        --x;
      }
      break;
    case 'H':
      if (x >= 10) {
        x -= 10;
      }
      break;
    case 'j':
    case KEY_DOWN:
      if (y < HEIGHT - 1) {
        ++y;
      }
      break;
    case 'J':
      if (y < HEIGHT - 10) {
        y += 10;
      }
      break;
    case 'k':
    case KEY_UP:
      if (y > 0) {
        --y;
      }
      break;
    case 'K':
      if (y >= 10) {
        y -= 10;
      }
      break;

    case 't':
      toggle(grid, y, x);
      break;
    case 'n':
      advanceState(grid);
    }

    wdraw(lifeInner, grid);
    wmove(lifeInner, y, x);
    wrefresh(lifeInner);
  }

exit:
  endwin();
  delwin(lifeInner);
  delwin(lifeOuter);

  return 0;
}