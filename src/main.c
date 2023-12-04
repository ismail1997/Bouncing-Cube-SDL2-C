#include<SDL2/SDL.h>
#include<stdbool.h>
#include"settings.h"
#include"game.h"


int main(int argc, char**argv)
{

    SDL_Window * window =NULL;
    SDL_Renderer * renderer =NULL;
    struct Cube * cube =NULL;

    //init the game ( window, renderer, the cube)
    initGame(&window,&renderer,&cube);

    bool gameOver = false;

    while(!gameOver)
    {


        handleEvent(&window,&renderer,&cube);

        updateScene(&cube);

        renderScene(&renderer,&cube);

        SDL_Delay(1000/FPS_LIMIT);
    }

    return 0;
}