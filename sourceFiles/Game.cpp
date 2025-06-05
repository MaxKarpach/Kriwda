#include <iostream>
#include <Game.h>
Game::Game( std::vector<Scene>& scenes, std::vector<DialogNode>& dialogNodes,std::vector<DialogChoice>& dialogChoices, 
    Renderer& renderer):
scenes(scenes), dialogNodes(dialogNodes), dialogChoices(dialogChoices), renderer(renderer){}

void Game::sceneDialog(std::vector<DialogNode>& dialogNodes,std::vector<DialogChoice>& dialogChoices, int currentNodeId, Renderer& renderer){
    while (true)
    {

        DialogNode* currentNode = nullptr;
        for (auto& node : dialogNodes) {
            if (node.getId() == currentNodeId) {
                currentNode = &node;
                break;
            }
        }
        if (!currentNode) {
            renderer.printEndlineText("Ошибка: узел диалога не найден.");
            break;
        }

        if (currentNode->getDescription() != ""){
            renderer.printEndlineText(currentNode->getDescription());
        }

        renderer.printText(currentNode->getName());
        renderer.printText(": ");
        renderer.printEndlineText(currentNode->getText());

        std::vector<DialogChoice*> currentChoices;
        for (auto& choice : dialogChoices) {
            if (choice.getNodeId() == currentNodeId) {
                currentChoices.push_back(&choice);
            }
        }

        for (int i = 0; i < currentChoices.size(); ++i) {
            renderer.printText(i + 1);
            renderer.printText(": ");
            renderer.printEndlineText(currentChoices[i]->getText());
        }

        int userChoice = 0;

        do {
            std::cin >> userChoice;
            if (userChoice <= 0 || userChoice > currentChoices.size()){
                renderer.printEndlineText("Неверный ввод");
            }
        } while (userChoice <= 0 || userChoice > currentChoices.size());

        currentNodeId = currentChoices[userChoice - 1]->getNextNodeId();
    }
}

void Game::initNewGame(std::vector<Scene>& scenes, std::vector<DialogNode>& dialogNodes,std::vector<DialogChoice>& dialogChoices, Renderer& renderer){
    std::vector<Scene> endings;
    Scene* beginning;
    for (Scene scene : scenes)
    {
        if (scene.getType() == 'b'){
            beginning = &scene;
            break;
        }
    }
    sceneDialog(dialogNodes, dialogChoices, beginning->getDialogNodeId(), renderer);
    isGameStarted = 1;
}

void Game::gameOver(Renderer& renderer){
    renderer.printEndlineText("Вы проиграли");
}

void Game::endGame( std::vector<Scene>& scenes, std::vector<DialogNode>& dialogNodes,std::vector<DialogChoice>& dialogChoices, Renderer& renderer){
    std::vector<Scene> endings;
    for (Scene scene : scenes){
        if (scene.getType() == 'e'){
            endings.push_back(scene);
        }
    }
    for (int i = 0; i < endings.size(); i++){
        renderer.printText(i + 1);
        renderer.printText(": ");
        renderer.printEndlineText(endings[i].getText());
    }
        int choice = 0;
    while (true) {
        std::cin >> choice;

        if (choice >= 1 && choice <= endings.size()) {
            break;
        } else {
            renderer.printText("Неверный выбор. Пожалуйста, введите число от 1 до ");
            renderer.printEndlineText(endings.size());
        }
    }
    renderer.printEndlineText("Выбранная концовка:");
    renderer.printEndlineText(endings[choice - 1].getText());
    sceneDialog(dialogNodes, dialogChoices, endings[choice - 1].getDialogNodeId(), renderer);
    renderer.printEndlineText("Конец игры");
    isGameEnded = 1;
}

void GameRegistry::load(std::istream& is) {
    GameStatsDef gsd;
    is >> gsd.isGameStarted;
    is >> gsd.isGameLoopEnded;
    is >> gsd.isGameEnded;
    gameStats = gsd;
}

void GameRegistry::save(std::ostream& os) {
    os << gameStats.isGameStarted << std::endl;
    os << gameStats.isGameLoopEnded << std::endl;
    os << gameStats.isGameEnded << std::endl;
}

GameStatsDef GameRegistry::getGameStats() const {
    return gameStats;
}

void GameRegistry::setGameStats(const GameStatsDef& def) {
    gameStats = def;
}

GameStatsDef GameRegistry::toGameStatsDef(const Game& game) {
    GameStatsDef def;
    def.isGameStarted = game.getIsGameStarted();
    def.isGameLoopEnded = game.getIsGameLoopEnded();
    def.isGameEnded = game.getIsGameEnded();
    return def;
}

void GameRegistry::fromGameStatsDef(Game& game, const GameStatsDef& def) {
    game.setIsGameStarted(def.isGameStarted);
    game.setIsGameLoopEnded(def.isGameLoopEnded);
    game.setIsGameEnded(def.isGameEnded);
}