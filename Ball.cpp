#include "Ball.h"

Ball::Ball(SDL_Renderer* renderer) :GameObject(renderer)
{
    SDL_Surface* surface = IMG_Load("media/ball.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    x = 0;
    y = 0;
    width = 30;
    height = 30;
    setDirection(1,1);
}

Ball::~Ball(){
    SDL_DestroyTexture(texture);
}

void Ball::Update() {
    x += dx;
    y += dy;
}

void Ball::Render(){
    SDL_Rect rectBall;
    rectBall.x = (int) x;
    rectBall.y = (int) y;
    rectBall.w = width;
    rectBall.h = height;
    SDL_RenderCopy(renderer, texture, NULL, &rectBall);
}

//Chuẩn hoá (dx,dy) phù hợp với tốc độ bóng
void Ball::setDirection(float dx, float dy){
    float dl = sqrt(dx * dx + dy * dy);
    this->dx = (dx / dl) * BALL_SPEED;
    this->dy = (dy / dl) * BALL_SPEED;
}