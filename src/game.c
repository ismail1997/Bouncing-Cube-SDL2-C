#include"settings.h"
#include"game.h"
#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>


void initGame(SDL_Window **window,SDL_Renderer **renderer,struct Cube ** cube)
{
    initSDL();
    initWindow(window);
    initRenderer(window,renderer);
    createCube(window,renderer,cube);
}


void initSDL(void)
{
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        SDL_Log("Error initialiazing SDL :%s\n",SDL_GetError());
        exit(1);
    }
}
void cleanAll(SDL_Window **window,SDL_Renderer **renderer, struct Cube **cube)
{
    if(*renderer !=NULL){
        SDL_DestroyRenderer(*renderer);
        *renderer=NULL;
    }
    if(*window!=NULL){
        SDL_DestroyWindow(*window);
        *window=NULL;
    }
    if(*cube!=NULL)
    {
        free(*cube);
        *cube=NULL;
    }
}
void initWindow(SDL_Window **window)
{
   *window = SDL_CreateWindow(GAME_NAME,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN); 
   if(*window==NULL)
   {
    SDL_Log("Error creating the window :%s\n",SDL_GetError());
    cleanAll(NULL,NULL,NULL);
    exit(1);
   }
}

void initRenderer(SDL_Window **window, SDL_Renderer **renderer)
{
    *renderer = SDL_CreateRenderer(*window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(*renderer ==NULL)
    {
        SDL_Log("Error creating renderer :%s\n",SDL_GetError());
        cleanAll(window,NULL,NULL);
        exit(1);
    }
}

void createCube(SDL_Window **window , SDL_Renderer **renderer, struct Cube **cube)
{
    *cube=malloc(sizeof(struct Cube));
    if(*cube==NULL){
        fprintf(stderr,"Error creating the cube 2D \n");
        cleanAll(window,renderer,NULL);
        exit(1);
    }

    (*cube)->x=SCREEN_WIDTH/2 -CUBE_SIZE/2 ;
    (*cube)->y=SCREEN_HEIGHT-GROUND_HEIGHT-CUBE_SIZE;
    (*cube)->velocity=0.0;
    (*cube)->isBouncing=false;
}


void handleEvent(SDL_Window **window, SDL_Renderer **renderer, struct Cube **cube)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
            {
                cleanAll(window,renderer,cube);
                exit(0);
            }
            case SDL_KEYDOWN:{
                if(event.key.keysym.sym==SDLK_SPACE && !(*cube)->isBouncing)
                {
                    (*cube)->velocity=-BOUNCING_FORCE;
                    (*cube)->isBouncing=true;
                }
                break;
            }
        }
    }
}


void updateScene(struct Cube **cube)
{
    (*cube)->y += (*cube)->velocity ;// s=ut
    (*cube)->velocity +=GRAVITY_FORCE;//v = u +at;

    if((*cube)->y > SCREEN_HEIGHT-CUBE_SIZE){
        (*cube)->y = SCREEN_HEIGHT-CUBE_SIZE;
        (*cube)->velocity=0.0;
        (*cube)->isBouncing =false;
    }
}


void renderScene(SDL_Renderer **renderer ,struct Cube **cube)
{
    SDL_SetRenderDrawColor(*renderer,0,0,0,255);
    SDL_RenderClear(*renderer);

    SDL_Rect ground = {0,SCREEN_HEIGHT-GROUND_HEIGHT,SCREEN_WIDTH,GROUND_HEIGHT};
    SDL_SetRenderDrawColor(*renderer,30,30,30,255);
    SDL_RenderFillRect(*renderer,&ground);

    //render cube 
    SDL_Rect cubeShape;
    cubeShape.x = (int) (*cube)->x;
    cubeShape.y = (int) (*cube)->y-GROUND_HEIGHT;
    cubeShape.w = CUBE_SIZE;
    cubeShape.h = CUBE_SIZE;
    SDL_SetRenderDrawColor(*renderer,50,145,255,255);
    SDL_RenderFillRect(*renderer,&cubeShape);
    
    SDL_RenderPresent(*renderer);
}