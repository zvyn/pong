// Copyright Milan Oberkirch
// <oberkirm@tf.uni-freiburg.de>

#ifndef PROJEKT_PAD_H_
#define PROJEKT_PAD_H_

#include <stdio.h>
#include <stdlib.h>
#include "./Pong.h"

// Sub-class of Pong for managing counters and creating window.
class Pad
{
  friend class Pong;
 public:
  // Constructor creats window, sets counters
  Pad();
  // Destructor resets window state
  ~Pad();
  // (re)initialice the window, (re)set counter
  void Init();
  // (re)draw the counter
  void Draw();
  // refresh everything
  void Clear();
  // increase one counter
  void CountUp(bool left);
 private:
  // width and hight of the window
  int _xMax, _yMax;
  // dimensions of the playground (Max is inclusive)
  int _xMaxPlay, _yMaxPlay, _xMinPlay, _yMinPlay;
  // center Position relative to the playground
  int _xMid, _yMid;
  // current score
  int _counterLeft, _counterRight;
};

#endif  // PROJEKT_PAD_H_
