#ifndef BOARD_H_
#define BOARD_H_

#include "GameObject.h"

//Số viên gạch hàng ngang
const int NUMBER_BRICK_WIDTH = 12;
//Số viên gạch hàng dọc
const int NUMBER_BRICK_HEIGHT = 12;

const float BRICK_WIDTH = 66.5;
const float BRICK_HEIGHT = 25;

struct Brick{
    int type;
    bool state;
    
};
class Board : public GameObject{
    public :
        Board(SDL_Renderer* renderer);
        ~Board();
        void Render();
        void CreateLevel();
        
        Brick bricks[NUMBER_BRICK_WIDTH][NUMBER_BRICK_HEIGHT];
    
    private :
        SDL_Texture* texture;
};
#endif