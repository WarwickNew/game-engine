// TODO: Stop this fuckery
const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

//#include <iostream>
#include <GL/glew.h>
// Make sure Glew is loaded first
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// TODO: Create Error handling class

int main(int argc, char **argv) {
  // Initialise SDL2
  // TODO: Check if sdl initialised
  SDL_Init(SDL_INIT_EVERYTHING);

  // Make OpenGL use double buffering (Render game first then shove to output)
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // TODO: Understand what a depth buffer is
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

  // TODO: Discover if thid is necessary for linux and what values they need be
  // SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  // SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  // SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  // SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  // Create Window
  SDL_Window *window =
      SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
  // TODO: Test that window was created successfully

  // Create glContext
  SDL_GLContext glContext = SDL_GL_CreateContext(window);
  // TODO: Test that glContext was created successfully

  // Initialise Glew
  if (glewInit() != GLEW_OK) {
    // TODO: Throw an error lol
  }

  // Create event handling struct
  SDL_Event input;

  // test square!
  float vertices[] = {
      0.5f,  0.5f,  0.0f, // top right
      0.5f,  -0.5f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f  // top left
  };
  unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  // Vertex Buffer Object
  unsigned int VBO;
  glGenBuffers(1, &VBO);

  // Bind the buffer and size it to the data provided
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Create vertex array that will populate buffer
  unsigned int VAO;
  glCreateVertexArrays(1, &VAO);
  glEnableVertexArrayAttrib(VAO, 0);

  // set up vertex array atributes
  glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

  // set up vbo for vao
  glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(float) * 3);

  // shove vertex array into buffer
  glBindVertexArray(VAO);

  // Create element buffer (allows the use of indices)
  unsigned int EBO;
  glGenBuffers(1, &EBO);

  // Bind element Buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // create vertex shader
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // compile vertex shader
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // TODO: test the shader was compiled
  // https://learnopengl.com/Getting-started/Hello-Triangle

  // create fragment shader
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  // compile fragment shader
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // TODO: test the shader was compiled
  // https://learnopengl.com/Getting-started/Hello-Triangle

  // Tell openGL how to interpret vertex data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Create the shader program
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  // Attach shaders to the shader program
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // TODO: test the shader was linked
  // https://learnopengl.com/Getting-started/Hello-Triangle

  // Clean up shader creation stuff from memory
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

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
    glUseProgram(shaderProgram);

    // I think this is meant to be here but it breaks...
    // shove vertex array into buffer
    glBindVertexArray(VAO);

    // TODO: Run game here lol
    // Draw triangle
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    SDL_GL_SwapWindow(window);
  };

  // Escaped Game loop

  // On close also destroy window
  SDL_DestroyWindow(window);

  // Close all leftover SDL systems
  SDL_Quit();

  return 0;
}
