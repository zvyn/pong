// Copyright Milan Oberkirch

#include <curses.h>
#include "./Parse.h"
#include "./Pong.h"
#include "./Pad.h"
#include "./Ball.h"
#include "./Bat.h"

int main(int argc, char** argv)
{
  Parse arguments(argc, argv);
  Pong pong;
  pong.Init(
      arguments.speed(),
      arguments.batLength(),
      arguments.pointsToWin(),
      arguments.ballTrace(),
      arguments.speedup(),
      arguments.bell());
  pong.Run();
}

