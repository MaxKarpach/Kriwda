#ifndef DIALOG_SYSTEM_H
#define DIALOG_SYSTEM_H

#include <iostream>
#include <vector>

#include <DialogChoice.h>
#include <DialogNode.h>
#include <Renderer.h>
#include <Location.h>

class DialogSystem {
 public:
  DialogSystem(std::vector<DialogNode>& dialog_nodes,
               std::vector<DialogChoice>& dialog_choices,
               int& current_node_id,
               Location* current_location,
               Renderer& renderer);

  void start_dialog();

 private:
  std::vector<DialogNode>& dialog_nodes_;
  std::vector<DialogChoice>& dialog_choices_;
  int& current_node_id_;
  Location* current_location_;
  Renderer& renderer_;
};

#endif
