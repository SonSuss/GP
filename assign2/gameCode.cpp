#include "gameCode.h"
#include "Button.cpp"

const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);


const char* intToConstChar(int num) {
    std::string str = std::to_string(num);
    return str.c_str();
}


float gameTimeSet = 90.0f;
float timePassed = 0.0f;
int timeSeconds = 0;


std::vector <Entity*> player1;
Entity *currentPlayer1;
int player1score =0;


std::vector <Entity*> player2;
Entity *currentPlayer2;
int player2score = 0;

Entity *ball;

Button resumeButton("RESUME", 30, 640, 250, 200, 50, bcolor,bchange, tcolor);

Button restartButton("RESTART",30, 640, 350, 200, 50, bcolor,bchange, tcolor);

Button menuButton("MENU", 30, 640, 450 , 200, 50, bcolor,bchange, tcolor);

Button pressEtoRestartButton("Press E To Restart",30, 640, 420 , 300, 50, bcolor,bchange, tcolor);

bool gamePasued = false;

bool UpdateAndRender(GameMem *gameMemory){
    GameState *gameState = (GameState*)gameMemory->storage;
    timeSeconds = (int)(gameTimeSet - timePassed);
    // init everything in the memory for the first time 
    if(!gameMemory->initialized){
        gameState->entityCount++; // skip the 0 entity cuz 0 = false 

        //  the walls
        gameState->entities[gameState->entityCount++] = new Wall(0 ,gameBarHeight,WIDTH, 15, 190, 190, 190, 255);//wall1
        gameState->entities[gameState->entityCount++] = new Wall(0 ,HEIGHT - 15 , WIDTH, 15, 190, 190, 190, 255);//wall2
        // /*test*/ gameState->entities[gameState->entityCount++] = new Wall(0 , gameBarHeight , 15 , (HEIGHT-gameBarHeight), 190, 190, 190, 255);//wall3
        // /*test*/ gameState->entities[gameState->entityCount++] = new Wall(WIDTH - 15 , gameBarHeight , 15 , (HEIGHT-gameBarHeight)  , 190, 190, 190, 255);//wall5
        gameState->entities[gameState->entityCount++] = new Wall(0 , gameBarHeight , 15 , (HEIGHT-gameBarHeight)/5 * 2 , 190, 190, 190, 255);//wall3
        gameState->entities[gameState->entityCount++] = new Wall(0 ,gameBarHeight + (HEIGHT-gameBarHeight)/5 * 3 , 15 , (HEIGHT-gameBarHeight)/5 * 2  , 190, 190, 190, 255);//wall4
        gameState->entities[gameState->entityCount++] = new Wall(WIDTH - 15 , gameBarHeight , 15 , (HEIGHT-gameBarHeight)/5 * 2  , 190, 190, 190, 255);//wall5
        gameState->entities[gameState->entityCount++] = new Wall(WIDTH - 15 ,gameBarHeight + (HEIGHT-gameBarHeight)/5 * 3  ,15,(HEIGHT-gameBarHeight)/5 * 2 , 190, 190, 190, 255);//wall6  
        // player
        // player 1
        gameState->entities[gameState->entityCount] = new Player(30 ,gameBarHeight + (HEIGHT-gameBarHeight)/2 - playerHeight / 2 - 50,0.0f, 300, 255,51,51,255) ;//player1
        player1.insert(player1.begin(), gameState->entities[gameState->entityCount]);gameState->entityCount++;
        gameState->entities[gameState->entityCount] = new Player(30 ,gameBarHeight + (HEIGHT-gameBarHeight)/2 - playerHeight / 2 + 50 ,0.0f, 300, 255,51,51,255) ;//player1
        player1.insert(player1.begin(), gameState->entities[gameState->entityCount]);gameState->entityCount++;
        gameState->entities[gameState->entityCount] = new Player(100 ,gameBarHeight + (HEIGHT-gameBarHeight)/2 - playerHeight / 2  ,0.0f, 300, 255,51,51,255) ;//player1
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
        gameState->entities[gameState->entityCount] = new Ball(WIDTH / 2 - 300, gameBarHeight + (HEIGHT-gameBarHeight)/2, 12);
        ball = gameState->entities[gameState->entityCount++];

        gameMemory->initialized = true;
    }
    const char *phayer1scoreC = intToConstChar(player1score);
    SDL_Color white = {255,255,255};
    writeText(40, white , phayer1scoreC , 440 , 25);
    const char *phayer2scoreC = intToConstChar(player2score);
    writeText(40, white , phayer2scoreC , 820 , 25);
    writeText(40, white , ":" , 640 , 23);
    const char *minute = intToConstChar((int)(timeSeconds/60));
    writeText(30, white , minute , 620 , 25);
    const char *second = intToConstChar(timeSeconds % 60);
    writeText(30, white , second , 670 , 25);
    //time up
    if (timeSeconds <= 0 ){
        SDL_Color white = {255,255,255};
        if (player1score == player2score){
            writeText(40,white,"DRAW!",640, 360);
        }
        if (player1score > player2score){
            writeText(40,white,"PLAYER 1 WIN!",640, 360);
        }
        if (player1score < player2score){
            writeText(40,white,"PLAYER 2 WIN!",640, 360);
        }   
        pressEtoRestartButton.render(renderer);
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
                    pressEtoRestartButton.mouseOn(mouseX, mouseY);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:{
                    if (event.button.button == SDL_BUTTON_LEFT){
                        if (event.button.state == SDL_RELEASED) {
                            if (pressEtoRestartButton.mousePressed(mouseX, mouseY)){
                                gameMemory->initialized = false;
                                gameState->entityCount = 0;
                                player1.clear();
                                player2.clear();
                                gamePasued = false;
                                // reset score and timer
                                timePassed = 0.0f;
                                player1score = 0;
                                player2score = 0;

                            }
                        break;
                        } 
                    }
                    break;
                }   
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                {
                    switch (event.key.keysym.sym){
                        case SDLK_ESCAPE:{
                            if (event.key.repeat == 0){
                                if (event.key.state == SDL_RELEASED){
                                    gameMemory->initialized = false;
                                    gameState->entityCount = 0;
                                    player1.clear();
                                    player2.clear();
                                    // reset score and timer
                                    timePassed = 0.0f;
                                    player1score = 0;
                                    player2score = 0;
                                    return false;
                                }
                            }
                            break;
                        }
                        case SDLK_e:{
                            if (event.key.repeat == 0){
                                if (event.key.state == SDL_RELEASED){
                                    gameMemory->initialized = false;
                                    gameState->entityCount = 0;
                                    player1.clear();
                                    player2.clear();
                                    // reset score and timer
                                    timePassed = 0.0f;
                                    player1score = 0;
                                    player2score = 0;
                                }
                            }
                            break;
                        }
                        default: break;
                    }
                }
                default: break;
            }
        }
    }
    else {//scoreboard    
        ball->Draw();
        for (int e_i = 1; e_i < gameState->entityCount - 1 ; e_i++){
            gameState->entities[e_i]->collision(ball);
            gameState->entities[e_i]->Draw();
        };
        if (gamePasued == false){
            {
                // key to move every thing =)) 
                if (currentKeyStates[SDL_SCANCODE_W]) {
                // Action to perform when W key is held
                    //SDL_Log("key W is being pressed");
                    currentPlayer1->moveUp();
                }
                if (currentKeyStates[SDL_SCANCODE_A]) {
                    // Action to perform when A key is held
                    //SDL_Log("key A is being pressed");
                    currentPlayer1->moveLeft();
                }

                if (currentKeyStates[SDL_SCANCODE_S]) {
                    // Action to perform when S key is held
                    //SDL_Log("key S is being pressed");
                    currentPlayer1->moveDown();
                }

                if (currentKeyStates[SDL_SCANCODE_D]) {
                    // Action to perform when D key is held
                    //SDL_Log("key D is being pressed");
                    currentPlayer1->moveRight();
                }
                // Movement for player 2
                if (currentKeyStates[SDL_SCANCODE_UP]) {
                    // Action to perform when Up Arrow key is held
                    //SDL_Log("Up Arrow key is being pressed");
                    currentPlayer2->moveUp();
                }

                if (currentKeyStates[SDL_SCANCODE_LEFT]) {
                    // Action to perform when Left Arrow key is held
                    //SDL_Log("Left Arrow key is being pressed");
                    currentPlayer2->moveLeft();
                }

                if (currentKeyStates[SDL_SCANCODE_DOWN]) {
                    // Action to perform when Down Arrow key is held
                    //SDL_Log("Down Arrow key is being pressed");
                    currentPlayer2->moveDown();
                }

                if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
                    // Action to perform when Right Arrow key is held
                    //SDL_Log("Right Arrow key is being pressed");
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
                                    if (event.key.state == SDL_RELEASED) {
                                        // Swap players when E key is pressed
                                        //SDL_Log("key E press");
                                        currentPlayer1->choose();
                                        player1.insert(player1.begin(),currentPlayer1);
                                        currentPlayer1 = player1.back();
                                        player1.pop_back();
                                        currentPlayer1->choose();
                                    }
                                    
                                }
                                break;
                            }
                            case SDLK_SLASH: {
                                if (event.key.repeat == 0) {
                                    if (event.key.state == SDL_RELEASED) {
                                        // Swap players when E key is pressed
                                        // SDL_Log("key / press");
                                        currentPlayer2->choose();
                                        player2.insert(player2.begin(),currentPlayer2);
                                        currentPlayer2 = player2.back();
                                        player2.pop_back();
                                        currentPlayer2->choose();
                                    }
                                }
                                break;
                            }
                            case SDLK_ESCAPE:{
                                if (event.key.repeat == 0){
                                    if (event.key.state == SDL_RELEASED){
                                        gamePasued = true;
                                    }
                                }
                                break;
                            }
                            default: break;
                        }
                    }break;
                    default: break;
                }
            }
            timePassed += deltaTime;
            ball->move();
            ball->Draw();
            if (ball->getBallX() < 0 ){
                player2score ++;
                gameMemory->initialized = false;
                gameState->entityCount = 0;
                player1.clear();
                player2.clear();
            }   
            if (ball->getBallX() > WIDTH){
                player1score ++;
                gameMemory->initialized = false;
                gameState->entityCount = 0;
                player1.clear();
                player2.clear();
            }
        }
        else {
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
                        resumeButton.mouseOn(mouseX, mouseY);
                        restartButton.mouseOn(mouseX, mouseY);
                        menuButton.mouseOn(mouseX, mouseY);
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN:
                    case SDL_MOUSEBUTTONUP:{
                        if (event.button.button == SDL_BUTTON_LEFT){
                            if (event.button.state == SDL_RELEASED) {
                                if (resumeButton.mousePressed(mouseX, mouseY)){
                                    gamePasued = false;
                                }
                                if (restartButton.mousePressed(mouseX, mouseY)){
                                    gameMemory->initialized = false;
                                    gameState->entityCount = 0;
                                    player1.clear();
                                    player2.clear();
                                    gamePasued = false;
                                    // reset score and timer
                                    timePassed = 0.0f;
                                    player1score = 0;
                                    player2score = 0;

                                }
                                if (menuButton.mousePressed(mouseX, mouseY)){
                                    gameMemory->initialized = false;
                                    gameState->entityCount = 0;
                                    player1.clear();
                                    player2.clear();
                                    // reset score and timer
                                    timePassed = 0.0f;
                                    player1score = 0;
                                    player2score = 0;
                                    gamePasued = false;
                                    return false;
                                }
                            break;
                            } 
                        }
                        break;
                    }   
                    case SDL_KEYDOWN:
                    case SDL_KEYUP:
                    {
                        switch (event.key.keysym.sym){
                            case SDLK_ESCAPE:{
                                if (event.key.repeat == 0){
                                    if (event.key.state == SDL_RELEASED){
                                        gamePasued = false;
                                    }
                                }
                                break;
                            }
                            default: break;
                        }
                    }
                    default: break;
                }
            }
            SDL_Rect pauseBox = {515, 185, 250, 350};
            SDL_SetRenderDrawColor(renderer, 20, 130, 60, 255);
            SDL_RenderFillRect(renderer, &pauseBox);
            resumeButton.render(renderer);
            restartButton.render(renderer);
            menuButton.render(renderer);
        }
    }
    return true;
}