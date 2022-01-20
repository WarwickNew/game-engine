#include "PlayerCamera.h"

PlayerCamera::PlayerCamera() {
  this->error = new Error("PlayerCamera");
  SDL_SetRelativeMouseMode(SDL_TRUE);
  SDL_GetRelativeMouseState(nullptr, nullptr);
}

PlayerCamera::~PlayerCamera() { delete this->error; }

void PlayerCamera::tick() {
  SDL_GetRelativeMouseState(&mouseX, &mouseY);

  // adjust rotation based off mouse input
  pos.yaw -= mouseX * mouseSensitivity;
  pos.pitch -= mouseY * mouseSensitivity;
  if (pos.pitch > maxPitch)
    pos.pitch = maxPitch;
  if (pos.pitch < -maxPitch)
    pos.pitch = -maxPitch;

  // Get player forward vector and rotation matrix
  glm::vec4 playerForward;
  glm::mat4 playerRotation;

  playerRotation = glm::rotate(playerRotation, pos.yaw, glm::vec3(0, 1, 0));
  playerRotation = glm::rotate(playerRotation, pos.pitch, glm::vec3(1, 0, 0));
  playerForward = glm::vec4(0, 0, -1, 0) * playerRotation;

  // move camera
  glm::mat4 view =
      glm::lookAt(glm::vec3(pos.location),
                  glm::vec3(pos.location + playerForward), glm::vec3(0, 1, 0));
  glm::mat4 projection =
      glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 1000.0f);
  glm::mat4 transform;

  MVP = projection * view * transform;
}

glm::mat4 PlayerCamera::getMVP() { return MVP; }
