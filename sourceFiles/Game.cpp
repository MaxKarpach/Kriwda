#include "../headerFiles/Game.h" 
#include <iostream>

const int MAX_STRING_LEN = 20;

void Game::initNewGame(){
    std::cout << "Начало игры" << std::endl;
}
void Game::gameOver(){
    std::cout << "Вы проиграли" << std::endl;
}
void Game::endGame(){
    std::cout << "Конец игры" << std::endl;
}