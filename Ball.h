#ifndef BALL_H_
#define BALL_H_
#include "GameObject.h"

const float BALL_SPEED = 8;

class Ball : public GameObject {
    public :
        Ball(SDL_Renderer* renderer);
        ~Ball();
        void Update();
        void Render();
        float dx, dy;
        void setDirection(float dx, float dy);
    private :
        SDL_Texture* texture;
};
#endif