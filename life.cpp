#include <iostream>
#include <sstream>

using namespace std;

constexpr int WIDTH = 10;
constexpr int HEIGHT = 10;

void printGrid(const char grid[][WIDTH])
{
  cout << "  0123456789" << endl;

  for (int i = 0; i < HEIGHT; ++i) {
    if (i <= 9) {
      cout << i << ' ';
    }

    for (int j = 0; j < WIDTH; ++j) {
      cout << grid[i][j];
    }
    cout << endl;
  }
}

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

int main(int argc, char **argv)
{
  cout << "Welcome to an implementation of Conway's Game of Life!" << endl;

  char grid[HEIGHT][WIDTH];
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      grid[i][j] = ' ';
    }
  }

  // Set the initial state of the game
  grid[0][1] = '#';
  grid[1][1] = '#';
  grid[2][1] = '#';

  // Primary loop
  while (true) {
    cout << "> ";
    string input;
    getline(cin, input);

    if (input == "q" || input == "quit") {
      break;
    }
    else if (input == "p" || input == "print") {
      printGrid(grid);
    }
    else if (input == "n" || input == "next") {
      advanceState(grid);
      printGrid(grid);
    } else if (input.at(0) == 't') {
      string dummy;
      int yPos;
      int xPos;

      stringstream words{input};
      words >> dummy >> yPos >> xPos;

      toggle(grid, yPos, xPos);

      printGrid(grid);
    }
  }

  return 0;
}