#include"main.h"
int main(int argc, char* argv[])
{
    srand(time(0));
    Game* game = new Game();
    game->Init();
    game->Run();

    delete game; 
    return 0;                        
}