#include <Game.h>

Game::Game(std::vector<Scene>& scenes, std::vector<DialogNode>& dialog_nodes,
           std::vector<DialogChoice>& dialog_choices, Renderer& renderer)
    : scenes_(scenes), dialog_nodes_(dialog_nodes), dialog_choices_(dialog_choices), renderer_(renderer) {}

void Game::scene_dialog(std::vector<DialogNode>& dialog_nodes, std::vector<DialogChoice>& dialog_choices,
                        int current_node_id, Renderer& renderer) {
    while (true) {
        DialogNode* current_node = nullptr;
        for (auto& node : dialog_nodes) {
            if (node.get_id() == current_node_id) {
                current_node = &node;
                break;
            }
        }

        if (!current_node) {
            renderer.print_endline_text("Ошибка: узел диалога не найден.");
            break;
        }

        if (!current_node->get_description().empty()) {
            renderer.print_endline_text(current_node->get_description());
        }

        if (!current_node->get_text().empty()) {
            renderer.print_text(current_node->get_name());
            renderer.print_text(": ");
            renderer.print_endline_text(current_node->get_text());
        }

        std::vector<DialogChoice*> current_choices;
        for (int choice_id : current_node->get_choices()) {
            for (auto& choice : dialog_choices) {
                if (choice.get_id() == choice_id && !choice.get_is_used()) {
                    current_choices.push_back(&choice);
                    break;
                }
            }
        }

        if (current_choices.empty()) {
            break;
        }

        for (int i = 0; i < current_choices.size(); ++i) {
            renderer.print_text(i + 1);
            renderer.print_text(": ");
            renderer.print_endline_text(current_choices[i]->get_text());
        }

        int user_choice = 0;
        do {
            std::cin >> user_choice;
            if (user_choice <= 0 || user_choice > current_choices.size()) {
                renderer.print_endline_text("Неверный ввод");
            }
        } while (user_choice <= 0 || user_choice > current_choices.size());

        current_node_id = current_choices[user_choice - 1]->get_next_node_id();
        current_choices[user_choice - 1]->set_is_used(true);

        if (current_node_id == 0) {
            break;
        }
    }
}

void Game::init_new_game(std::vector<Scene>& scenes, std::vector<DialogNode>& dialog_nodes,
                         std::vector<DialogChoice>& dialog_choices, Renderer& renderer) {
    Scene* beginning = nullptr;
    for (Scene& scene : scenes) {
        if (scene.get_type() == 'b') {
            beginning = &scene;
            break;
        }
    }

    if (beginning) {
        scene_dialog(dialog_nodes, dialog_choices, beginning->get_dialog_node_id(), renderer);
        is_game_started_ = true;
    } else {
        renderer.print_endline_text("Начальная сцена не найдена.");
    }
}

void Game::game_over(Renderer& renderer) {
    renderer.print_endline_text("Вы проиграли");
    renderer.print_endline_text("Загрузка...");
}

void Game::end_game(std::vector<Scene>& scenes, std::vector<DialogNode>& dialog_nodes,
                    std::vector<DialogChoice>& dialog_choices, Renderer& renderer) {
    std::vector<Scene> endings;
    for (const Scene& scene : scenes) {
        if (scene.get_type() == 'e') {
            endings.push_back(scene);
        }
    }

    for (int i = 0; i < endings.size(); i++) {
        renderer.print_text(i + 1);
        renderer.print_text(": ");
        renderer.print_endline_text(endings[i].get_text());
    }

    int choice = 0;
    while (true) {
        std::cin >> choice;
        if (choice >= 1 && choice <= endings.size()) {
            break;
        } else {
            renderer.print_text("Неверный выбор. Пожалуйста, введите число от 1 до ");
            renderer.print_endline_text(endings.size());
        }
    }

    scene_dialog(dialog_nodes, dialog_choices, endings[choice - 1].get_dialog_node_id(), renderer);
    renderer.print_endline_text("Конец игры");
    is_game_ended_ = true;
}

void GameRegistry::load(std::istream& is) {
    GameStatsDef gsd;
    is >> gsd.is_game_started;
    is >> gsd.is_game_loop_ended;
    is >> gsd.is_game_ended;
    game_stats_ = gsd;
}

void GameRegistry::save(std::ostream& os) {
    os << game_stats_.is_game_started << std::endl;
    os << game_stats_.is_game_loop_ended << std::endl;
    os << game_stats_.is_game_ended << std::endl;
}

GameStatsDef GameRegistry::get_game_stats() const {
    return game_stats_;
}

void GameRegistry::set_game_stats(const GameStatsDef& def) {
    game_stats_ = def;
}

GameStatsDef GameRegistry::to_game_stats_def(const Game& game) {
    GameStatsDef def;
    def.is_game_started = game.get_is_game_started();
    def.is_game_loop_ended = game.get_is_game_loop_ended();
    def.is_game_ended = game.get_is_game_ended();
    return def;
}

void GameRegistry::from_game_stats_def(Game& game, const GameStatsDef& def) {
    game.set_is_game_started(def.is_game_started);
    game.set_is_game_loop_ended(def.is_game_loop_ended);
    game.set_is_game_ended(def.is_game_ended);
}
