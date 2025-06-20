#include <iostream>
#include <Player.h>
#include <Location.h>
#include <Renderer.h>

#ifndef LOCATIONYSTEM_H
#define LOCATIONSYSTEM_H

class LocationSystem {
 public:
  LocationSystem(Player& player, std::vector<Location>& locations, int& enemiesCount, Renderer& renderer);
  void move();

  private:
  Player& player_;
  std::vector<Location>& locations_;
  Renderer& renderer_;
  int &enemiesCount_;
template<typename T> T* findById(int id, std::vector<T>& vec);
};

#endif  
