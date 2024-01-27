//

#include <iostream>
#include <SDL2/SDL.h>
// #include <string>
// #include <vector>
// #include <math.h>
// #include <time.h>

SDL_Window *window;
SDL_Renderer *renderer;

const int WIDTH = 1280 , HEIGHT = 720;

void render(){
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void keyEvent(SDL_Event event){
    switch (event.key.keysym.sym){
        case SDLK_w:{
            if (event.key.repeat == 0 ){
                if (event.key.state == SDL_PRESSED){
                    SDL_Log("key w pressed");
                }
                else if (event.key.state == SDL_RELEASED){
                    SDL_Log("key w released");
                }
            }
        }break;
        case SDLK_a:{
            if (event.key.repeat == 0 ){
                if (event.key.state == SDL_PRESSED){
                    SDL_Log("key a pressed");
                }
                else if (event.key.state == SDL_RELEASED){
                    SDL_Log("key a released");
                }
            }
        }break;
        case SDLK_s:{
            if (event.key.repeat == 0 ){
                if (event.key.state == SDL_PRESSED){
                    SDL_Log("key s pressed");
                }
                else if (event.key.state == SDL_RELEASED){
                    SDL_Log("key s released");
                }
            }
        }break;
        case SDLK_d:{
            if (event.key.repeat == 0 ){
                if (event.key.state == SDL_PRESSED){
                    SDL_Log("key d pressed");
                }
                else if (event.key.state == SDL_RELEASED){
                    SDL_Log("key d released");
                }
            }
        }break;
        case SDLK_DOWN:{
            if (event.key.repeat == 0 ){
                if (event.key.state == SDL_PRESSED){
                    SDL_Log("key down pressed");
                }
                else if (event.key.state == SDL_RELEASED){
                    SDL_Log("key down released");
                }
            }
        }break;
        case SDLK_UP:{
            if (event.key.repeat == 0 ){
                if (event.key.state == SDL_PRESSED){
                    SDL_Log("key up pressed");
                }
                else if (event.key.state == SDL_RELEASED){
                    SDL_Log("key up released");
                }
            }
        }break;
        case SDLK_RIGHT:{
            if (event.key.repeat == 0 ){
                if (event.key.state == SDL_PRESSED){
                    SDL_Log("key right pressed");
                }
                else if (event.key.state == SDL_RELEASED){
                    SDL_Log("key right released");
                }
            }
        }break;
        case SDLK_LEFT:{
            if (event.key.repeat == 0 ){
                if (event.key.state == SDL_PRESSED){
                    SDL_Log("key left pressed");
                }
                else if (event.key.state == SDL_RELEASED){
                    SDL_Log("key left released");
                }
            }
        }break;
    }
}

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("TINY FOODBALL!", SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , WIDTH , HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    
    if (window == NULL){
        std::cout << " window is dead " << SDL_GetError() <<  std::endl;
        return 1;
    }
    renderer = SDL_CreateRenderer( window , -1 , SDL_WINDOW_SHOWN );
    if (renderer == NULL){
        std::cout << " renderer is dead " << SDL_GetError() <<  std::endl;
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);


//game loop
    bool gameRunning = true ; 
    while (gameRunning){
        //event loop
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch (event.type){

                case SDL_QUIT:{
                    gameRunning = false;

                } break;

                //event for keyboard press and release
                case SDL_KEYDOWN:
                case SDL_KEYUP:{
                    keyEvent(event);
                }break;
            }
        }
        render();
    }
    return EXIT_SUCCESS;

}
