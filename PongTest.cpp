// Copyright 2011 Milan Oberkirch
// <oberkirm@uni-freiburg.de>

#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "./Pong.h"

Pong pong;

TEST(PongTest, Init)
{
  pong.Init(100, 10, 1, '.', 2, true);
  ASSERT_EQ(pong._pointsToWin, 1);
  ASSERT_EQ(10, pong._batSize);
}

TEST(BatTest, Init)
{
  Bat bat;
  bat.Init(0, 100, 1, 200, 10);
  ASSERT_EQ(10, bat._length);
  ASSERT_EQ(100, bat._y);
}

TEST(BallTest, Init)
{
  Ball ball;
  std::vector<float> direction;
  direction.push_back(0.8);
  direction.push_back(0.3);
  ball.Init(200, 100, direction);
  ASSERT_NEAR(ball._direction[0], 0.8, 0.001);
  ASSERT_NEAR(ball._direction[1], 0.3, 0.001);
}
