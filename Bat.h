// Copyright Milan Oberkirch
// <oberkirm@tf.uni-freiburg.de>

#ifndef PROJEKT_BAT_H_
#define PROJEKT_BAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <gtest/gtest.h>

// Subclass of Pong for managing the bats.
class Bat
{
  friend class Pong;
 public:
  // Constructor
  Bat();
  // Initiator initiates variables with given initial values
  void Init(int x, int y, int xMin, int xMax, int length);
  FRIEND_TEST(BatTest, Init);
  // Destructor
  ~Bat() { }
  // move Bat by % of its length
  void Move(bool up, char percentOfLength);
  // move Bat by 25% of its length
  void Move(bool up);
  // draw the bat at current Position
  void Draw();
  void Draw(int y);
  // Delete bat from screen
  void Erase();
 private:
  // current Position (upper left corner is (0,0))
  int _x, _y;
  // Borders for the y-Position
  int _yMin, _yMax;
  // length
  int _length;
};

#endif  // PROJEKT_BAT_H_
