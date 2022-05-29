#include "Paddle.h"

Paddle :: Paddle(SDL_Renderer* renderer) :GameObject(renderer){
    SDL_Surface* surface = IMG_Load("media/paddle.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    x = 325;
    y = 570;
    width = 150;
    height = 30;
    velX = 0;
}

void Paddle::Render(){

    SDL_Rect rectPaddle;
    rectPaddle.x = (int) x;
    rectPaddle.y = (int) y;
    rectPaddle.w = width;
    rectPaddle.h = height;
    SDL_RenderCopy(renderer,texture,0,&rectPaddle);
}

Paddle ::~Paddle(){
    SDL_DestroyTexture(texture);
}

void Paddle::HandleEvent(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN and e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            velX -= PADDLE_SPEED;
            break;
        case SDLK_RIGHT:
            velX += PADDLE_SPEED;
            break;
        default:
            break;
        }
    }

    if (e.type == SDL_KEYUP and e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            velX += PADDLE_SPEED;
            break;
        case SDLK_RIGHT:
            velX -= PADDLE_SPEED;
            break;
        default:
            break;
        }
    }
}

void Paddle::movePaddle(){
    x += velX;
    if (x < 0 or x + width > SCREEN_WIDTH) x -= velX;
}

