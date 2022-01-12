#include "PlayerCamera.h"

PlayerCamera::PlayerCamera() {
  SDL_SetRelativeMouseMode(SDL_TRUE);
  SDL_GetRelativeMouseState(nullptr, nullptr);
}

PlayerCamera::~PlayerCamera() {}

void PlayerCamera::tick() {}

glm::mat4 PlayerCamera::getMVP() {}
