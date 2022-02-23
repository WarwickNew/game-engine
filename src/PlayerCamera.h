#pragma once
#include "Error.h"
#include <SDL2/SDL_keyboard.h>
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
  const float movementSpeed = 0.02f;
  const float mouseSensitivity = 0.05f;

  // Player position
  glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 cameraForward = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 cameraUp = glm::vec3(0.0f, 0.0f, -1.0f);
  float cameraYaw = -90.0f;
  float cameraPitch = 0.0f;

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