#include "PlayerCamera.h"

PlayerCamera::PlayerCamera() {
  SDL_SetRelativeMouseMode(SDL_TRUE);
  SDL_GetRelativeMouseState(nullptr, nullptr);
}

PlayerCamera::~PlayerCamera() {}

void PlayerCamera::tick() {
  pos.vectorPos = glm::vec4(0.0f, 0.0f, 5.0f, 1.0f);
  // Get the mouse movement
  int mouseX, mouseY;
  SDL_GetRelativeMouseState(&mouseX, &mouseY);

  // Calculate rotation
  pos.yaw -= mouseX * mouseSensitivity;
  pos.pitch -= mouseX * mouseSensitivity;

  // Stop camera from looking too far up/down
  const float maxPitch = glm::radians(89.0f);
  if (pos.pitch > maxPitch)
    pos.pitch = maxPitch;
  if (pos.pitch < -maxPitch)
    pos.pitch = -maxPitch;

  glm::vec4 playerForward(0.0f, 0.0f, -1.0f, 0.0f);
  glm::mat4 playerRotation;
  // Rotate yaw
  playerRotation =
      glm::rotate(playerRotation, pos.yaw, glm::vec3(0.0f, 1.0f, 0.0f));
  // Rotate pitch
  playerRotation =
      glm::rotate(playerRotation, pos.pitch, glm::vec3(1.0f, 0.0f, 0.0f));
  playerForward = playerRotation * playerForward;

  // until we add keyboard stuff set the position to a static value

  // create MVP
  glm::mat4 view = glm::lookAt(
      glm::vec3(pos.vectorPos),
      glm::vec3(pos.vectorPos +
                playerForward /* glm::vec4(0.0f, 0.0f, -1.0f, 0.0f) */),
      glm::vec3(0.0f, 1.0f, 0.0f));

  // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1
  // unit <-> 100 units
  float width = 800;
  float height = 600;
  glm::mat4 projection = glm::perspective(
      glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
  glm::mat4 transform = glm::mat4(1.0f);

  MVP = projection * view * transform;
}

glm::mat4 PlayerCamera::getMVP() { return MVP; }
