#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<math.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
class GameObject {
    public :
        GameObject(SDL_Renderer* renderer);
        ~GameObject();
        float x, y; 
        int width, height;
        void Render();

        // Kiểm tra va chạm 2 vật thể
        bool checkCollision(GameObject* other);
    protected :
        SDL_Renderer* renderer;
};

#endif