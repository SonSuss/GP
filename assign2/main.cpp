//2052688
#include "gameCode.cpp"

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

    window = SDL_CreateWindow("TINY FOODBALL!", SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , WIDTH , HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);
    
    if (window == NULL){
        SDL_Log("window is dead");
        SDL_GetError();
        return 1;
    }
    renderer = SDL_CreateRenderer( window , -1 , SDL_RENDERER_ACCELERATED /* SDL_RENDERER_PRESENTVSYNC  to set fps as a computer monitor  */ );
    if (renderer == NULL){
        SDL_Log("renderer is dead");
        SDL_GetError() ;
        return 1;
    }

    // set memory for the game
    GameMem gameMemory = {};
    gameMemory.storageSize = 258 * 1024 ; //get memory 258Kb  
    gameMemory.storage = malloc((size_t) gameMemory.storageSize);

    if (gameMemory.storage){
        memset(gameMemory.storage, 0, gameMemory.storageSize);

        SDL_Rect gameBarMargin = {0,0, WIDTH, gameBarHeight};
        SDL_Rect gameBar = {3 , 3, WIDTH - 6, gameBarHeight - 6};
        

        Uint64 performFreq = SDL_GetPerformanceFrequency();
        Uint64 frameStartTime = SDL_GetPerformanceCounter();
        Uint64 frameEndTime, elapsedTime;


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
            

            // render();
            SDL_SetRenderDrawColor(renderer, 50, 80, 50, 255);
            
            SDL_RenderClear(renderer);
            //-- draw things
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &gameBarMargin);

                SDL_SetRenderDrawColor(renderer, 30, 80, 30, 255);
                SDL_RenderFillRect(renderer, &gameBar);



                UpdateAndRender(&gameMemory);
            
            SDL_RenderPresent(renderer);

            // FPS caculate
            frameEndTime = SDL_GetPerformanceCounter();
            elapsedTime = frameEndTime - frameStartTime;
            deltaTime = (double)elapsedTime / (double)performFreq; // v of object = S_per_second * deltaTime
            frameStartTime = frameEndTime;
            //SDL_Log("Delta time: %f, FPS: %f", deltaTime, 1/deltaTime);
            
            

            // //Cap fps
            // if (FPS - deltaTime * 1000 > 0){
            //     fpsCap =  floor(FPS - deltaTime*1000) + 1;
            //     SDL_Delay(fpsCap);}

            // SDL_Delay(floor(15.666f - deltaTime));
            
        }
    }
    else {
        SDL_Log("Can not get memory for the game");
    }
    return EXIT_SUCCESS;    

}
