#pragma once
#include "Error.h"
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_stdinc.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>

class PlayerCamera {
private:
  // Error reporting class
  Error error = Error("PlayerCamera");
  // Constants for speed and sensitivity
  const float movementSpeed = 0.005f;
  const float mouseSensitivity = 0.005f;

  // Player position
  struct position {
    glm::vec4 vectorPos;
    float pitch;
    float yaw;
  } pos;

  // Mouse position
  int mouseX, mouseY;

  // Camera position
  glm::mat4 MVP;

public:
  PlayerCamera();

  ~PlayerCamera();

  void tick();

  glm::mat4 getMVP();
};
