// Copyright Milan Oberkirch
// <oberkirm@tf.uni-freiburg.de>

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "./Bat.h"

Bat::Bat()
{
  _x = _y = 0;
  _length = 1;
}

void Bat::Init(int x, int y, int yMin, int yMax, int length)
{
  _x = x;
  _y = y;
  _yMin = yMin;
  _yMax = yMax;
  _length = length;
}

void Bat::Move(bool up)
{
  // Delete the bat from screen
  Erase();
  if (up)
  {
    _y -= (_length / 2);
  }
  else
  {
    _y += (_length / 2);
  }
  // Draw the bat into the screen-buffer
  Draw();
}

void Bat::Draw()
{
  // draw a '|' to every position, that equals the bat-position
  for (int i = _y; i < _length+_y; ++i)
  {
    if (i <= _yMax && i >= _yMin)
    {
      move(i, _x);
      printw("|");
    }
  }
}

void Bat::Draw(int y)
{
  _y = y;
  Draw();
}

void Bat::Erase()
{
  for (int i = _y; i < _length+_y; ++i)
  {
    if (i <= _yMax && i >= _yMin)
    {
      move(i, _x);
      printw(" ");
    }
  }
}
