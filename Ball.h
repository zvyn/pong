// Copyright Milan Oberkirch
// <oberkirm@tf.uni-freiburg.de>

#ifndef PROJEKT_BALL_H_
#define  PROJEKT_BALL_H_

#include <stdio.h>
#include <stdlib.h>
#include <gtest/gtest.h>
#include <vector>

using std::vector;

// Sub-class of Pong for managing the ball.
class Ball
{
  friend class Pong;
 public:
  // Constructor (see "private:" for discription of variables)
  Ball();
  // Destructor
  ~Ball() { }
  // set all values
  void Init(
      int x, int y,
      vector<float> direction,
      char ballTrace, int speedup);
  // set state values
  void Init(int x, int y, vector<float> direction);
  FRIEND_TEST(BallTest, Init);
  // ... and increase the _direction with given speedup
  void Init(int x, int y);
  // move Ball one step further
  void Step();
  // toggle movement of the ball
  bool toggle;
  // modify speed by factor (makes shure, that ball remains playable)
  void modSpeed(float factor);
  // switch components of _direction
  void modDirection();
  // reflect Ball on vertical object (it is reflectet horizontally then)
  void ReflectHorizontally();
  // reflect Ball on horizontal object
  void ReflectVertically();
  // draw the Ball at the current location
  void Draw();
  // Delte Ball from screen
  void Erase();
 private:
  // current Position (upper left corner is (0,0))
  float _xFloat, _yFloat;  // the absolute Position
  int _xView, _yView;  // position on the screen
  int _x, _y;  // position casted to integers
  // the direction; (1,1) means -100% (ball moves right down →↓)
  vector<float> _direction;
  char _ballTrace;
  int _speedup;
};

#endif  // PROJEKT_BALL_H_
