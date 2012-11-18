// Copyright Milan Oberkirch
// I don't think its an art to write this.

#ifndef PROJEKT_PARSE_H_
#define PROJEKT_PARSE_H_

class Parse
{
 public:
  // Constructers are for constructing
  Parse(int argc, char** argv);
  // Destructor
  ~Parse() { }
  // Get-Methods for parsed Variables
  int speed() { return _speed; }
  int batLength() { return _batLength; }
  int pointsToWin() { return _pointsToWin; }
  char ballTrace() { return _ballTrace; }
  int speedup() { return _speedup; }
  bool bell() { return _bell; }
 private:
  void Init(int argc, char** argv);
  void printUsageAndExit();
  int _speed;
  int _batLength;
  int _pointsToWin;
  char _ballTrace;
  int _speedup;
  bool _bell;
  int _argc;
  char** _argv;
};

#endif  // PROJEKT_PARSE_H_
