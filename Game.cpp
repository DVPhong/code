#include"Game.h"

Game::Game(){
    window = NULL;
    renderer = NULL;
    texture = NULL;

}
Game::~Game(){

}

void Game::Init(){
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Breakout Game ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
        std::cout<<"Error creating window: "<<SDL_GetError()<< std::endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
        std::cout<<"Error creating render: "<<SDL_GetError()<<std::endl;
    
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        std::cout<<" SDL_mixer Error: "<< Mix_GetError() << std::endl;

    if( TTF_Init() == -1 )
		std::cout<< "SDL_ttf could not initialize! SDL_ttf Error: "<< TTF_GetError() << std::endl;			            
}
void Game::Audio(){
    music = Mix_LoadMUS("media/3D Dot Game Heroes Soundtrack.mp3");
    if (music == NULL)
    {
         std::cout<<" Failed to load music! SDL_Mixer Error: "<< Mix_GetError() << std::endl;
    }
    brickHit = Mix_LoadWAV("media/brick_hit.mp3");
    if (brickHit == NULL)
    {
         std::cout<<" Failed to load brickHit music! SDL_Mixer Error: "<< Mix_GetError() << std::endl;
    }
    paddleHit = Mix_LoadWAV("media/paddle_hit.mp3");
    if (paddleHit == NULL)
    {
         std::cout<<" Failed to load paddleHit music! SDL_Mixer Error: "<< Mix_GetError() << std::endl;
    }
    lifeLost = Mix_LoadWAV("media/life_lost.mp3");
    if (lifeLost == NULL)
    {
         std::cout<<" Failed to load lifeLost music! SDL_Mixer Error: "<< Mix_GetError() << std::endl;
    }
    windowHit = Mix_LoadWAV("media/wall.mp3");
    if (windowHit == NULL)
    {
         std::cout<<" Failed to load windowHit music! SDL_Mixer Error: "<< Mix_GetError() << std::endl;
    }
}

void Game::loadFont(std::string text){
    font = TTF_OpenFont("media/lazy.ttf",40);
    if( font == NULL )
    {
        std::cout<< "Failed to load lazy font! SDL_ttf Error: "<< TTF_GetError() ;
    }

    SDL_Color textColor = { 255,255,255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    SDL_Rect srcRect;
	SDL_Rect desRect;
	TTF_SizeText(font, text.c_str(), &srcRect.w, &srcRect.h);

	srcRect.x = 0;
	srcRect.y = 0;

	desRect.x = 20;
	desRect.y = 500;

	desRect.w = srcRect.w;
	desRect.h = srcRect.h;

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, &srcRect, &desRect);
}
void Game::Update()
{
    int mx, my;
    Uint8 mstate = SDL_GetMouseState(&mx, &my);
    if (mstate&SDL_BUTTON(1)) {
        //Nh???n chu???t tr??i ????? b???t ?????u 
         Mix_PlayMusic(music, -1);
        if (isOriginalLocation) {
            isOriginalLocation = false;
            //?????t b??ng ch???y theo h?????ng ch???ch sang ph???i 45 ?????
            ball->setDirection(1, -1);
        }
    }

    if (isOriginalLocation)  resetBall();
    if (countBricks() == 0)
    { 
        newGame();
        level++;
    }
    if (!isOriginalLocation)  ball->Update(); 
}

void Game::Run()
{
    ball = new Ball(renderer);
    paddle = new Paddle(renderer);
    board = new Board(renderer);
    button = new Button(renderer);
    newGame();
    Audio();
    int quit = 1;
    bool quitAll = false;

    while (!quitAll) {
    while (quit == 1)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) {quit = 0;quitAll = true;}
            paddle->HandleEvent(e);
        }
        paddle->movePaddle();

        checkWindowColision();
        if (ballRemain < 1) quit = 0; 
        checkPaddleCollision();
        checkBrickCollision();
        text = "Score : "+ std::to_string(score) + "  " + "Level : "+std::to_string(level) + " Ball : x" + std::to_string(ballRemain);
        loadFont(text);
        Update();
        Render();
    }
    quit = 2;
    SDL_Surface* surface1 = IMG_Load("media/GameOver1.jpg");
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, surface1);
    SDL_FreeSurface(surface1);
    SDL_RenderPresent(renderer);
    
    while(quit == 2)
    {
        SDL_RenderCopy(renderer, texture1, NULL,NULL);
        //SDL_RenderClear(renderer);
        button->Render();
        SDL_RenderPresent(renderer);
        SDL_Event e;
        while(SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) {quit = 0;quitAll = true;}
            if (button->handleEvent(&e)) {quit = 1;ballRemain = 2;score = 0;level = 1;newGame();Audio();}
        }
        
    }
    }
    delete ball;
    delete paddle;
    delete board;
    delete button;
    Clean();
    
    SDL_Quit();
    Mix_Quit();
    TTF_Quit();
}
void Game::newGame(){
    board->CreateLevel();
    resetPaddle();
    resetBall();
}
void Game::resetPaddle(){
    isOriginalLocation = true;
    paddle->x = 325;
    paddle->y = 570;
}
void Game::resetBall(){
    ball->x = (SCREEN_WIDTH - ball->width) *0.5f;
    ball->y = (SCREEN_HEIGHT - paddle->height - ball->height) *1.0f;
}
int Game::countBricks() {
    int brickcount = 0;
    for (int i = 0; i < NUMBER_BRICK_WIDTH; i++) {
        for (int j = 0; j < NUMBER_BRICK_HEIGHT; j++) {
            Brick brick = board->bricks[i][j];
            if (brick.state) {
                brickcount++;
            }
        }
    }
    return brickcount;
}
void Game::Clean()
{
    Mix_FreeChunk(brickHit);
    Mix_FreeChunk(windowHit);
    Mix_FreeChunk(paddleHit);
    Mix_FreeChunk(lifeLost);
    brickHit = NULL;
    windowHit = NULL;
    paddleHit = NULL;
    lifeLost = NULL;

    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void Game::Render()
{
    SDL_RenderClear(renderer);
    loadFont(text);
    ball->Render();
    paddle->Render();
    board->Render();
    SDL_RenderPresent(renderer);
}

void Game::checkWindowColision(){
    // tr??i
    if (ball-> x < 0) 
    {
        ball->x = 0;
        ball->dx = ball->dx * -1;
        Mix_PlayChannel(-1, windowHit, 0);
    } 
    //ph???i
    else if (ball->x + ball->width > SCREEN_WIDTH)
    {
        ball->x = SCREEN_WIDTH - ball->width;
        ball->dx = ball->dx * -1; 
        Mix_PlayChannel(-1, windowHit, 0);
    }
    //tr??n
    if (ball->y < 0) 
    {
        ball->y = 0;
        ball->dy = ball->dy * -1;
        Mix_PlayChannel(-1, windowHit, 0);
    }
    //d?????i
    else if (ball->y + ball->height > SCREEN_HEIGHT)
    {
        //ball->y = SCREEN_HEIGHT - ball->height;
        //ball->dy = ball->dy * -1;
        Mix_PlayChannel(-1, lifeLost, 0);
        Mix_PauseMusic();
        ballRemain -= 1;
        resetPaddle();
    }
    
}

float Game::getReflection(float hitx) {
    // ?????m b???o r???ng bi???n hitx n???m trong chi???u r???ng c???a paddle
    if (hitx < 0) {
        hitx = 0;
    } else if (hitx > paddle->width) {
        hitx = paddle->width;
    }
    hitx -= paddle->width / 2.0f;
    //hitx > 0 l?? b??n ph???i <0 b??n tr??i
    
    return (hitx / (paddle->width / 2.0f));
}


void Game::checkPaddleCollision() {
    float ballcenterx = ball->x + ball->width / 2.0f;
    
    if (ball->checkCollision(paddle)) {
        ball->y = paddle->y - ball->height;
        ball->setDirection(getReflection(ballcenterx - paddle->x), -1);
        Mix_PlayChannel(-1, paddleHit, 0);
    }
}
void Game::checkBrickCollision(){
    for (int i = 0; i < NUMBER_BRICK_WIDTH; i++) 
        for (int j = 0; j < NUMBER_BRICK_HEIGHT; j++) {
            Brick brick = board->bricks[i][j];
            if (brick.state)
            {
                //to??? ????? c???a brick
                float brickX = board->x + i * BRICK_WIDTH;
                float brickY = board->y + j * BRICK_HEIGHT;
                
                //to??? ????? t??m c???a ball
                float ballCenterX = ball->x + 0.5f* ball->width;
                float ballCenterY = ball->y + 0.5f * ball->height;
                
                //to??? ????? t??m c???a brick
                float brickCenterX = brickX + 0.5f * BRICK_WIDTH;
                float brickCenterY = brickY + 0.5f * BRICK_HEIGHT;

            if (ball->x < brickX + BRICK_WIDTH and ball->x +ball->width >= brickX and 
            ball->y <= brickY + BRICK_HEIGHT and ball->y + ball->height >= brickY) {

                Mix_PlayChannel(-1, brickHit, 0);  
                board->bricks[i][j].state = false;
                score += board->bricks[i][j].type + 1;  

                //T??nh to??n cho ball ??i ????? ch???m ????? kh??ng xuy??n qua li??n t???c c??c vi??n g???ch
                float xmin = std::max(brickX, ball->x);
                float xmax = std::min(brickX + BRICK_WIDTH, ball->x + ball->width);
                float xsize = xmax - xmin;
                float ymin = std::max(brickY, ball->y);
                float ymax = std::min(brickY + BRICK_HEIGHT, ball->y + ball->height);
                float ysize = ymax - ymin;

                if (xsize > ysize)
                {
                    if (ballCenterY > brickCenterY)
                    {
                        ball->y += ysize + 0.01f;
                        response("Bottom");
                    }
                    else {
                        ball->y -= ysize + 0.01f;
                        response("Top");
                    }
                } else {
                    if (ballCenterX < brickCenterX){
                        ball->x -= xsize + 0.01f;
                        response("Left");
                    }
                    else {
                        ball->x += xsize + 0.01f;
                        response("Right");
                    }
                }
                return;
            }
            }
}
}
void Game::response(std::string side){
    int kx = 1, ky = 1; // H??? s??? 1,-1 ????? nh??n v??o dx,dy c???a b??ng  --> H?????ng c???a b??ng t????ng ???ng v???i h?????ng va ch???m
    if (ball->dx > 0)
    {
        if (ball->dy > 0)
        {
            if (side == "Left" or side == "Bottom") kx = -1;
                else ky = -1;
        }
        else if (ball->dy < 0) 
        {
            if (side == "Left" or side == "Top") kx = -1;
                else ky = -1;
        }
    }
    else if (ball->dx < 0)
    {
        if (ball->dy > 0)
        {
            if (side == "Right" or side == "Bottom") kx = -1;
                else ky = -1;
        }
        else if (ball->dy < 0) 
        {
            if (side == "Left" or side == "Right") kx = -1;
                else ky = -1;
        }
    }
    ball->setDirection(kx * ball->dx, ky * ball->dy);
}

