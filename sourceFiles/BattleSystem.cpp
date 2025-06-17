#include "BattleSystem.h"

#include <iostream>

BattleSystem::BattleSystem(Player& player, Enemy* enemy, Renderer& renderer,
                           Location* location,
                           std::vector<Ability*>& playerAbilities,
                           std::vector<Ability*>& enemyAbilities)
    : player_(player),
      enemy_(enemy),
      renderer_(renderer),
      currentLocation_(location),
      playerAbilities_(playerAbilities),
      enemyAbilities_(enemyAbilities) {}

void BattleSystem::prepareBattle() {
  playerHp_ = player_.getHp();
  enemyHp_ = enemy_->getHp();
  renderer_.printText("Ваш враг: ");
  renderer_.printEndlineText(enemy_->getName());
}

void BattleSystem::startBattle() {
  player_.initDodgeCount();
  enemy_->initDodgeCount();
  renderer_.printEndlineText("Введите");
  renderer_.printEndlineText("1: Атака");
  renderer_.printEndlineText("2: Защита");
  renderer_.printEndlineText("3: Уклонение");
  for (int i = 0; i < player_.getAbilitiesCount(); i++) {
    renderer_.printText(i + player_.getAbilitiesCount() + 1);
    renderer_.printText(": ");
    renderer_.printEndlineText(playerAbilities_[i]->getName());
  }
  userChoice_ = 0;
  enemyChoice_ = enemyMove();
  std::cin >> userChoice_;
}

bool BattleSystem::endBattle() {
  player_.refreshStatsAfterRound();
  enemy_->refreshStatsAfterRound();

  for (int i = 0; i < player_.getAbilitiesCount(); i++) {
    playerAbilities_[i]->refreshMovesCount();
    enemyAbilities_[i]->refreshMovesCount();
  }

  if (enemy_->getHp() <= 0 && player_.getHp() > 0) {
    renderer_.printEndlineText("Вы победили");
    player_.winRound(enemy_->getId(), playerHp_);
    currentLocation_->setItems(enemy_->getItems());
    currentLocation_->setEnemyId(0);
    currentLocation_->setDialogNodeId(0);

    for (int i = 0; i < enemyAbilities_.size(); i++) {
      enemyAbilities_[i]->setMovesCount(enemyAbilities_[i]->getMaxMovesCount());
      playerAbilities_[i]->setMovesCount(playerAbilities_[i]->getMaxMovesCount());
    }

    return true;

  } else if (player_.getHp() <= 0) {
    renderer_.printEndlineText("Вы проиграли");
    player_.loseRound(playerHp_);
    enemy_->winRound(enemyHp_);

    for (int i = 0; i < enemyAbilities_.size(); i++) {
      enemyAbilities_[i]->setMovesCount(enemyAbilities_[i]->getMaxMovesCount());
      playerAbilities_[i]->setMovesCount(playerAbilities_[i]->getMaxMovesCount());
    }

    return true;

  } else {
    player_.afterRoundInfo();
    enemy_->afterRoundInfo();

    for (int i = 0; i < player_.getAbilitiesCount(); i++) {
      playerAbilities_[i]->countMoves();
    }

    return false;
  }
}

void BattleSystem::clash() {
  if (userChoice_ == 1) {
    if (player_.getStamina() > 0) {
      if (enemyChoice_ == 2) {
        enemy_->setIsShieldOn(1);
        enemy_->setShield(enemy_->getShield() - player_.getDamage());
        player_.setStamina(player_.getStamina() - player_.getStaminaFactor());

        if (enemy_->getShield() > 0) {
          renderer_.printEndlineText("Вы ударили в блок");
        } else {
          renderer_.printEndlineText("Вы пробили щит");
          enemy_->setHp(enemy_->getHp() + enemy_->getShield());
        }

      } else if (enemyChoice_ == 3) {
        enemy_->setIsDodgeOn(1);
        player_.setStamina(player_.getStamina() - player_.getStaminaFactor());
        renderer_.printEndlineText("Вы промахнулись");

      } else {
        player_.setStamina(player_.getStamina() - player_.getStaminaFactor());
        renderer_.printEndlineText("Вы попали");
        enemy_->setHp(enemy_->getHp() - player_.getDamage());
      }

    } else {
      renderer_.printEndlineText("Не хватает выносливости");
    }

  } else if (userChoice_ == 2) {
    if (player_.getShield() > 0) {
      player_.setIsShieldOn(1);
      renderer_.printEndlineText("Вы поставили блок");

      if (enemyChoice_ == 1) {
        player_.setShield(player_.getShield() - enemy_->getDamage());
        enemy_->setStamina(enemy_->getStamina() - enemy_->getStaminaFactor());

        if (player_.getShield() > 0) {
          renderer_.printEndlineText("Враг ударил в блок");
        } else {
          renderer_.printEndlineText("Враг пробил щит");
          player_.setHp(player_.getHp() + player_.getShield());
        }

      } else if (enemyChoice_ > 3 &&
                 enemyAbilities_[enemyChoice_ - 4]->getType() == 'd') {
        player_.setShield(
            player_.getShield() -
            enemyAbilities_[enemyChoice_ - 4]->getFactor());
        enemyAbilities_[enemyChoice_ - 4]->setMovesCount(
            enemyAbilities_[enemyChoice_ - 4]->getMovesCount() - 1);

        if (player_.getShield() > 0) {
          renderer_.printEndlineText("Враг ударил в блок");
        } else {
          renderer_.printEndlineText("Враг пробил щит");
          player_.setHp(player_.getHp() + player_.getShield());
        }
      }

    } else {
      renderer_.printEndlineText("Щита нет");
    }

  } else if (userChoice_ == 3) {
    if (player_.getIsDodgeOn() == 0) {
      renderer_.printEndlineText("Вы уклонились");
      player_.setIsDodgeOn(1);

      if (enemyChoice_ == 1) {
        enemy_->setStamina(enemy_->getStamina() - enemy_->getStaminaFactor());
        renderer_.printEndlineText("Враг промахнулся");

      } else if (enemyChoice_ > 3 &&
                 enemyAbilities_[enemyChoice_ - 4]->getType() == 'd') {
        renderer_.printEndlineText("Враг промахнулся");
        enemyAbilities_[enemyChoice_ - 4]->setMovesCount(
            enemyAbilities_[enemyChoice_ - 4]->getMovesCount() - 1);
      }

    } else {
      renderer_.printEndlineText("Вы не можете уклониться");
    }

  } else if (userChoice_ >= 4 &&
             userChoice_ <= (3 + player_.getAbilitiesCount())) {
    int idx = userChoice_ - 4;
    if (playerAbilities_[idx]->getMovesCount() ==
        playerAbilities_[idx]->getMaxMovesCount()) {
      playerAbilities_[idx]->setMovesCount(
          playerAbilities_[idx]->getMovesCount() - 1);
      renderer_.printText("Вы использовали способность ");
      renderer_.printEndlineText(playerAbilities_[idx]->getName());

      switch (playerAbilities_[idx]->getType()) {
        case 'd':
          if (enemyChoice_ == 2) {
            enemy_->setIsShieldOn(1);
            enemy_->setShield(enemy_->getShield() -
                              playerAbilities_[idx]->getFactor());

            if (enemy_->getShield() > 0) {
              renderer_.printEndlineText("Вы ударили в блок");
            } else {
              renderer_.printEndlineText("Вы пробили щит");
              enemy_->setHp(enemy_->getHp() + enemy_->getShield());
            }

          } else if (enemyChoice_ == 3) {
            enemy_->setIsDodgeOn(1);
            renderer_.printEndlineText("Вы промахнулись");

          } else {
            enemy_->setHp(enemy_->getHp() -
                          playerAbilities_[idx]->getFactor());
            renderer_.printEndlineText("Вы попали");
          }
          break;

        case 'h':
          if (player_.getHp() + playerAbilities_[idx]->getFactor() > playerHp_) {
            player_.setHp(playerHp_);
          } else {
            player_.setHp(player_.getHp() + playerAbilities_[idx]->getFactor());
          }
          break;

        default:
          break;
      }

    } else {
      renderer_.printEndlineText("Вы не можете использовать эту способность");
    }

  } else {
    renderer_.printEndlineText("Неверный ввод");
  }

  if (enemyChoice_ == 1) {
    if (userChoice_ != 2 && userChoice_ != 3) {
      player_.setHp(player_.getHp() - enemy_->getDamage());
      renderer_.printEndlineText("Враг попал");
    }

  } else if (enemyChoice_ == 2) {
    enemy_->setIsShieldOn(1);
    renderer_.printEndlineText("Враг поставил блок");

  } else if (enemyChoice_ == 3) {
    enemy_->setIsDodgeOn(1);
    renderer_.printEndlineText("Враг уклонился");

  } else if (enemyChoice_ >= 4 &&
             enemyChoice_ <= (3 + enemy_->getAbilitiesCount())) {
    int idx = enemyChoice_ - 4;
    enemyAbilities_[idx]->setMovesCount(
        enemyAbilities_[idx]->getMovesCount() - 1);
    renderer_.printText("Враг использовал способность ");
    renderer_.printEndlineText(enemyAbilities_[idx]->getName());

    switch (enemyAbilities_[idx]->getType()) {
      case 'd':
        if (userChoice_ != 2 && userChoice_ != 3) {
          player_.setHp(player_.getHp() - enemyAbilities_[idx]->getFactor());
          renderer_.printEndlineText("Враг попал");
        }
        break;

      case 'h':
        if (enemy_->getHp() + enemyAbilities_[idx]->getFactor() > enemyHp_) {
          enemy_->setHp(enemyHp_);
        } else {
          enemy_->setHp(enemy_->getHp() + enemyAbilities_[idx]->getFactor());
        }
        break;

      default:
        break;
    }
  }
}

int BattleSystem::enemyMove() {
  srand(time(0));
  while (true) {
    enemyChoice_ = rand() % (3 + enemy_->getAbilitiesCount()) + 1;

    if (enemyChoice_ == 1 && enemy_->getStamina() > 0) break;
    if (enemyChoice_ == 2 && enemy_->getShield() > 0) break;
    if (enemyChoice_ == 3 && enemy_->getIsDodgeOn() == 0) break;

    if (enemyChoice_ >= 4 &&
        enemyChoice_ <= (3 + enemy_->getAbilitiesCount())) {
      if (enemyAbilities_[enemyChoice_ - 4]->getMovesCount() ==
          enemyAbilities_[enemyChoice_ - 4]->getMaxMovesCount()) {
        break;
      }
    }
  }

  return enemyChoice_;
}

void BattleSystem::battle() {
  prepareBattle();
  bool battleOver = false;
  do {
    startBattle();
    clash();
    battleOver = endBattle();
  } while (!battleOver);
}
