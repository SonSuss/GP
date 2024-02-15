#ifndef main
#define main

#include <iostream>
#include <SDL2/SDL.h>
#include <stdint.h>
// #include <math.h>
// #include <string>
// #include <vector>
// #include <time.h>


SDL_Window *window;
SDL_Renderer *renderer;

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