#pragma once
#include "Error.h"
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_stdinc.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <string>

class PlayerCamera {
private:
  // Constants for speed and sensitivity
  const float movementSpeed = 0.05f;
  const float mouseSensitivity = 0.05f;
  const float maxPitch = glm::radians(89.0f);

  // Player position
  struct CameraPosition {
    glm::vec4 location;
    float pitch;
    float yaw;
  } pos;

  // Mouse position
  int mouseX, mouseY;

  // Camera position
  glm::mat4 MVP;

  // Error
  Error *error = nullptr;

public:
  PlayerCamera();

  ~PlayerCamera();

  void tick();

  glm::mat4 getMVP();
};
