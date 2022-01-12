#pragma once
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_stdinc.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>

class PlayerCamera {
private:
  // Constants for speed and sensitivity
  const float movementSpeed = 0.05f;
  const float mouseSensitivity = 0.05f;

  // Player position
  struct position {
    glm::vec4 location;
    float pitch;
    float yaw;
  };

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
