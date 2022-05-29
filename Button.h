#ifndef BUTTON_H_
#define BUTTON_H_
#include"GameObject.h"
#include<iostream>
class Button : public GameObject
{
    public :
        Button(SDL_Renderer* renderer);
        ~Button();
        SDL_Rect buttonRect;
        void Render();
        bool handleEvent (SDL_Event* e);
    private:
        SDL_Texture* texture;
};
#endif