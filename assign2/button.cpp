#include "Button.h"

void  Button::render(SDL_Renderer* renderer) {
        // Render button background
        font = TTF_OpenFont("Sans.ttf", m_textSize);
        textSurface = TTF_RenderText_Solid(font, m_text, tcolor);

        m_textRect.x = m_rect.x + (m_rect.w - textSurface->w) / 2;
        m_textRect.y = m_rect.y + (m_rect.h - textSurface->h) / 2;

        SDL_SetRenderDrawColor(renderer, bcolor.r, bcolor.g, bcolor.b, bcolor.a);
        SDL_RenderFillRect(renderer, &m_rect);
        // Render text
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_QueryTexture(textTexture, nullptr, nullptr, &m_textRect.w, &m_textRect.h);
        SDL_RenderCopy(renderer, textTexture, nullptr, &m_textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        TTF_CloseFont(font);
}

void Button::mouseOn(int x, int y){
    if (m_rect.x < x && m_rect.x + m_rect.w > x && m_rect.y < y && m_rect.y + m_rect.h > y ){
        bcolor = bchangeColor;
    }
    else {bcolor = bprechange;}
}

bool Button::mousePressed(int x, int y){
    if (m_rect.x < x && m_rect.x + m_rect.w > x && m_rect.y < y && m_rect.y + m_rect.h > y ){
        return true;
    }
    else return false;
}

void writeText(int size, SDL_Color color, const char *t, int x, int y){
    font = TTF_OpenFont("Sans.ttf", size);
    SDL_Surface* text;
    text = TTF_RenderText_Solid( font, t, color );
    SDL_Texture* text_texture;
    text_texture = SDL_CreateTextureFromSurface( renderer, text );
    SDL_Rect dest = { x - text->w / 2 , y - text->h/2 , text->w, text->h };
    SDL_RenderCopy( renderer, text_texture, nullptr , &dest );  
    SDL_DestroyTexture( text_texture );
    SDL_FreeSurface(text );
}