#pragma once
#include <iostream>
#include <string>

class Error {
private:
  // this string gives us the name of the object the error occured in
  std::string object;

public:
  Error(std::string location);

  // TODO: make the crash break game loop
  void crash(std::string msg);
  void crash(std::string reason, std::string msg);
  void warn(std::string msg);
  // TODO: write log issues to a file rather than throw
  void log(std::string msg);
};
