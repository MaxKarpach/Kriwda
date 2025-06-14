#include <iostream>
#include <Renderer.h>
#include <Scene.h>
#include <DialogNode.h>
#include <DialogChoice.h>
#ifndef GAME_H
#define GAME_H

struct GameStatsDef {
    bool isGameStarted;
    bool isGameLoopEnded;
    bool isGameEnded;
};

class Game {
public:
    Game(std::vector<Scene> &scenes, std::vector<DialogNode> &dialogNodes, std::vector<DialogChoice> &dialogChoices, Renderer &renderer);

    bool getIsGameStarted() const {
        return isGameStarted_;
    }
    void setIsGameStarted(bool value){
        isGameStarted_ = value;
    }
    bool getIsGameLoopEnded() const {
        return isGameLoopEnded_;
    }
    void setIsGameLoopEnded(bool value){
        isGameLoopEnded_ = value;
    }
    bool getIsGameEnded() const {
        return isGameEnded_;
    }
    void setIsGameEnded(bool value){
        isGameEnded_ = value;
    }

    void sceneDialog(std::vector<DialogNode> &dialogNodes, std::vector<DialogChoice> &dialogChoices, int currentNodeId, Renderer &renderer);

    void initNewGame( std::vector<Scene>& scenes, std::vector<DialogNode>& dialogNodes,std::vector<DialogChoice>& dialogChoices, Renderer& renderer);
    void gameOver(Renderer& renderer);
    void endGame(std::vector<Scene>& scenes, std::vector<DialogNode>& dialogNodes,std::vector<DialogChoice>& dialogChoices, Renderer& renderer);

private:
    bool isGameStarted_;
    bool isGameLoopEnded_;
    bool isGameEnded_;
    std::vector<Scene> &scenes_;
    std::vector<DialogNode> &dialogNodes_;
    std::vector<DialogChoice> &dialogChoices_;
    Renderer &renderer_;

};

class GameRegistry {
public:
    void load(std::istream& is);
    void save(std::ostream& os);
    GameStatsDef getGameStats() const;
    void setGameStats(const GameStatsDef& def);

    GameStatsDef toGameStatsDef(const Game& game);
    void fromGameStatsDef(Game& game, const GameStatsDef& def);

private:
    GameStatsDef gameStats;
};
#endif