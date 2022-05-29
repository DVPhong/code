#ifndef PADDLE_H_
#define PADDLE_H_

#include "GameObject.h"
const float PADDLE_SPEED = 10;
class Paddle : public GameObject {
    public :
        Paddle(SDL_Renderer* renderer);
        ~Paddle();
        void Render();
        void HandleEvent(SDL_Event &e);
        void movePaddle();
        float velX;
    private :
        SDL_Texture* texture;
};

#endif