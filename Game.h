#ifndef GAME_H_
#define GAME_H_
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<stdlib.h>
#include<string>
#include<algorithm>

#include"Ball.h"
#include"Paddle.h"
#include"Board.h"
#include"Button.h"
class Game {
    public :
        Game();
        ~Game();
        void Init();
        void Update();
        void Render();
        void Run();
        void Clean();

        Ball* ball;
        Paddle* paddle;
        Board* board;
        Button* button;

        bool isOriginalLocation;
        void newGame();
        void resetPaddle();
        void resetBall();
        void checkWindowColision();
        void checkPaddleCollision();
        float getReflection(float hitx);
        void checkBrickCollision();
        void response(std::string side);
        int countBricks();

        int score = 0, level = 1;
        int ballRemain = 2; 

        void Audio();
        Mix_Chunk *brickHit = NULL;
        Mix_Chunk *paddleHit = NULL;
        Mix_Chunk *lifeLost = NULL;
        Mix_Chunk *windowHit = NULL;
        Mix_Music *music = NULL;

        TTF_Font* font = NULL;
        std::string text ;
        void loadFont(std::string text);
    private :
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;

};

#endif