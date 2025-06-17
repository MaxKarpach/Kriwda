#include <iostream>

#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
 public:
  void printEndlineText(const std::string& text);
  void printEndlineText(const int& text);
  void printText(const std::string& text);
  void printText(const int& text);
};

#endif  
