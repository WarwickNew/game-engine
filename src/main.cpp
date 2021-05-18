// Include Config header generated by GNU autotools
#include "../config.h"
#include <GL/glew.h>
// Make sure Glew is loaded first
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
// Not used yet
//#include <glm/glm.hpp>
// File reader
#include <fstream>
#include <iostream>
#include <string>
// Shader
#include "ShaderLoader.h"

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

  // TODO: Understand what a depth buffer is
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

  // TODO: Discover if this is necessary for linux and what values they need be
  // SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  // SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  // SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  // SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  // Create Window
  SDL_Window *window = SDL_CreateWindow(PACKAGE_STRING, SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, 800, 600,
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
  if (window == NULL) {
    error.crash("Unable to initialise SDL Window: ", SDL_GetError());
    return 1;
  }

  // Create glContext
  SDL_GLContext glContext = SDL_GL_CreateContext(window);
  // TODO: Test that glContext was created successfully

  // Tell us the number of vertex attributes allowed in bug reports
  //
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

  ShaderLoader shader("src/vertex.glsl", "src/fragment.glsl");

  float vertices[] = {
      // positions        // texture Co-ords
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
      0.0f,  0.5f,  0.0f, 0.5f, 1.0f  // top
  };

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // texture attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally
  // modify this VAO, but this rarely happens. Modifying other VAOs requires a
  // call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
  // VBOs) when it's not directly necessary. glBindVertexArray(0);

  // Game loop
  bool running = true;
  while (running) {
    // SDL Event handling loop
    while (SDL_PollEvent(&input) > 0) {
      // Handle SDL quit event
      if (input.type == SDL_QUIT) {
        running = false;
      }
      // TODO: Do something with keys lol
    };
    // Clear screen ready for next loop
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Make every shader/rendering call from this point on use our shader
    // glUseProgram(shaderProgram);

    shader.use();

    // I think this is meant to be here but it breaks...
    // shove vertex array into buffer
    glBindVertexArray(VAO);

    // TODO: Run game here lol
    // Draw triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0);

    SDL_GL_SwapWindow(window);
  };

  // Escaped Game loop

  // On close also destroy window
  SDL_DestroyWindow(window);

  // Close all leftover SDL systems
  SDL_Quit();

  return 0;
}
