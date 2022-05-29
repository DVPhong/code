#include "Board.h"

Board::Board(SDL_Renderer* renderer) : GameObject(renderer){
    SDL_Surface* surface = IMG_Load("media/bricks.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    x = 0;
    y = 0;
    width = SCREEN_WIDTH;
    height = SCREEN_HEIGHT;
}

Board::~Board(){
    SDL_DestroyTexture(texture);
}

void Board::Render(){
    for (int i = 0; i < NUMBER_BRICK_WIDTH; i++)
        for (int j = 0; j < NUMBER_BRICK_HEIGHT; j++)
            {
                Brick oneBrick = bricks[i][j];
                
                if (oneBrick.state == false) continue;
                SDL_Rect srcrect;
                srcrect.x = (oneBrick.type % 2) * BRICK_WIDTH;
                srcrect.y = (oneBrick.type / 2) * BRICK_HEIGHT;
                srcrect.w = BRICK_WIDTH;
                srcrect.h = BRICK_HEIGHT;
                SDL_Rect dstrect;
                dstrect.x = x + i * BRICK_WIDTH;
                dstrect.y = y + j * BRICK_HEIGHT;
                dstrect.w = BRICK_WIDTH;
                dstrect.h = BRICK_HEIGHT;
                SDL_RenderCopy(renderer, texture,&srcrect, &dstrect);

            }
} 
void Board::CreateLevel(){
    for (int i = 0; i < NUMBER_BRICK_WIDTH; i++)
        for (int j = 0; j < NUMBER_BRICK_HEIGHT; j++)
            {
                int randomType = rand() % 4;
                bricks[i][j].state = true;
                bricks[i][j].type = randomType;            }
}