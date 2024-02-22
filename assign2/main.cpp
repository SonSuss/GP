//2052688
#include "gameCode.cpp"

Button startButton("START", 40, WIDTH/2 , (HEIGHT-gameBarHeight)/2 - 50 , 150 , 70, bcolor, bchange ,tcolor);
Button quitButton("QUIT", 40, WIDTH/2 , (HEIGHT-gameBarHeight)/2 + 50 , 150 , 70, bcolor, bchange ,tcolor);

bool menu(){
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:{
                gameRunning = false;
                break;
            }
            case SDL_MOUSEMOTION:{
                startButton.mouseOn(mouseX, mouseY);
                quitButton.mouseOn(mouseX, mouseY);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:{
                if (event.button.button == SDL_BUTTON_LEFT){
                    if (event.button.state == SDL_RELEASED) {
                        if (quitButton.mousePressed(mouseX, mouseY)){
                            gameRunning = false;
                            break;
                        }
                        return startButton.mousePressed(mouseX, mouseY);
                    } 
                }
                break;
            }
            default: break;
        }
    }
    SDL_Color color = {255,255,255};
    writeText(70 , color, "TINY FOOTBALL!!!", 640 , 185);
    startButton.render(renderer);
    quitButton.render(renderer);
    return false;
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
    if ( TTF_Init() < 0 ) {
        SDL_Log("Text is dead");
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
        SDL_Rect gameBar = {3 , 3, 1274, 44};
        SDL_Rect gameLine1 = {587, 3 , 6 , 44};
        SDL_Rect gameLine2 = {690, 3 , 6 , 44};

        Uint64 performFreq = SDL_GetPerformanceFrequency();
        Uint64 frameStartTime = SDL_GetPerformanceCounter();
        Uint64 frameEndTime, elapsedTime;

        bool phase = false; //0 for menu; 1 for game.
        //game loop
        while (gameRunning){
        SDL_SetRenderDrawColor(renderer, 50, 80, 50, 255);
        SDL_RenderClear( renderer );
            if (phase == false){
                phase = menu();
            }
            else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &gameBarMargin);
                SDL_SetRenderDrawColor(renderer, 30, 80, 30, 255);
                SDL_RenderFillRect(renderer, &gameBar);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &gameLine1);
                SDL_RenderFillRect(renderer, &gameLine2);
                phase = UpdateAndRender(&gameMemory);
                SDL_RenderPresent(renderer);}
            //-- draw things
            // FPS caculate
            frameEndTime = SDL_GetPerformanceCounter();
            elapsedTime = frameEndTime - frameStartTime;
            deltaTime = (double)elapsedTime / (double)performFreq; // v of object = S_per_second * deltaTime
            frameStartTime = frameEndTime;
            // SDL_Log("Delta time: %f, FPS: %f", deltaTime, 1/deltaTime);
            
            // //Cap fps
            // if (FPS - deltaTime * 1000 > 0){
            //     fpsCap =  floor(FPS - deltaTime*1000) + 1;
            //     SDL_Delay(fpsCap);}

            // SDL_Delay(floor(15.666f - deltaTime));
            SDL_RenderPresent(renderer);
        }
    }
    else {
        SDL_Log("Can not get memory for the game");
    }
    return EXIT_SUCCESS;    

}
