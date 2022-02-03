#include "PlayerCamera.h"

PlayerCamera::PlayerCamera() {
  SDL_SetRelativeMouseMode(SDL_TRUE);
  SDL_GetRelativeMouseState(nullptr, nullptr);
}

PlayerCamera::~PlayerCamera() {}

void PlayerCamera::tick() {
  // get camera right
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraForward));

  // get position to look at
  glm::vec3 cameraTarget = cameraPosition + cameraForward;

  // TODO Handle movement speed based on delta time
  // handle keyboard input
  const Uint8 *keyboardState = SDL_GetKeyboardState(nullptr);
  if (keyboardState[SDL_SCANCODE_W])
    cameraPosition += cameraForward * movementSpeed;
  if (keyboardState[SDL_SCANCODE_S])
    cameraPosition -= cameraForward * movementSpeed;
  if (keyboardState[SDL_SCANCODE_A])
    cameraPosition += cameraRight * movementSpeed;
  if (keyboardState[SDL_SCANCODE_D])
    cameraPosition -= cameraRight * movementSpeed;

  // handle mouse
  SDL_GetRelativeMouseState(&mouseX, &mouseY);
  cameraYaw += mouseX * mouseSensitivity;
  cameraPitch -= mouseY * mouseSensitivity;
  // lock pitch to certain range
  if (cameraPitch > 89.0f)
    cameraPitch = 89.0f;
  if (cameraPitch < -89.0f)
    cameraPitch = -89.0f;

  // calculate camera rotation
  glm::vec3 direction;
  direction.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
  direction.y = sin(glm::radians(cameraPitch));
  direction.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
  cameraForward = glm::normalize(direction);

  // MVP stuff
  glm::mat4 model = glm::mat4(1.0f);

  glm::mat4 view;
  view = glm::lookAt(cameraPosition, cameraTarget, up);

  glm::mat4 projection = glm::perspective(
      glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

  MVP = projection * view * model;
}

glm::mat4 PlayerCamera::getMVP() { return MVP; }
