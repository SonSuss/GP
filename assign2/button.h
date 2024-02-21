#ifndef BUTTON_H
#define BUTTON_H

#include "main.h"


class Button {
    private:
        const char* m_text;
        int m_textSize;
        SDL_Rect m_rect;
        SDL_Rect m_textRect;
        SDL_Color bcolor;
        SDL_Color bprechange;
        SDL_Color bchangeColor;
        SDL_Color tcolor;
        TTF_Font* font;
        SDL_Surface* textSurface;
        SDL_Texture* textTexture;

    public:
        Button(const char* text, int text_size, int x, int y, int w, int h, SDL_Color bcolor, SDL_Color bchange,SDL_Color tcolor)
            : m_text(text), m_textSize(text_size), bprechange(bcolor),bchangeColor(bchange) ,tcolor(tcolor) {
                this->m_rect.x = x - w/2;
                this->m_rect.y = y - h/2;
                this->m_rect.w = w;
                this->m_rect.h = h;
                this->bcolor = bprechange;
        }


        void render(SDL_Renderer* renderer);
        void mouseOn(int x, int y);
        bool mousePressed(int x, int y);
};



#endif

