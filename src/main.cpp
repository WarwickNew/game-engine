#include <GL/glew.h>
// Make sure Glew is loaded first
#include <GL/gl.h>
#include <SDL2/SDL.h>
// File reader
#include <string>
// Shader
#include "ShaderLoader.h"
// Camera
#include "PlayerCamera.h"
#include "helpers/RootDir.h"
// Objects
#include "Mesh.h"
#include "Model.h"
#include "Terrain.h"

// Include error class
#include "Error.h"
Error error("main");

int main(int argc, char **argv) {
  // Initialise SDL2
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    error.crash("Unable to initialise SDL: ", SDL_GetError());
    return 1;
  }

  // Make OpenGL use double buffering (Render game first then shove to output)
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // Initialise depth buffer
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

  // TODO: Discover if this is necessary for linux and what values they need be
  // SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  // SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  // SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  // SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  // Create Window
  SDL_Window *window =
      SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
  if (window == NULL) {
    error.crash("Unable to initialise SDL Window: ", SDL_GetError());
    return 1;
  }

  // Set openGL version so RenderDoc works
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  // Create glContext
  SDL_GLContext glContext = SDL_GL_CreateContext(window);
  if (!glContext) {
    error.crash("No SDL OpenGL Context initialised.");
  }

  // Tell us the number of vertex attributes allowed in bug reports
  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  error.log("Maximum num of vertex attributes supported: " +
            std::to_string(nrAttributes));

  // Initialise Glew
  if (glewInit() != GLEW_OK) {
    error.crash("Unable to initialise GLEW (OpenGL Extention Wrangler)");
  }

  // Create event handling struct
  SDL_Event input;

  ShaderLoader shader(ROOT_DIR "data/shaders/vertex.glsl",
                      ROOT_DIR "data/shaders/fragment.glsl",
                      ROOT_DIR "data/shaders/geometry.glsl");

  // Create player camera object
  PlayerCamera camera;

  // Enable Render order things don't render in front of the wrong objects
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  // glCullFace(GL_FRONT);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  // Initialise terrain.
  Terrain terrain = Terrain();

  // Debug MC table
  Model debugSphere =
      Model(ROOT_DIR "data/game-models/DebugSphere/DebugSphere.obj");
  debugSphere.resize(glm::vec3(0.1f));
  bool index[8] = {true, true, true, true, true, true, true, true};
  Model debugMCsegment = Model(ROOT_DIR "data/game-models/1/MetalFloor.obj");

  // Game loop
  bool running = true;
  while (running) {
    // SDL Event handling loop
    while (SDL_PollEvent(&input) > 0) {
      // Handle SDL quit event
      if (input.type == SDL_QUIT) {
        running = false;
      }
      switch (input.type) {
      case SDL_QUIT:
        running = false;
      case SDL_KEYDOWN:
        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_ESCAPE])
          running = false;
      }
    };

    // TODO: Run game here lol
    camera.tick();

    // Clear screen ready for next loop
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Send our glsl shader our camera information
    shader.setMat4("MVP", camera.getMVP());

    shader.setVec3("CameraPos", camera.getCameraPosition());

    terrain.draw(shader);

    // draw debug sphere at correct config
    debugMCsegment.draw(shader);
    debugSphere.setPosition(glm::vec3(0));
    debugSphere.draw(shader);
    if (index[0] == true) {
      debugSphere.setPosition(glm::vec3(-1, -1, -1));
      debugSphere.draw(shader);
    }
    if (index[1] == true) {
      debugSphere.setPosition(glm::vec3(1, -1, -1));
      debugSphere.draw(shader);
    }
    if (index[2] == true) {
      debugSphere.setPosition(glm::vec3(1, 1, -1));
      debugSphere.draw(shader);
    }
    if (index[3] == true) {
      debugSphere.setPosition(glm::vec3(-1, 1, -1));
      debugSphere.draw(shader);
    }
    if (index[4] == true) {
      debugSphere.setPosition(glm::vec3(-1, -1, 1));
      debugSphere.draw(shader);
    }
    if (index[5] == true) {
      debugSphere.setPosition(glm::vec3(1, -1, 1));
      debugSphere.draw(shader);
    }
    if (index[6] == true) {
      debugSphere.setPosition(glm::vec3(1, 1, 1));
      debugSphere.draw(shader);
    }
    if (index[7] == true) {
      debugSphere.setPosition(glm::vec3(-1, 1, 1));
      debugSphere.draw(shader);
    }

    shader.use();

    SDL_GL_SwapWindow(window);
  };

  // Escaped Game loop

  // On close also destroy window
  SDL_DestroyWindow(window);

  // Close all leftover SDL systems
  SDL_Quit();

  return 0;
}
