#include "gameCode.h"


void setFRect(SDL_FRect *rect, float x, float y, float width, float height){
    rect->x = x;
    rect->y = y;
    rect->w = width;
    rect->h = height;
}

void UpdateAndRender(GameMem *gameMemory){
    GameState *gameState = (GameState*)gameMemory->storage;

    // init everything in the memory for the first time 
    if(!gameMemory->initialized){
        setFRect(&gameState->rect, 5.0, HEIGHT /2 - playerHeight /2 , playerWidth, playerHeight);

        gameMemory->initialized = true;
    }
    gameState->rect.x += 120 * deltaTime;

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderFillRectF(renderer, &gameState->rect);

}