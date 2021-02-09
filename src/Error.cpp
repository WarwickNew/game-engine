#include "Error.h"

Error::Error(std::string location) { object = location; }
void Error::crash(std::string msg) {
  log("Error: " + msg);
  throw object + ": \n" + msg;
}
void Error::crash(std::string reason, std::string msg) {
  log("Error: " + reason + ": \n" + msg);
  throw object + ": \n" + reason + ": \n" + msg;
}
void Error::warn(std::string msg) {
  log("Warining: " + msg);
  // throw object + ": " + msg;
}
void Error::log(std::string msg) {
  std::cout << object << ": \n" << msg << std::endl;
}
