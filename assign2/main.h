#ifndef main
#define main

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdint.h>
// #include <math.h>
// #include <string>
// #include <vector>
// #include <time.h>


SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font* font ;
SDL_Color bcolor = {0, 102, 0};
SDL_Color bchange = {102,30,0};
SDL_Color tcolor = {255,255,255};

// unlitmited FPS
double deltaTime;
// // cap FPS
// double FPS = 1000 / /*FPS go here ->*/ 60.0;
// Uint32 fpsCap; //ms

bool gameRunning = true ; 

const int gameBarHeight = 50 ;

const float playerHeight = 60, playerWidth = 30 ;

const int WIDTH = 1280 , HEIGHT = 720;

struct GameMem
{   
    bool initialized = false ;
    Uint64 storageSize;
    void *storage; 
};


#endif //main   //