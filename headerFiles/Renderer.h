#include <iostream>

#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
 public:
  void print_endline_text(const std::string& text);
  void print_endline_text(const int& text);
  void print_text(const std::string& text);
  void print_text(const int& text);
};

#endif
