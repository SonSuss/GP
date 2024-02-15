#ifndef gameCode
#define gameCode


#include <vector>
#include "main.h"

#define ENTITYCOUNT 256
// #include <vector>


class Entity{
    // entityType entityType;
public:
    float x, y;
    float w, h; 
    int r, g, b, a;

virtual void moveUp()=0;
virtual void moveDown()=0;
virtual void moveLeft()=0;
virtual void moveRight()=0;
virtual void move()=0;
virtual void choose()=0;
virtual void UpdateAndDraw()=0;

};


class Wall : public Entity {
    public:
    SDL_FRect rect;
    Wall(float x = 0.0f, float y = 0.0f, float w = 0, float h = 0, int r = 0 , int b = 0, int g=0, int a=0){
            rect.x=x;
            rect.y=y;
            rect.w=w;
            rect.h=h;
            this->r =r;
            this->g =g;
            this->b =b;
            this->a =a;
        };

    void moveUp(){};
    void moveDown(){};
    void moveLeft(){};
    void moveRight(){};
    void move(){};
    void choose(){};
    void UpdateAndDraw() {
        SDL_SetRenderDrawColor(renderer, r,b,g,a);
        SDL_RenderFillRectF(renderer, &rect);
    };
};

class Ball : public Entity {
    public:
    Ball(float x=0.0f, float y=0.0f, float radius=0.0f){
        this->x = x; 
        this->y = y;
        this->w = radius;
        };
    void moveUp(){};
    void moveDown(){};
    void moveLeft(){};
    void moveRight(){};
    void move(){};
    void choose(){};
    void UpdateAndDraw(){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set color to white
        // Calculate the radius squared for efficient comparison
        float radiusSquared = w * w;
        // Iterate over each pixel within the bounding box of the circle
        for (int dy = -w; dy <= w; dy++) {
            for (int dx = -w; dx <= w; dx++) {
                // Calculate the distance from the center of the circle
                float distanceSquared = dx * dx + dy * dy;
                // If the distance is within the radius, draw the pixel
                if (distanceSquared <= radiusSquared) {
                    SDL_RenderDrawPointF(renderer, x + dx, y + dy);
                }
            }
        }
    }
};

class Player : public Wall {
    float acceleration;
    float velocity;
    bool isChoose; 
    public:
    Player(float x = 0.0f, float y = 0.0f , float acceleration = 0, float velocity = 0, int r = 0 , int b = 0, int g=0, int a=0) {
            this->rect.x=x;
            this->rect.y=y;
            this->rect.w= playerWidth;
            this->rect.h= playerHeight;
            this->acceleration = acceleration ;
            this->velocity = velocity;
            this->r =r;
            this->g =g;
            this->b =b;
            this->a =a;
            isChoose = false;
        };
    
    void moveUp() {
        this->rect.y -= velocity * deltaTime;
        if (this->rect.y < gameBarHeight ){this->rect.y = gameBarHeight ;};
    }

    void moveDown() {
        this->rect.y += velocity * deltaTime;
        if (this->rect.y > (HEIGHT - playerHeight)) { this->rect.y = HEIGHT - playerHeight;};
    }

    void moveLeft() {
        this->rect.x -= velocity * deltaTime;
        if (this->rect.x < 0.0f ) { this->rect.x = 0.0f;};
    }

    void moveRight() {
        this->rect.x += velocity * deltaTime;
        if (this->rect.x > (WIDTH - playerWidth) ) { this->rect.x = WIDTH - playerWidth;};
    }
    void move(){};
    void choose(){
        if(isChoose){
            isChoose =false;
        }else isChoose = true;
        };
    void UpdateAndDraw() {
        SDL_SetRenderDrawColor(renderer, r,b,g,a);
        SDL_RenderFillRectF(renderer, &rect);
        if (isChoose){
            SDL_SetRenderDrawColor(renderer, 255,255,51,255);
            SDL_RenderDrawRectF(renderer, &rect);
        }
    };
};

struct GameState{
    int entityCount;
    Entity *entities[ENTITYCOUNT]; 
};


#endif