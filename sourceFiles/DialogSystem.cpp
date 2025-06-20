#include <DialogSystem.h>

DialogSystem::DialogSystem(std::vector<DialogNode>& dialogNodes, std::vector<DialogChoice>& dialogChoices,
     int& currentNodeId, Location* currentLocation, Renderer& renderer):
    dialogNodes_(dialogNodes), dialogChoices_(dialogChoices), currentNodeId_(currentNodeId),
    currentLocation_(currentLocation), renderer_(renderer){}

void DialogSystem::startDialog() {
  while (true) {
    DialogNode* currentNode = nullptr;
    for (auto& node : dialogNodes_) {
      if (node.getId() == currentNodeId_) {
        currentNode = &node;
        break;
      }
    }
    if (!currentNode) {
      renderer_.printEndlineText("Ошибка: узел диалога не найден.");
      break;
    }

    if (currentNode->getDescription() != "") {
      renderer_.printEndlineText(currentNode->getDescription());
    }

    if (currentNode->getChoices().size() == 0) {
      currentLocation_->setDialogNodeId(0);
    }

    if (currentNode->getName() != "") {
      renderer_.printText(currentNode->getName());
      renderer_.printText(": ");
      renderer_.printEndlineText(currentNode->getText());
    }

    std::vector<DialogChoice*> currentChoices;
    for (int choiceId : currentNode->getChoices()) {
      for (auto& choice : dialogChoices_) {
        if (choice.getId() == choiceId && !choice.getIsUsed()) {
          currentChoices.push_back(&choice);
          break;
        }
      }
    }

    if (currentChoices.empty()) {
      break;
    }

    renderer_.printEndlineText("0: выход");
    for (int i = 0; i < currentChoices.size(); ++i) {
      renderer_.printText(i + 1);
      renderer_.printText(": ");
      renderer_.printEndlineText(currentChoices[i]->getText());
    }

    int userChoice = 0;
    std::cin >> userChoice;

    if (userChoice <= 0 || userChoice > currentChoices.size()) {
      renderer_.printEndlineText("Диалог прерван.");
      break;
    }

    currentNodeId_ = currentChoices[userChoice - 1]->getNextNodeId();
    currentChoices[userChoice - 1]->setisUsed(1);
    if (currentChoices[userChoice - 1]->getNextNodeId() == 0) {
      currentLocation_->setDialogNodeId(0);
      break;
    }
  }
}