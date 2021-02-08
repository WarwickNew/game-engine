#pragma once
#include <string>

class Error {
private:
  // this string gives us the name of the object the error occured in
  std::string object;

public:
  Error(std::string location);
};
