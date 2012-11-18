// Copyright Milan Oberkirch
// I don't think its an art to write this.

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "./Parse.h"

Parse::Parse(int argc, char** argv)
{
  _speed = 20;
  _batLength = 12;
  _pointsToWin = 3;
  _ballTrace = ' ';
  _speedup = 0;
  _bell = true;
  Init(argc, argv);
}

void Parse::Init(int argc, char** argv)
{
  _argc = argc;
  _argv = argv;
  if (_argc < 1) fprintf(stderr, "_argc < 1 WTF?! This is a bug!");
  struct option options[] =
  {
    {"speedup", 1, NULL, 'a'},
    {"speed", 1, NULL, 's'},
    {"bat-length", 1, NULL, 'b'},
    {"points-to-win", 1, NULL, 'w'},
    {"trace", 1, NULL, 't'},
    {"mute", 0, NULL, 'm'},
    {NULL, 0, NULL, 0}
  };
  optind = 1;
  while (true)
  {
    // Remember that getopt_long rearranges the arguments
    int c = getopt_long(_argc, _argv, "a:s:b:w:t:m:", options, NULL);
    // if no arguments are left, break
    if (c == -1) break;
    switch (c)
    {
      case 's':
        _speed = atoi(optarg);
        break;
      case 'b':
        _batLength = atoi(optarg);
        break;
      case 'w':
        _pointsToWin = atoi(optarg);
        break;
      case 't':
        _ballTrace = optarg[0];
        break;
      case 'a':
        _speedup = atoi(optarg);
        break;
      case 'm':
        _bell = false;
        break;
      // if there are unknowen arguments, this programm should:
      default:
        printUsageAndExit();
    }
  }
  // only one argument left (if not...):
  if (optind != argc) printUsageAndExit();
}

void Parse::printUsageAndExit()
{
  fprintf(stderr,
      "\nUsage:\n"
      "\tA simple pong-game.\n"
      "\t(Press any key inside the game to gain a short help)\n"
      "Optional Parameters:\n"
      "\t-s [--speed=]Number : Set the speed of the ball in percent\n"
      "\t-b [--bat-length=]Number : Set the length of the bats\n"
      "\t-w [--points-to-win=]Num"
      "ber : Set the count of points you need to win.\n"
      "\t-a [--speedup=]Number : speedup after every point\n"
      "\t-w [--trace=]Number : Trace of the Ball\n");
  exit(1);
}
