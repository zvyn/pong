// Copyright Milan Oberkirch
// <oberkirm@tf.uni-freiburg.de>

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include "./Pong.h"
#include "./Pad.h"
#include "./Bat.h"
#include "./Ball.h"

using std::vector;


// ____________________________________________________________________________
Pong::Pong()
{
}


// ____________________________________________________________________________
void Pong::Init(
    int relativeSpeed,
    int batSize,
    int pointsToWin,
    char ballTrace,
    int speedup,
    bool bell)
{
  _relativeSpeed = relativeSpeed;
  _batSize = batSize;
  _pointsToWin = pointsToWin;
  _ballTrace = ballTrace;
  _speedup = speedup;
  _bell = bell;
  // Initialicing Pad
  _pad.Init();
  // Initialicing Ball
  vector<float> direction;
  direction.push_back(0.8 * _relativeSpeed * 0.01);
  direction.push_back(0.3 * _relativeSpeed * 0.01);
  _ball.Init(_pad._xMid, _pad._yMid, direction, _ballTrace, speedup);
  // Initialicing Bats
  _batLeft.Init(_pad._xMinPlay, _pad._yMid, _pad._yMinPlay, _pad._yMaxPlay,
      _batSize);
  _batRight.Init(_pad._xMaxPlay, _pad._yMid, _pad._yMinPlay, _pad._yMaxPlay,
      _batSize);
  _pad.Draw();
  Draw();
}


// ____________________________________________________________________________
void Pong::Run()
{
  while (true)
  {
    // Handling all events.
    Event();
    // Moving _ball one step further (refreshes screen)
    _ball.Step();
    // Slowing down a bit (importent for Performance)
    usleep(3000);
  }
}


// ____________________________________________________________________________
void Pong::Draw()
{
  _batRight.Draw();
  _batLeft.Draw();
}

// ____________________________________________________________________________
void Pong::printUsageAndPause()
{
  _ball.toggle = true;
  _pad.Clear();
  printw(
      "HOW TO PLAY:\n"
      "Goal:\n\tMove your bat up or down to hit the ball.\n"
      "Keys:\n"
      "* left bat:\n"
      "\tq:\t move up\n"
      "\ta:\t move down\n"
      "* right bat:\n"
      "\tarrow key up:\t move up\n"
      "\tarrow key down:\t move down\n"
      "any key: print this massage and pause\n"
      "STRG+C:\t Exit game!\n"
      "PRESS 'ESC' TO GO BACK TO THE GAME");
}

// ____________________________________________________________________________
void Pong::Event()
{
  HandleKeyEvents();
  HandleBallEvents();
  JumpBatIfOut(&_batRight);
  JumpBatIfOut(&_batLeft);
}

void Pong::HandleKeyEvents()
{
  char key = getch();
  if (key < 0) key = 7;  // ncurses makes it possible to have negative chars
  if (_ball.toggle && (key == 7 || key != 27)) return;
  switch (key)
  {
    // unspecified input (7 is mapped to bell -> could not be set by user)
    case 7: break;
    // Up-Key for right bat
    case 3: _batRight.Move(true);
              break;
    // Down-Key for right bat
    case 2: _batRight.Move(false);
              break;
    // Up-Key for left bat
    case 'q': _batLeft.Move(true);
              break;
    // Down-Key for left bat
    case 'a': _batLeft.Move(false);
              break;
    case 27: _pad.Clear();
             Draw();
             _pad.Draw();
             _ball.toggle = false;
             break;
    default: printUsageAndPause();
             break;
  }
}

void Pong::HandleBallEvents()
{
  // ball hits one of the horizontal walls
  if (_ball._y == _pad._yMinPlay || _ball._y == _pad._yMaxPlay)
  {
    _ball.ReflectVertically();
    _ball.Step();
    bell();
    Draw();
  }
  IsBallAtLeftBat();
  IsBallAtRightBat();
}

void Pong::IsBallAtLeftBat()
{
  const Bat &bat = _batLeft;
  if (_ball.toggle) return;
  // ball touches border
  if (_ball._x <= _pad._xMinPlay)
  {
    // ball touches bat
    if ((bat._y <= _ball._y) &&
         (bat._y > (_ball._y - bat._length)))
    {
      // reflect on bat
      _ball.ReflectHorizontally();
      _ball.Step();
      // beep and redraw bats
      bell();
      Draw();
    }
    // ball leaves at left side (not really but it would)
    else
    {
      // Score for the other player
      _pad._counterRight++;
      if (_pad._counterRight >= _pointsToWin) Win();
      _pad.Draw();
      // reinitialice ball
      _ball.Init(_pad._xMid, _pad._yMid);
      // redraw bats
      Draw();
    }
  }
}

void Pong::IsBallAtRightBat()
{
  const Bat &bat = _batRight;
  if (_ball.toggle) return;
  // ball touches border
  if (_ball._x >= _pad._xMaxPlay)
  {
    // ball touches bat
    if ((bat._y <= _ball._y) &&
         (bat._y > (_ball._y - bat._length)))
    {
      // reflect on bat
      _ball.ReflectHorizontally();
      _ball.Step();
      // beep and redraw bats
      bell();
      Draw();
    }
    // ball leaves at left side (not really but it would)
    else
    {
      // Score for the other player
      _pad._counterLeft++;
      if (_pad._counterLeft >= _pointsToWin) Win();
      _pad.Draw();
      // reinitialice ball
      _ball.Init(_pad._xMid, _pad._yMid);
      // redraw bats
      Draw();
    }
  }
}

void Pong::JumpBatIfOut(Bat *bat)
{
  if (bat->_y + bat->_length < _pad._yMinPlay)
  {
    bat->Draw(_pad._yMaxPlay);
  }
  if (bat->_y > _pad._yMaxPlay)
  {
    bat->Draw(_pad._yMinPlay);
  }
}

void Pong::Win()
{
  _ball.toggle = true;
  _pad.Clear();
  printw(
      "YOU WON WITH FINEL SCORE: %d : %d\n"
      "New game? (Press CTRL+C to exit or any key to start a new game)\n",
      _pad._counterLeft, _pad._counterRight);
  char c = 0;
  while (true)
  {
    c = getch();
    if (c > 0) break;
  }
  Init(_relativeSpeed, _batSize, _pointsToWin, _ballTrace, _speedup, _bell);
  _ball.toggle = false;
}

void Pong::bell()
{
  if (_bell) printf("\a");
}
