#include "BattleSystem.h"
#include <iostream>
BattleSystem::BattleSystem(Player& player, Enemy* enemy, Renderer& renderer,
    Location* location, std::vector<Ability*>& 
     playerAbilities, std::vector<Ability*>& enemyAbilities)
    :player(player),enemy(enemy), renderer(renderer), currentLocation(location),
    playerAbilities(playerAbilities), enemyAbilities(enemyAbilities){}

void BattleSystem::prepareBattle(){
    playerHp = player.getHp();
    enemyHp = enemy->getHp();
    renderer.printText("Ваш враг: ");
    renderer.printEndlineText(enemy->getName());
}

void BattleSystem::startBattle(){
        player.initDodgeCount();
        enemy->initDodgeCount();
        renderer.printEndlineText("Введите");
        renderer.printEndlineText("1: Атака");
        renderer.printEndlineText("2: Защита");
        renderer.printEndlineText("3: Уклонение");
        for (int i = 0; i < player.getAbilitiesCount(); i++) {
            renderer.printText(i + player.getAbilitiesCount() + 1);
            renderer.printText(": ");
            renderer.printEndlineText(playerAbilities[i]->getName());
        }
        userChoice = 0;
        enemyChoice = enemyMove();
        std::cin >> userChoice;
}

bool BattleSystem::endBattle(){
       player.refreshStatsAfterRound();
       enemy->refreshStatsAfterRound();
        for (int i = 0; i < player.getAbilitiesCount(); i++) {
            playerAbilities[i]->refreshMovesCount();
            enemyAbilities[i]->refreshMovesCount();
        }
        if (enemy->getHp() <= 0){
            renderer.printEndlineText("Вы победили");
            player.addToEnemies(enemy->getId());
            currentLocation->setItems(enemy->getItems());
            currentLocation->setEnemyId(0);
            currentLocation->setDialogNodeId(0);
            for (int i = 0; i < enemyAbilities.size();i++){
                    enemyAbilities[i]->setMovesCount(enemyAbilities[i]->getMaxMovesCount());
                    playerAbilities[i]->setMovesCount(playerAbilities[i]->getMaxMovesCount());
            }
            return true;
        }
        else if (player.getHp() <= 0){
                renderer.printEndlineText("Вы проиграли");
                player.loseRound(playerHp);
                enemy->winRound(enemyHp);
                for (int i = 0; i < enemyAbilities.size();i++){
                    enemyAbilities[i]->setMovesCount(enemyAbilities[i]->getMaxMovesCount());
                    playerAbilities[i]->setMovesCount(playerAbilities[i]->getMaxMovesCount());
                }
                    return true;
            }
            else{
                player.afterRoundInfo();
                enemy->afterRoundInfo();
                for (int i = 0; i < player.getAbilitiesCount(); i++) {
                playerAbilities[i]->countMoves();
                }
                return false;
            }
}

void BattleSystem::clash(){
        if (userChoice == 1){
            if (player.getStamina() > 0){
                if (enemyChoice == 2){
                    enemy->setIsShieldOn(1);
                    enemy->setShield(enemy->getShield() - player.getDamage());
                    player.setStamina(player.getStamina() - player.getStaminaFactor());
                    if (enemy->getShield() > 0){
                    renderer.printEndlineText("Вы ударили в блок");
                    } else {
                    renderer.printEndlineText("Вы пробили щит");
                     enemy->setHp(enemy->getHp() + enemy->getShield());
                    }
                } else if(enemyChoice == 3){
                            enemy->setIsDodgeOn(1);
                            player.setStamina(player.getStamina() - player.getStaminaFactor());
                            renderer.printEndlineText("Вы промахнулись");
                } else {
                    player.setStamina(player.getStamina() - player.getStaminaFactor());
                    renderer.printEndlineText("Вы попали");
                    enemy->setHp(enemy->getHp() - player.getDamage());
                }
            } else {
                    renderer.printEndlineText("Не хватает выносливости");
            }
        } else if (userChoice == 2){
                if (player.getShield() > 0){
                    player.setIsShieldOn(1);
                    renderer.printEndlineText("Вы поставили блок");
                    if (enemyChoice == 1){
                        player.setShield(player.getShield() - enemy->getDamage());
                        enemy->setStamina(enemy->getStamina() - enemy->getStaminaFactor());
                        if (player.getShield() > 0){
                            renderer.printEndlineText("Враг ударил в блок");
                        } else {
                            renderer.printEndlineText("Враг пробил щит");
                            player.setHp(player.getHp() + player.getShield());
                        }
                    } else if (enemyChoice > 3 && enemyAbilities[enemyChoice - 4]->getType() == 'd'){
                            player.setShield(player.getShield() - enemyAbilities[enemyChoice - 4]->getFactor());
                            enemyAbilities[enemyChoice - 4]->setMovesCount(enemyAbilities[enemyChoice - 4]->getMovesCount() - 1);
                            if (player.getShield() > 0){
                               renderer.printEndlineText("Враг ударил в блок");
                            } else {
                                renderer.printEndlineText("Враг пробил щит");
                                player.setHp(player.getHp() + player.getShield());
                            }
                    }
                } else {
                    renderer.printEndlineText("Щита нет");
                }
        } else if (userChoice == 3){
                if (player.getIsDodgeOn() == 0){
                    renderer.printEndlineText("Вы уклонились");
                    player.setIsDodgeOn(1);
                    if (enemyChoice == 1){
                        enemy->setStamina(enemy->getStamina() - enemy->getStaminaFactor());
                        renderer.printEndlineText("Враг промахнулся");
                    } else if (enemyChoice > 3 && enemyAbilities[enemyChoice - 4]->getType() == 'd'){
                            renderer.printEndlineText("Враг промахнулся");
                            enemyAbilities[enemyChoice - 4]->setMovesCount(enemyAbilities[enemyChoice - 4]->getMovesCount() - 1);
                    }
                } else {
                    renderer.printEndlineText("Вы не можете уклониться");
                }
        } else if (userChoice >= 4 && userChoice <= (3+player.getAbilitiesCount())){
            if (playerAbilities[userChoice-4]->getMovesCount() == playerAbilities[userChoice-4]->getMaxMovesCount()){
                playerAbilities[userChoice-4]->setMovesCount(playerAbilities[userChoice-4]->getMovesCount() - 1);
                renderer.printText("Вы использовали способность ");
                renderer.printEndlineText(playerAbilities[userChoice-4]->getName());
                if (playerAbilities[userChoice-4]->getType() == 'd'){
                    if (enemyChoice == 2){
                        enemy->setIsShieldOn(1);
                        enemy->setShield(enemy->getShield() - playerAbilities[userChoice-4]->getFactor());
                        if (enemy->getShield() > 0){
                        renderer.printEndlineText("Вы ударили в блок");
                        }
                        else {
                        renderer.printEndlineText("Вы пробили щит");
                        enemy->setHp(enemy->getHp() + enemy->getShield());
                        }
                    } else if (enemyChoice == 3){
                        enemy->setIsDodgeOn(1);
                        renderer.printEndlineText("Вы промахнулись");
                    } else {
                        enemy->setHp(enemy->getHp() - playerAbilities[userChoice-4]->getFactor());
                        renderer.printEndlineText("Вы попали");
                    }
                } else {
                    player.setHp(player.getHp() + playerAbilities[userChoice-4]->getFactor());
                }
            } else {
                renderer.printEndlineText("Вы не можете использовать эту способность");
            }
        }
        else {
            renderer.printEndlineText("Неверный ввод");
        }
        
        if (enemyChoice == 1){
            player.setHp(player.getHp() - enemy->getDamage());
            renderer.printEndlineText("Враг попал");
        } else if (enemyChoice == 2) {
            enemy->setIsShieldOn(1);
            renderer.printEndlineText("Враг поставил блок");
        } else if (enemyChoice == 3) {
            enemy->setIsDodgeOn(1);
            renderer.printEndlineText("Враг уклонился");
        } else if (enemyChoice >= 4 && enemyChoice <= (3+enemy->getAbilitiesCount())){
                enemyAbilities[enemyChoice-4]->setMovesCount(enemyAbilities[enemyChoice-4]->getMovesCount() - 1);
                renderer.printText("Враг использовал способность ");
                renderer.printEndlineText(enemyAbilities[enemyChoice-4]->getName());
                if (enemyAbilities[enemyChoice-4]->getType() == 'd'){
                    player.setHp(player.getHp() - enemyAbilities[enemyChoice-4]->getFactor());
                    renderer.printEndlineText("Враг попал");  
                } else {
                    enemy->setHp(enemy->getHp() + enemyAbilities[enemyChoice-4]->getFactor());
                }
        }
}

int BattleSystem::enemyMove(){
    srand(time(0));
    while (true)
    {
        enemyChoice = rand() % (3+enemy->getAbilitiesCount()) + 1;
        std::cout << enemyChoice << std::endl;
        if (enemyChoice == 1) {
            if (enemy->getStamina() > 0){
                break;
            }
        } else if (enemyChoice == 2) {
            if (enemy->getShield() > 0){
                break;
            }
        } else if (enemyChoice == 3) {
            if (enemy->getIsDodgeOn() == 0){
                break;
            }
        } else if (enemyChoice >= 4 && enemyChoice <= (3+enemy->getAbilitiesCount())){
            if (enemyAbilities[enemyChoice-4]->getMovesCount() == enemyAbilities[enemyChoice-4]->getMaxMovesCount()){
                break;
            }
    }
    }
    return enemyChoice;
}

void BattleSystem::battle(){
    prepareBattle();
    bool battleOver = false;
    do {
    startBattle();
    clash();
    battleOver = endBattle();
    } while (!battleOver);
}