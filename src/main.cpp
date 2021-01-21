//#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

//TODO: Create Error handling class

int main(int argc, char ** argv){
    // Initialise SDL2
    //TODO: Check if sdl initialised
    SDL_Init(SDL_INIT_EVERYTHING);

    //Make OpenGL use double buffering (Render game first then shove to output)
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //TODO: Understand what a depth buffer is
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

    //TODO: Discover if thid is necessary for linux and what values they need be
    //SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    //SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    //SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    //SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    
    // Create Window
    SDL_Window *window =
        SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                800, 600, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
    //TODO: Test that window was created successfully

    //Create glContext
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    //TODO: Test that glContext was created successfully

    //Initialise Glew
    if (glewInit() != GLEW_OK){
        //TODO: Throw an error lol
    }


    //Create event handling struct
    SDL_Event input;

    // Game loop
    bool running = true;
    while(running){
        //SDL Event handling loop
        while (SDL_PollEvent(&input) > 0){
            // Handle SDL quit event
            if (input.type == SDL_QUIT){
                running = false;
            }
            //TODO: Do something with keys lol

        };
    };

    // Escaped Game loop

    // On close also destroy window
    SDL_DestroyWindow(window);

    // Close all leftover SDL systems
    SDL_Quit();

    return 0;
}
