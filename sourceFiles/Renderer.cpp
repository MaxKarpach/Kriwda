#include "../headerFiles/Renderer.h"
#include <iostream>

void Renderer::printEndlineText(const std::string& text) {
    std::cout << text << std::endl;
}

void Renderer::printEndlineText(const int& text) {
    std::cout << text << std::endl;
}

void Renderer::printText(const std::string& text) {
    std::cout << text;
}

void Renderer::printText(const int& text) {
    std::cout << text;
}
