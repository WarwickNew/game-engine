#include "ShaderLoader.h"
#include <iostream>

// This function always expects vertex and fragment shaders, if a geometry
// shader is present then it will also compile in that boi too.
// TODO: Make this code more readable and reduce the number of if statements.
void ShaderLoader::loadShader(const char *vertexPath, const char *fragmentPath,
                              const char *geometryPath) {
  std::string vertexCode;
  std::string fragmentCode;
  std::string geometryCode;

  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  std::ifstream gShaderFile;

  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  if (geometryPath != nullptr)
    gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // Open Files
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    if (geometryPath != nullptr)
      gShaderFile.open(geometryPath);
    std::stringstream vShaderStream, fShaderStream, gShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    if (geometryPath != nullptr)
      gShaderStream << gShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    if (geometryPath != nullptr)
      gShaderFile.close();
    // convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
    if (geometryPath != nullptr)
      geometryCode = gShaderStream.str();
  } catch (std::string e) {
    error.crash("Failed to read shaderfiles", e);
  }
  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();
  const char *gShaderCode = geometryCode.c_str();

  // Compile shaders
  unsigned int vertex, fragment, geometry;
  int success;
  char infoLog[512];

  // Vertex Shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  // Try to communicate errors if they exist
  glGetShaderInfoLog(vertex, 512, NULL, infoLog);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    std::cout << infoLog << success << std::endl;
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    error.crash("Vertex shader compilation failed", infoLog);
  }

  // create fragment shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  // compile fragment shader
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  // https://learnopengl.com/Getting-started/Hello-Triangle
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    error.crash("Fragment shader compilation failed", infoLog);
  }

  // create geometry shader
  if (geometryPath != nullptr) {
    geometry = glCreateShader(GL_GEOMETRY_SHADER);
    // compile fragment shader
    glShaderSource(geometry, 1, &gShaderCode, NULL);
    glCompileShader(geometry);
    // https://learnopengl.com/Getting-started/Hello-Triangle
    glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(geometry, 512, NULL, infoLog);
      error.crash("Geometry shader compilation failed", infoLog);
    }
  }
  // shader Program
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  if (geometryPath != nullptr)
    glAttachShader(ID, geometry);
  glLinkProgram(ID);
  // print linking errors if any
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    error.crash("Shader Linking failed", infoLog);
  }

  // delete the shaders as they're linked into our program now and no longer
  // necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
  glDeleteShader(geometry);
}

ShaderLoader::ShaderLoader(const char *vertexPath, const char *fragmentPath,
                           const char *geometryPath) {
  this->loadShader(vertexPath, fragmentPath, geometryPath);
}

ShaderLoader::ShaderLoader(const char *vertexPath, const char *fragmentPath) {
  this->loadShader(vertexPath, fragmentPath, nullptr);
}

void ShaderLoader::use() { glUseProgram(ID); }
void ShaderLoader::setBool(const std::string &name, bool value) const {
  int uniformLocation = glGetUniformLocation(ID, name.c_str());
  glUniform1i(uniformLocation, (int)value);

  if (uniformLocation == -1)
    error.warn("Uniform location " + name + " not found");
}
void ShaderLoader::setInt(const std::string &name, int value) const {
  int uniformLocation = glGetUniformLocation(ID, name.c_str());
  glUniform1i(uniformLocation, value);

  if (uniformLocation == -1)
    error.warn("Uniform location " + name + " not found");
}
void ShaderLoader::setFloat(const std::string &name, float value) const {
  int uniformLocation = glGetUniformLocation(ID, name.c_str());
  glUniform1f(uniformLocation, value);

  if (uniformLocation == -1)
    error.warn("Uniform location " + name + " not found");
}
void ShaderLoader::setMat4(const std::string &name, glm::mat4 value) const {
  int uniformLocation = glGetUniformLocation(ID, name.c_str());
  glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &value[0][0]);

  if (uniformLocation == -1)
    error.warn("Uniform location " + name + " not found");
}
void ShaderLoader::setVec3(const std::string &name, glm::vec3 value) const {
  int uniformLocation = glGetUniformLocation(ID, name.c_str());
  glUniform3fv(uniformLocation, 1, glm::value_ptr(value));

  if (uniformLocation == -1)
    error.warn("Uniform location " + name + " not found");
}
