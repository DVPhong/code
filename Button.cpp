#include"Button.h"

Button::Button(SDL_Renderer* renderer):GameObject(renderer){
    SDL_Surface* surface = IMG_Load("media/restartButoon.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    x = 290;
    y = 350;
    width = 200;
    height = 50;
    buttonRect.x = x;
    buttonRect.y = y;
    buttonRect.w = width;
    buttonRect.h = height; 
}
Button::~Button(){
    SDL_DestroyTexture(texture);
}
bool Button::handleEvent(SDL_Event* e)
{
    if (e->type == SDL_MOUSEBUTTONDOWN)
    {
        int x1,y1;
        SDL_GetMouseState(&x1, &y1);
        bool inside = true;
        if (x1 < buttonRect.x)
        {
            inside = false;
        }
        if (y1 < buttonRect.y )
        {
            inside = false;
        }
        if (y1 > (buttonRect.y + buttonRect.h))
        {
            inside = false;
        }
        if (x1 > (buttonRect.x + buttonRect.w))
        {
            inside = false;
        }
        return inside;
    }
    return false;
}

void Button::Render(){
    SDL_RenderCopy(renderer, texture, NULL, &buttonRect);
}