#include "BattleSystem.h"

BattleSystem::BattleSystem(Player& player, Enemy* enemy, Renderer& renderer,
                           Location* location,
                           std::vector<Ability*>& player_abilities,
                           std::vector<Ability*>& enemy_abilities)
    : player_(player),
      enemy_(enemy),
      renderer_(renderer),
      current_location_(location),
      player_abilities_(player_abilities),
      enemy_abilities_(enemy_abilities) {}

void BattleSystem::player_attack() {
  if (player_.get_stamina() > 0) {
    if (enemy_choice_ == 2) {
      enemy_->set_is_shield_on(1);
      enemy_->set_shield(enemy_->get_shield() - player_.get_damage());
      player_.set_stamina(player_.get_stamina() - player_.get_stamina_factor());

      if (enemy_->get_shield() > 0) {
        renderer_.print_endline_text("Вы ударили в блок");
      } else {
        renderer_.print_endline_text("Вы пробили щит");
        enemy_->set_hp(enemy_->get_hp() + enemy_->get_shield());
      }
    } else if (enemy_choice_ == 3) {
      enemy_->set_is_dodge_on(1);
      player_.set_stamina(player_.get_stamina() - player_.get_stamina_factor());
      renderer_.print_endline_text("Вы промахнулись");
    } else {
      player_.set_stamina(player_.get_stamina() - player_.get_stamina_factor());
      renderer_.print_endline_text("Вы попали");
      enemy_->set_hp(enemy_->get_hp() - player_.get_damage());
    }
  } else {
    renderer_.print_endline_text("Не хватает выносливости");
  }
}

void BattleSystem::player_defence() {
  if (player_.get_shield() > 0) {
    player_.set_is_shield_on(1);
    renderer_.print_endline_text("Вы поставили блок");

    if (enemy_choice_ == 1) {
      player_.set_shield(player_.get_shield() - enemy_->get_damage());
      enemy_->set_stamina(enemy_->get_stamina() - enemy_->get_stamina_factor());

      if (player_.get_shield() > 0) {
        renderer_.print_endline_text("Враг ударил в блок");
      } else {
        renderer_.print_endline_text("Враг пробил щит");
        player_.set_hp(player_.get_hp() + player_.get_shield());
      }
    } else if (enemy_choice_ > 3 &&
               enemy_abilities_[enemy_choice_ - 4]->get_type() == 'd') {
      player_.set_shield(player_.get_shield() -
                         enemy_abilities_[enemy_choice_ - 4]->get_factor());
      enemy_abilities_[enemy_choice_ - 4]->set_moves_count(
          enemy_abilities_[enemy_choice_ - 4]->get_moves_count() - 1);

      if (player_.get_shield() > 0) {
        renderer_.print_endline_text("Враг ударил в блок");
      } else {
        renderer_.print_endline_text("Враг пробил щит");
        player_.set_hp(player_.get_hp() + player_.get_shield());
      }
    }
  } else {
    renderer_.print_endline_text("Щита нет");
  }
}

void BattleSystem::player_dodge() {
  if (player_.get_is_dodge_on() == 0) {
    renderer_.print_endline_text("Вы уклонились");
    player_.set_is_dodge_on(1);

    if (enemy_choice_ == 1) {
      enemy_->set_stamina(enemy_->get_stamina() - enemy_->get_stamina_factor());
      renderer_.print_endline_text("Враг промахнулся");
    } else if (enemy_choice_ > 3 &&
               enemy_abilities_[enemy_choice_ - 4]->get_type() == 'd') {
      renderer_.print_endline_text("Враг промахнулся");
      enemy_abilities_[enemy_choice_ - 4]->set_moves_count(
          enemy_abilities_[enemy_choice_ - 4]->get_moves_count() - 1);
    }
  } else {
    renderer_.print_endline_text("Вы не можете уклониться");
  }
}

void BattleSystem::player_ability() {
  int idx = user_choice_ - 4;
  if (player_abilities_[idx]->get_moves_count() ==
      player_abilities_[idx]->get_max_moves_count()) {
    player_abilities_[idx]->set_moves_count(
        player_abilities_[idx]->get_moves_count() - 1);
    renderer_.print_text("Вы использовали способность ");
    renderer_.print_endline_text(player_abilities_[idx]->get_name());

    switch (player_abilities_[idx]->get_type()) {
      case 'd':
        if (enemy_choice_ == 2) {
          enemy_->set_is_shield_on(1);
          enemy_->set_shield(enemy_->get_shield() -
                             player_abilities_[idx]->get_factor());

          if (enemy_->get_shield() > 0) {
            renderer_.print_endline_text("Вы ударили в блок");
          } else {
            renderer_.print_endline_text("Вы пробили щит");
            enemy_->set_hp(enemy_->get_hp() + enemy_->get_shield());
          }
        } else if (enemy_choice_ == 3) {
          enemy_->set_is_dodge_on(1);
          renderer_.print_endline_text("Вы промахнулись");
        } else {
          enemy_->set_hp(enemy_->get_hp() -
                         player_abilities_[idx]->get_factor());
          renderer_.print_endline_text("Вы попали");
        }
        break;
      case 'h':
        if (player_.get_hp() + player_abilities_[idx]->get_factor() > player_hp_) {
          player_.set_hp(player_hp_);
        } else {
          player_.set_hp(player_.get_hp() + player_abilities_[idx]->get_factor());
        }
        break;
      default:
        break;
    }
  } else {
    renderer_.print_endline_text("Вы не можете использовать эту способность");
  }
}

void BattleSystem::enemy_attack() {
  if (user_choice_ != 2 && user_choice_ != 3) {
    player_.set_hp(player_.get_hp() - enemy_->get_damage());
    renderer_.print_endline_text("Враг попал");
  }
}

void BattleSystem::enemy_defence() {
  enemy_->set_is_shield_on(1);
  renderer_.print_endline_text("Враг поставил блок");
}

void BattleSystem::enemy_dodge() {
  enemy_->set_is_dodge_on(1);
  renderer_.print_endline_text("Враг уклонился");
}

void BattleSystem::enemy_ability() {
  int idx = enemy_choice_ - 4;
  enemy_abilities_[idx]->set_moves_count(
      enemy_abilities_[idx]->get_moves_count() - 1);
  renderer_.print_text("Враг использовал способность ");
  renderer_.print_endline_text(enemy_abilities_[idx]->get_name());

  switch (enemy_abilities_[idx]->get_type()) {
    case 'd':
      if (user_choice_ != 2 && user_choice_ != 3) {
        player_.set_hp(player_.get_hp() - enemy_abilities_[idx]->get_factor());
        renderer_.print_endline_text("Враг попал");
      }
      break;
    case 'h':
      if (enemy_->get_hp() + enemy_abilities_[idx]->get_factor() > enemy_hp_) {
        enemy_->set_hp(enemy_hp_);
      } else {
        enemy_->set_hp(enemy_->get_hp() + enemy_abilities_[idx]->get_factor());
      }
      break;
    default:
      break;
  }
}

void BattleSystem::prepare_battle() {
  player_hp_ = player_.get_hp();
  enemy_hp_ = enemy_->get_hp();
  renderer_.print_text("Ваш враг: ");
  renderer_.print_endline_text(enemy_->get_name());
}

void BattleSystem::start_battle() {
  player_.init_dodge_count();
  enemy_->init_dodge_count();
  renderer_.print_endline_text("Введите");
  renderer_.print_endline_text("1: Атака");
  renderer_.print_endline_text("2: Защита");
  renderer_.print_endline_text("3: Уклонение");

  for (int i = 0; i < player_.get_abilities_count(); i++) {
    renderer_.print_text(i + player_.get_abilities_count() + 1);
    renderer_.print_text(": ");
    renderer_.print_endline_text(player_abilities_[i]->get_name());
  }

  user_choice_ = 0;
  enemy_choice_ = enemy_move();
  std::cin >> user_choice_;
}

bool BattleSystem::end_battle() {
  player_.refresh_stats_after_round();
  enemy_->refresh_stats_after_round();

  for (int i = 0; i < player_.get_abilities_count(); i++) {
    player_abilities_[i]->refresh_moves_count();
    enemy_abilities_[i]->refresh_moves_count();
  }

  if (enemy_->get_hp() <= 0 && player_.get_hp() > 0) {
    renderer_.print_endline_text("Вы победили");
    player_.win_round(enemy_->get_id(), player_hp_);
    current_location_->set_items(enemy_->get_items());
    current_location_->set_enemy_id(0);
    current_location_->set_dialog_node_id(0);

    for (int i = 0; i < enemy_abilities_.size(); i++) {
      enemy_abilities_[i]->set_moves_count(enemy_abilities_[i]->get_max_moves_count());
      player_abilities_[i]->set_moves_count(player_abilities_[i]->get_max_moves_count());
    }

    return true;
  } else if (player_.get_hp() <= 0) {
    renderer_.print_endline_text("Вы проиграли");
    player_.lose_round(player_hp_);
    enemy_->win_round(enemy_hp_);

    for (int i = 0; i < enemy_abilities_.size(); i++) {
      enemy_abilities_[i]->set_moves_count(enemy_abilities_[i]->get_max_moves_count());
      player_abilities_[i]->set_moves_count(player_abilities_[i]->get_max_moves_count());
    }

    return true;
  } else {
    player_.after_round_info();
    enemy_->after_round_info();

    for (int i = 0; i < player_.get_abilities_count(); i++) {
      player_abilities_[i]->count_moves();
    }

    return false;
  }
}

void BattleSystem::clash() {
  if (user_choice_ == 1) {
    player_attack();
  } else if (user_choice_ == 2) {
    player_defence();
  } else if (user_choice_ == 3) {
    player_dodge();
  } else if (user_choice_ >= 4 &&
             user_choice_ <= (3 + player_.get_abilities_count())) {
    player_ability();
  } else {
    renderer_.print_endline_text("Неверный ввод");
  }

  if (enemy_choice_ == 1) {
    enemy_attack();
  } else if (enemy_choice_ == 2) {
    enemy_defence();
  } else if (enemy_choice_ == 3) {
    enemy_dodge();
  } else if (enemy_choice_ >= 4 &&
             enemy_choice_ <= (3 + enemy_->get_abilities_count())) {
    enemy_ability();
  }
}

int BattleSystem::enemy_move() {
  srand(time(0));
  while (true) {
    enemy_choice_ = rand() % (3 + enemy_->get_abilities_count()) + 1;

    if (enemy_choice_ == 1 && enemy_->get_stamina() > 0) break;
    if (enemy_choice_ == 2 && enemy_->get_shield() > 0) break;
    if (enemy_choice_ == 3 && enemy_->get_is_dodge_on() == 0) break;

    if (enemy_choice_ >= 4 &&
        enemy_choice_ <= (3 + enemy_->get_abilities_count())) {
      if (enemy_abilities_[enemy_choice_ - 4]->get_moves_count() ==
          enemy_abilities_[enemy_choice_ - 4]->get_max_moves_count()) {
        break;
      }
    }
  }

  return enemy_choice_;
}

void BattleSystem::battle() {
  prepare_battle();
  bool battle_over = false;
  do {
    start_battle();
    clash();
    battle_over = end_battle();
  } while (!battle_over);
}
