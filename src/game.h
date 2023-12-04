#ifndef __GAME__H
#define __GAME__H

#include<SDL2/SDL.h>
#include<stdbool.h>


struct Cube{
    float x;
    float y;
    float velocity;
    bool isBouncing;
};


// method to init game 
void initSDL(void);
void initGame(SDL_Window **window, SDL_Renderer **renderer,struct Cube **cube);
void initWindow(SDL_Window **window);
void initRenderer(SDL_Window **window, SDL_Renderer **renderer);
void cleanAll(SDL_Window **window,SDL_Renderer **renderer, struct Cube **cube);
void createCube(SDL_Window **window , SDL_Renderer **renderer, struct Cube **cube);

void handleEvent(SDL_Window **window, SDL_Renderer **renderer, struct Cube **cube);
void updateScene(struct Cube **cube);
void renderScene(SDL_Renderer **renderer ,struct Cube **cube);

#endif