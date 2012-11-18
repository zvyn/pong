// Copyright Milan Oberkirch
// <oberkirm@tf.uni-freiburg>

#include <curses.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "./Pong.h"
#include "./Ball.h"

Ball::Ball()
{
  _x = _y = 0;
  _direction.push_back(0);
  _direction.push_back(0);
}

void Ball::Init(int x, int y)
{
  modSpeed(1 + (0.01 * _speedup));
  Init(x, y, _direction);
}

void Ball::modSpeed(float factor)
{
  float direction0 = factor * _direction[0];
  float direction1 = factor * _direction[1];
  // prevent unplayable speeds
  if (direction0 > 0.8 || direction1 > 0.8)
  {
    float relation = direction1 / direction0;
    direction0 = 0.8;
    direction1 = relation;
  }
  if ((direction0 < 0.05 || direction1 < 0.025)
      && direction0 > 0 && direction1 > 0)
  {
    float relation = direction1 / direction0;
    direction0 = 0.1;
    direction1 = relation * 0.1;
  }
  // set new speed
  _direction[0] = direction0;
  _direction[1] = direction1;
}

void Ball::modDirection()
{
  _direction[0] += ((_x % 3) * 0.01);
  if (_direction[0] > 2) _direction[0] -= 1;
}

void Ball::Init(int x, int y, vector<float> direction)
{
  _xFloat = _x = x;
  _yFloat = _y = y;
  _direction = direction;
  toggle = false;
}

void Ball::Init(
    int x, int y,
    vector<float> direction,
    char ballTrace, int speedup)
{
  _ballTrace = ballTrace;
  _speedup = speedup;
  Init(x, y, direction);
}

void Ball::Step()
{
  if (toggle) return;
  _xFloat += _direction[0];
  _yFloat += _direction[1];
  int xNew = static_cast<int>(round(_xFloat));
  int yNew = static_cast<int>(round(_yFloat));
  bool doDraw = false;
  if (xNew != _xView && yNew != _yView) doDraw = true;
  if (doDraw) Erase();
  _x = xNew;
  _y = yNew;
  if (doDraw)
  {
    Draw();
    refresh();
  }
}

void Ball::ReflectHorizontally()
{
  _direction[0] = _direction[0] * (-1);
}

void Ball::ReflectVertically()
{
  _direction[1] *= (-1);
}

void Ball::Draw()
{
  move(_y, _x);
  printw("O");
  _xView = _x;
  _yView = _y;
}

void Ball::Erase()
{
  move(_yView, _xView);
  printw("%c", _ballTrace);
}

