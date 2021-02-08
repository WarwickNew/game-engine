#include "Error.h"

Error::Error(std::string location) { object = location; }
void Error::crash(std::string msg) { throw object + ": " + msg; }
void Error::crash(std::string reason, std::string msg) {
  throw object + ": " + reason + ": " + msg;
}
void Error::warn(std::string msg) { throw object + ": " + msg; }
void Error::log(std::string msg) { throw object + ": " + msg; }
