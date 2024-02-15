#include "gameCode.h"

const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);


Entity *player1a;
Entity *player1b;
std::vector <Entity*> player1;
Entity *currentPlayer1;

std::vector <Entity*> player2;
Entity *currentPlayer2;

void UpdateAndRender(GameMem *gameMemory){
    GameState *gameState = (GameState*)gameMemory->storage;

    // init everything in the memory for the first time 
    if(!gameMemory->initialized){
        gameState->entityCount++; // skip the 0 entity cuz 0 = false 
        // the walls
        gameState->entities[gameState->entityCount++] = new Wall(0 ,gameBarHeight,WIDTH, 15, 190, 190, 190, 255);//wall1
        gameState->entities[gameState->entityCount++] = new Wall(0 ,HEIGHT - 15 , WIDTH, 15, 190, 190, 190, 255);//wall2
        gameState->entities[gameState->entityCount++] = new Wall(0 , gameBarHeight , 15 , (HEIGHT-gameBarHeight)/5 * 2 , 190, 190, 190, 255);//wall3
        gameState->entities[gameState->entityCount++] = new Wall(0 ,gameBarHeight + (HEIGHT-gameBarHeight)/5 * 3 , 15 , (HEIGHT-gameBarHeight)/5 * 2  , 190, 190, 190, 255);//wall4
        gameState->entities[gameState->entityCount++] = new Wall(WIDTH - 15 , gameBarHeight , 15 , (HEIGHT-gameBarHeight)/5 * 2  , 190, 190, 190, 255);//wall5
        gameState->entities[gameState->entityCount++] = new Wall(WIDTH - 15 ,gameBarHeight + (HEIGHT-gameBarHeight)/5 * 3  ,15,(HEIGHT-gameBarHeight)/5 * 2 , 190, 190, 190, 255);//wall6

        //player
        //player 1
        gameState->entities[gameState->entityCount] = new Player(30 ,gameBarHeight + (HEIGHT-gameBarHeight)/2 - playerHeight / 2 - 50,0.0f, 300, 255,51,51,255) ;//player1
        player1.insert(player1.begin(), gameState->entities[gameState->entityCount]);gameState->entityCount++;
        gameState->entities[gameState->entityCount] = new Player(30 ,gameBarHeight + (HEIGHT-gameBarHeight)/2 - playerHeight / 2 + 50 ,0.0f, 300, 255,51,51,255) ;//player1
        player1.insert(player1.begin(), gameState->entities[gameState->entityCount]);gameState->entityCount++;
        gameState->entities[gameState->entityCount] = new Player(130 ,gameBarHeight + (HEIGHT-gameBarHeight)/2 - playerHeight / 2  ,0.0f, 300, 255,51,51,255) ;//player1
        player1.insert(player1.begin(), gameState->entities[gameState->entityCount]);gameState->entityCount++;
        currentPlayer1 = player1.back();
        player1.pop_back();
        currentPlayer1->choose();
        
        //player 2   30 - 60 
        gameState->entities[gameState->entityCount] = new Player(WIDTH - 30 - 30 , gameBarHeight + (HEIGHT-gameBarHeight)/2 - playerHeight / 2 - 50, 0.0f, 300, 0,128,255 ,255) ;//player2
        player2.insert(player2.begin(), gameState->entities[gameState->entityCount]);gameState->entityCount++;
        gameState->entities[gameState->entityCount] = new Player(WIDTH - 30 - 30  ,gameBarHeight + (HEIGHT-gameBarHeight)/2 - playerHeight / 2 +50 ,0.0f, 300, 0,128,255,255) ;//player2
        player2.insert(player2.begin(), gameState->entities[gameState->entityCount]);gameState->entityCount++;
        gameState->entities[gameState->entityCount] = new Player(WIDTH - 30 - 30 - 100 ,gameBarHeight + (HEIGHT-gameBarHeight)/2 - playerHeight / 2  ,0.0f, 300, 0,128,255,255) ;//player2
        player2.insert(player2.begin(), gameState->entities[gameState->entityCount]);gameState->entityCount++;
        currentPlayer2 = player2.back();
        player2.pop_back();
        currentPlayer2->choose();

        //ball
        gameState->entities[gameState->entityCount++] = new Ball(WIDTH / 2, gameBarHeight + (HEIGHT-gameBarHeight)/2, 15);

        gameMemory->initialized = true;
    }


    {
    // key to move every thing =)) 
    if (currentKeyStates[SDL_SCANCODE_W]) {
    // Action to perform when W key is held
        SDL_Log("key W is being pressed");
        currentPlayer1->moveUp();
    }

    if (currentKeyStates[SDL_SCANCODE_A]) {
        // Action to perform when A key is held
        SDL_Log("key A is being pressed");
        currentPlayer1->moveLeft();
    }

    if (currentKeyStates[SDL_SCANCODE_S]) {
        // Action to perform when S key is held
        SDL_Log("key S is being pressed");
        currentPlayer1->moveDown();
    }

    if (currentKeyStates[SDL_SCANCODE_D]) {
        // Action to perform when D key is held
        SDL_Log("key D is being pressed");
        currentPlayer1->moveRight();
    }
    // Movement for player 2
    if (currentKeyStates[SDL_SCANCODE_UP]) {
        // Action to perform when Up Arrow key is held
        SDL_Log("Up Arrow key is being pressed");
        currentPlayer2->moveUp();
    }

    if (currentKeyStates[SDL_SCANCODE_LEFT]) {
        // Action to perform when Left Arrow key is held
        SDL_Log("Left Arrow key is being pressed");
        currentPlayer2->moveLeft();
    }

    if (currentKeyStates[SDL_SCANCODE_DOWN]) {
        // Action to perform when Down Arrow key is held
        SDL_Log("Down Arrow key is being pressed");
        currentPlayer2->moveDown();
    }

    if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
        // Action to perform when Right Arrow key is held
        SDL_Log("Right Arrow key is being pressed");
        currentPlayer2->moveRight();
    }
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:{
                gameRunning = false;
                break;
            }
            //event for keyboard press and release
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                switch (event.key.keysym.sym){
                    case SDLK_e: {
                        if (event.key.repeat == 0) {
                            if (event.key.state == SDL_PRESSED) {
                                // Swap players when E key is pressed
                                SDL_Log("key E press");
                                currentPlayer1->choose();
                                player1.insert(player1.begin(),currentPlayer1);
                                currentPlayer1 = player1.back();
                                player1.pop_back();
                                currentPlayer1->choose();
                            }
                            // Note: You can add additional handling for SDL_RELEASED if needed
                        }
                    }
                    case SDLK_SLASH: {
                        if (event.key.repeat == 0) {
                            if (event.key.state == SDL_PRESSED) {
                                // Swap players when E key is pressed
                                SDL_Log("key E press");
                                currentPlayer2->choose();
                                player2.insert(player2.begin(),currentPlayer2);
                                currentPlayer2 = player2.back();
                                player2.pop_back();
                                currentPlayer2->choose();
                            }
                            // Note: You can add additional handling for SDL_RELEASED if needed
                        }
                    }
                    default: break;
                }
            }
            default: break;
        }
    }


    // Hit the ball and move it


    for (int e_i = 1; e_i < gameState->entityCount ; e_i++){
        gameState->entities[e_i]->UpdateAndDraw();
    };

}