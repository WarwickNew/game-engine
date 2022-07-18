#pragma once
#include <GL/glew.h>
// Make sure Glew is loaded first
#include <GL/gl.h>
// File reader
#include "Error.h"
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

class ShaderLoader {
private:
  unsigned int ID;
  Error error = Error("ShaderLoader");

public:
  // constructor builds shader
  ShaderLoader(const char *vertexPath, const char *fragmentPath);

  // use the shader
  void use();

  // utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setMat4(const std::string &name, glm::mat4 value) const;
  void setVec3(const std::string &name, glm::vec3 value) const;
};
