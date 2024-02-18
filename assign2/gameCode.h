#ifndef gameCode
#define gameCode


#include <vector>
#include <cmath>
#include "main.h"
 

#define ENTITYCOUNT 256
// #include <vector>
const double PI = 3.14159265 ;

class Entity{
    // entityType entityType;
public:
    float x, y;
    float pre_x = 0, pre_y = 0;
    float w, h; 
    int r, g, b, a;

virtual void moveUp()=0;
virtual void moveDown()=0;
virtual void moveLeft()=0;
virtual void moveRight()=0;
virtual void move()=0;
virtual void choose()=0;
virtual void collision(Entity *object)=0;
virtual void UpdateAndDraw()=0;
virtual double getAngle()=0;
virtual float getVelocity()=0;
virtual void setBall(double angle, float velocity)=0;
virtual float getBallX()=0;

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
    void collision(Entity *object){
        double angle = object->getAngle();
        float x_w = this->rect.x + this->rect.w;
        float y_h = this->rect.y + this->rect.h;
        //hit top
        if ( 0 < angle && angle < PI){ 
            if (this->rect.x - object->w < object->x && object->x < x_w + object->w){
                if (object->y + object->w >= this->rect.y && object->pre_y + object->w < this->rect.y){
                    angle = 2 * PI - angle;
                }
            }
        }
        // hit bottom
        else {
            if (this->rect.x - object->w < object->x && object->x < x_w + object->w){
                if (object->y - object->w <=  y_h && object->pre_y - object->w >  y_h){
                    angle = 2 * PI - angle;
                }
            }
        }
        //hit left
        if (PI/2 < angle && angle < PI * 3 / 2){
            if (this->rect.y - object->w < object->y &&  object->y < y_h + object->w ){
                if (object->x - object->w <= x_w && object->pre_x - object->w > x_w){
                    angle = PI - angle;
                }
            }
        }
        //hit right
        else {
            if (this->rect.y - object->w < object->y && object->y < y_h + object->w ){
                if (object->x + object->w >= this->rect.x && object->pre_x + object->w < this->rect.x){
                    angle = PI - angle;
                }
            }
        }
        object->setBall(angle, object->getVelocity());
    };
    float getBallX(){return 0;};
    double getAngle(){return 0;};
    void setBall(double angle, float velocity){};
    float getVelocity(){return 0;};
    void UpdateAndDraw() {
        SDL_SetRenderDrawColor(renderer, r,b,g,a);
        SDL_RenderFillRectF(renderer, &rect);
    };
};

class Ball : public Entity {
    float acceleration = 100;
    float velocity = -1;
    double vAngle = 0 ;
    public:
    Ball(float x=0.0f, float y=0.0f, float radius=0.0f){
        this->x = x; 
        this->y = y; 
        this->pre_x = x;
        this->pre_y = y;
        this->w = radius;
        };
    void moveUp(){};
    void moveDown(){};
    void moveLeft(){};
    void moveRight(){};
    void move(){
        if (this->vAngle <= 0) {this->vAngle += 2*PI;}
        if (this->vAngle > 2*PI){this->vAngle -= 2*PI;}
        this->pre_x = this->x;
        this->pre_y = this->y;
        this->x += velocity * cos(vAngle) * deltaTime;
        this->y += velocity * sin(vAngle) * deltaTime;
        this->velocity = this->velocity - this->acceleration*deltaTime;
    };
    void choose(){};
    void collision(Entity *object){};
    double getAngle(){return this->vAngle;};
    float getVelocity(){return this->velocity;};
    void setBall(double angle, float velocity){
        if(velocity > 900 ){this->velocity = 900;}else {this->velocity = velocity;}
        this->vAngle = angle;
    };
    float getBallX(){
        return this->x;
    }
    
    void UpdateAndDraw(){
        if (this->velocity > 0){move();}else {this->velocity = -1 ; this->vAngle = 0;}
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
        float radiusSquared = w * w;
        for (int dy = -w; dy <= w; dy++) {
            for (int dx = -w; dx <= w; dx++) {
                float distanceSquared = dx * dx + dy * dy;
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
    float pre_x, pre_y;
    float x_center , y_center;
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
            this->pre_x = x;
            this->pre_y = y;
            isChoose = false;
        };
    
    void moveUp() {
        this->pre_y = this->rect.y;
        this->rect.y -= velocity * deltaTime;
        if (this->rect.y < gameBarHeight ){this->rect.y = gameBarHeight ;};
    }
    void moveDown() {
        this->pre_y = this->rect.y;
        this->rect.y += velocity * deltaTime;
        if (this->rect.y > (HEIGHT - playerHeight)) { this->rect.y = HEIGHT - playerHeight;};
    }
    void moveLeft() {
        this->pre_x = this->rect.x;
        this->rect.x -= velocity * deltaTime;
        if (this->rect.x < 0.0f ) { this->rect.x = 0.0f;};
    }
    void moveRight() {
        this->pre_x = this->rect.x;
        this->rect.x += velocity * deltaTime;
        if (this->rect.x > (WIDTH - playerWidth) ) { this->rect.x = WIDTH - playerWidth;};
    }
    void choose(){
        if(isChoose){
            isChoose =false;
        }else isChoose = true;
        };
    void collision(Entity *object){
        double angle = object->getAngle();
        float ballV= object->getVelocity();
        float tan = atan((object->y - this->y_center) / (object->x - this->x_center));
        float x_w = this->rect.x + this->rect.w;
        float y_h = this->rect.y + this->rect.h;
        if (ballV > 0){
            // right
            if (this->rect.y - object->w < object->y && object->y < y_h + object->w ){
                if (object->x - object->w <= this->rect.x + this->rect.w && object->pre_x - object->w > this->pre_x + this->rect.w){
                    tan += PI - angle;
                    if (tan < - PI / 2){tan = - PI / 2;}
                    if (tan > PI / 2){tan = PI / 2;}
                    object->setBall(tan , this->velocity * 2 + ballV);
                    object->x = this->rect.x + this->rect.w + object->w + 1;
                }
            //left
                if (object->x + object->w >= this->rect.x && object->pre_x + object->w < this->pre_x){
                    if (tan >0){
                        if (angle > PI){
                            angle = 2 * PI - angle;
                            tan += angle;
                            tan += PI;
                        }
                        else {
                            angle = - angle;
                            tan += angle;
                            tan += PI;
                        }
                    }
                    else {
                        if (angle > PI){
                            angle = 2 * PI - angle;
                            tan += angle + PI;
                        }
                        else {
                            tan = - tan; 
                            tan += angle;
                            tan = PI - tan; 
                        }
                    }
                    object->setBall(tan , this->velocity * 2 + ballV);
                    object->x = this->rect.x - object->w - 1;
                }
            }
            if (this->rect.x - object->w < object->x && object->x < x_w + object->w){
                if (this->rect.y <= object->y + object->w && this->pre_y > object->pre_y + object->w){
                    if (tan > 0 ){object->setBall(tan + PI , this->velocity * 2);}
                    else {object->setBall(tan , this->velocity * 2 + ballV);}
                    object->y = this->rect.y - object->w - 1;
                } 
                if (this->rect.y + this->rect.h >= object->y - object->w && this->pre_y + this->rect.h < object->pre_y - object->w){
                    if (tan > 0 ){object->setBall(tan  , this->velocity * 2);}
                    else {object->setBall(tan + PI , this->velocity * 2 + ballV);}
                    object->y = this->rect.y + this->rect.h + object->w + 1;
                }
            }
        }
        else {
            if (this->rect.y - object->w < object->y && object->y < y_h + object->w ){
                if (this->rect.x + this->rect.w >= object->x - object->w && this->pre_x + this->rect.w < object->x - object->w){
                    object->setBall(tan , this->velocity * 2);
                    object->x = this->rect.x + this->rect.w + object->w + 1;
                }
                else if (this->rect.x <= object->x + object->w && this->pre_x > object->x + object->w ){
                    object->setBall(tan + PI , this->velocity * 2);
                    object->x = this->rect.x - object->w -1;
                }
            }
            if (this->rect.x - object->w < object->x && object->x < x_w + object->w){
                if (this->rect.y <= object->y + object->w && this->pre_y > object->y + object->w){
                    if (tan > 0 ){object->setBall(tan + PI , this->velocity * 2);}
                    else {object->setBall(tan , this->velocity * 2);}
                    object->y = this->rect.y - object->w - 1;
                } 
                if (this->rect.y + this->rect.h >= object->y - object->w && this->pre_y + this->rect.h < object->y - object->w){
                    if (tan > 0 ){object->setBall(tan  , this->velocity * 2);}
                    else {object->setBall(tan + PI , this->velocity * 2);}
                    object->y = this->rect.y + this->rect.h + object->w + 1;
                }
            }
        }
    };
    void UpdateAndDraw() {
        x_center = this->rect.x + this->rect.w / 2;
        y_center = this->rect.y + this->rect.h / 2;
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