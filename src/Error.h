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
  const void crash(std::string msg) const;
  const void crash(std::string reason, std::string msg) const;
  const void warn(std::string msg) const;
  // TODO: write log issues to a file rather than throw
  const void log(std::string msg) const;
};
