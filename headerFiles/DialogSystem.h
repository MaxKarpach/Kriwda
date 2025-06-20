#include <iostream>
#include <DialogChoice.h>
#include <DialogNode.h>
#include <Renderer.h>
#include <Location.h>

#ifndef DIALOGSYSTEM_H
#define DIALOGSYSTEM_H

class DialogSystem {
 public:
  DialogSystem(std::vector<DialogNode>& dialogNodes, std::vector<DialogChoice>& dialogChoices, int& currentNodeId, Location* currentLocation, Renderer& renderer);
  void startDialog();

  private:
  std::vector<DialogNode>& dialogNodes_;
  std::vector<DialogChoice>& dialogChoices_;
  int& currentNodeId_;
  Location *currentLocation_;
  Renderer &renderer_;
};

#endif  