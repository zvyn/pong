// Copyright Milan Oberkirch
// <oberkirm@tf.uni-freiburg.de>

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include "./Pong.h"

// ____________________________________________________________________________
Pad::Pad()
{
  _xMax = _yMax = 0;
  _counterLeft = _counterRight = 0;
}

// ____________________________________________________________________________
Pad::~Pad()
{
  endwin();
}

// ____________________________________________________________________________
void Pad::Init()
{
  // Initiate screen, see "man 3 ncurses" for more details
  initscr();
  cbreak();
  noecho();
  nonl();
  nodelay(stdscr, true);
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);
  curs_set(false);

  // Set all maximum values
  getmaxyx(stdscr, _yMax, _xMax);
  // All borders are inclusive
  _xMax--;
  _yMax--;
  _xMaxPlay = _xMax;
  _yMaxPlay = _yMax - 1;
  _xMinPlay = 0;
  _yMinPlay = 2;
  _xMid = ((_xMaxPlay - _xMinPlay) / 2) + _xMinPlay;
  _yMid = ((_yMaxPlay - _yMinPlay) / 2) + _yMinPlay;

  // Initialice counter
  _counterLeft = _counterRight = 0;
}

// ____________________________________________________________________________
void Pad::CountUp(bool left)
{
  left?_counterLeft++:_counterRight++;
  Draw();
}

// ____________________________________________________________________________
void Pad::Draw()
{
  mvprintw(0, (_xMax / 2) - 5,
      "%.3d | %.3d",
      _counterLeft, _counterRight);
  move(_yMinPlay - 1, 0);
  for (int i = 0; i <= _xMax; ++i)
  {
    printw("_");
  }
  move(_yMax, 0);
  for (int i = 0; i <= _xMax; ++i)
  {
    printw("_");
  }
}

// ____________________________________________________________________________
void Pad::Clear()
{
  refresh();
  clear();
  move(0, 0);
}
