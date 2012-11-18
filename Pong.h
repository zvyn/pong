// Copyright Milan Oberkirch
// <oberkirm@tf.uni-freiburg.de>

#ifndef PROJEKT_PONG_H_
#define PROJEKT_PONG_H_

#include <stdio.h>
#include <stdlib.h>
#include <gtest/gtest.h>
#include "./Pad.h"
#include "./Bat.h"
#include "./Ball.h"

// Main class for the pong-game |· |
class Pong
{
 public:
  // Constructor (uses init to set all standart values)
  Pong();
  // Destructor
  ~Pong() { }
  // set all standart values
  void Init(
      int relativeSpeed,
      int batSize,
      int pointsToWin,
      char ballTrace,
      int speedup,
      bool bell);
  FRIEND_TEST(PongTest, Init);
  // run the programm (this function takes care of events and maks sure that
  // changes to the window are drawed one after another)
  void Run();
  // redraw everything (runs all Draw Functions of the sub-classes)
  void Draw();
  // prints Usage while pausing the Programm (if unknown key is pressed)
  void printUsageAndPause();
  // print final score and ask for replay
  void Win();
 private:
  // check for events and call the right function for the detected event
  void Event();
  void HandleKeyEvents();
  void HandleBallEvents();
  void JumpBatIfOut(Bat *bat);
  void IsBallAtLeftBat();
  void IsBallAtRightBat();
  void bell();
  // the pad is responsible for drawing the window and setting counters
  friend void Bat::Draw();
  Pad _pad;
  // the bats
  Bat _batLeft;
  Bat _batRight;
  // the ball
  Ball _ball;
  // Initial parameters
  int _relativeSpeed;
  int _batSize;
  int _pointsToWin;
  char _ballTrace;
  int _speedup;
  bool _bell;
};

#endif  // PROJEKT_PONG_H_
