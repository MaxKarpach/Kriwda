#include <DialogSystem.h>

DialogSystem::DialogSystem(std::vector<DialogNode>& dialog_nodes,
                           std::vector<DialogChoice>& dialog_choices,
                           int& current_node_id,
                           Location* current_location,
                           Renderer& renderer)
    : dialog_nodes_(dialog_nodes),
      dialog_choices_(dialog_choices),
      current_node_id_(current_node_id),
      current_location_(current_location),
      renderer_(renderer) {}

void DialogSystem::start_dialog() {
  while (true) {
    DialogNode* current_node = nullptr;

    for (auto& node : dialog_nodes_) {
      if (node.get_id() == current_node_id_) {
        current_node = &node;
        break;
      }
    }

    if (!current_node) {
      renderer_.print_endline_text("Ошибка: узел диалога не найден.");
      break;
    }

    if (!current_node->get_description().empty()) {
      renderer_.print_endline_text(current_node->get_description());
    }

    if (current_node->get_choices().empty()) {
      current_location_->set_dialog_node_id(0);
    }

    if (!current_node->get_name().empty()) {
      renderer_.print_text(current_node->get_name());
      renderer_.print_text(": ");
      renderer_.print_endline_text(current_node->get_text());
    }

    std::vector<DialogChoice*> current_choices;
    for (int choice_id : current_node->get_choices()) {
      for (auto& choice : dialog_choices_) {
        if (choice.get_id() == choice_id && !choice.get_is_used()) {
          current_choices.push_back(&choice);
          break;
        }
      }
    }

    if (current_choices.empty()) {
      break;
    }

    renderer_.print_endline_text("0: выход");
    for (int i = 0; i < current_choices.size(); ++i) {
      renderer_.print_text(i + 1);
      renderer_.print_text(": ");
      renderer_.print_endline_text(current_choices[i]->get_text());
    }

    int user_choice = 0;
    std::cin >> user_choice;

    if (user_choice <= 0 || user_choice > current_choices.size()) {
      renderer_.print_endline_text("Диалог прерван.");
      break;
    }

    current_node_id_ = current_choices[user_choice - 1]->get_next_node_id();
    current_choices[user_choice - 1]->set_is_used(true);

    if (current_node_id_ == 0) {
      current_location_->set_dialog_node_id(0);
      break;
    }
  }
}
