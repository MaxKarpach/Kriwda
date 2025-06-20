#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <Renderer.h>
#include <Scene.h>
#include <DialogNode.h>
#include <DialogChoice.h>

struct GameStatsDef {
    bool is_game_started;
    bool is_game_loop_ended;
    bool is_game_ended;
};

class Game {
 public:
    Game(std::vector<Scene>& scenes, std::vector<DialogNode>& dialog_nodes,
         std::vector<DialogChoice>& dialog_choices, Renderer& renderer);

    bool get_is_game_started() const { return is_game_started_; }
    void set_is_game_started(bool value) { is_game_started_ = value; }

    bool get_is_game_loop_ended() const { return is_game_loop_ended_; }
    void set_is_game_loop_ended(bool value) { is_game_loop_ended_ = value; }

    bool get_is_game_ended() const { return is_game_ended_; }
    void set_is_game_ended(bool value) { is_game_ended_ = value; }

    void scene_dialog(std::vector<DialogNode>& dialog_nodes,
                      std::vector<DialogChoice>& dialog_choices, int current_node_id,
                      Renderer& renderer);

    void init_new_game(std::vector<Scene>& scenes,
                       std::vector<DialogNode>& dialog_nodes,
                       std::vector<DialogChoice>& dialog_choices,
                       Renderer& renderer);

    void game_over(Renderer& renderer);

    void end_game(std::vector<Scene>& scenes,
                  std::vector<DialogNode>& dialog_nodes,
                  std::vector<DialogChoice>& dialog_choices, Renderer& renderer);

 private:
    bool is_game_started_ = false;
    bool is_game_loop_ended_ = false;
    bool is_game_ended_ = false;

    std::vector<Scene>& scenes_;
    std::vector<DialogNode>& dialog_nodes_;
    std::vector<DialogChoice>& dialog_choices_;
    Renderer& renderer_;
};

class GameRegistry {
 public:
    void load(std::istream& is);
    void save(std::ostream& os);
    GameStatsDef get_game_stats() const;
    void set_game_stats(const GameStatsDef& def);

    GameStatsDef to_game_stats_def(const Game& game);
    void from_game_stats_def(Game& game, const GameStatsDef& def);

 private:
    GameStatsDef game_stats_;
};

#endif
