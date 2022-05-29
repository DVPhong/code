#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* renderer){
    this->renderer = renderer;
    x = 0; y = 0;
    width = 1; height = 1;
}

GameObject::~GameObject(){

}

//void GameObject::Update(){}

void GameObject::Render(){

}

bool GameObject::checkCollision(GameObject* other){
    if (x < other->x + other->width and x + width > other->x and 
        y + height > other->y and y < other->y +  other->height)
    return true;
    return false;
}