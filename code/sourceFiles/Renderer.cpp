#include "Renderer.h"
#include <iostream>

void Renderer::print_endline_text(const std::string& text) {
    std::cout << text << std::endl;
}

void Renderer::print_endline_text(const int& text) {
    std::cout << text << std::endl;
}

void Renderer::print_text(const std::string& text) {
    std::cout << text;
}

void Renderer::print_text(const int& text) {
    std::cout << text;
}


