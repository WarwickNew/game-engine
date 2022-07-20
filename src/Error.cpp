#include "Error.h"

Error::Error(std::string location) { object = location; }
const void Error::crash(std::string msg) const {
  log("Error: " + msg);
  throw std::string(object + ": \n" + msg);
}
const void Error::crash(std::string reason, std::string msg) const {
  log("Error: " + reason + ": \n" + msg);
  throw std::string(object + ": \n" + reason + ": \n" + msg);
}
const void Error::warn(std::string msg) const {
  log("Warining: " + msg);
  // throw object + ": " + msg;
}
const void Error::log(std::string msg) const {
  std::cout << object << ": \n" << msg << std::endl;
}
