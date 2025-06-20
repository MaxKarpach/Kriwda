#include "ResourceSystem.h"
#include <fstream>

ResourceSystem::ResourceSystem(Player& player, std::vector<Location>& locations, std::vector<Enemy>& enemies,
    std::vector<Ability>& abilities, std::vector<Item>& items, std::vector<DialogNode>& dialogNodes,
    std::vector<DialogChoice>& dialogChoices, std::vector<Scene>& scenes, Game& game, std::string& fileName):
    player_(player), locations_(locations), enemies_(enemies),  abilities_(abilities),
    items_(items), dialogNodes_(dialogNodes), dialogChoices_(dialogChoices), scenes_(scenes),
    game_(game), fileName_(fileName){}

void ResourceSystem::downloadData(){
   std::ifstream input(fileName_);

  PlayerRegistry playerRegistry;
  playerRegistry.load(input);
  player_ = playerRegistry.getPlayer();

  locations_.clear();
  enemies_.clear();
  abilities_.clear();
  items_.clear();
  dialogNodes_.clear();
  dialogChoices_.clear();
  scenes_.clear();

  LocationRegistry locationRegistry;
  locationRegistry.load(input);
  std::vector<LocationDef> locationDefs = locationRegistry.getLocations();
  for (const LocationDef& def : locationDefs) {
    locations_.push_back(Location(def));
  }

  EnemyRegistry enemyRegistry;
  enemyRegistry.load(input);
  std::vector<EnemyDef> enemyDefs = enemyRegistry.getEnemies();
  for (const EnemyDef& def : enemyDefs) {
    enemies_.push_back(Enemy(def));
  }

  AbilityRegistry abilityRegistry;
  abilityRegistry.load(input);
  std::vector<AbilityDef> abilityDefs = abilityRegistry.getAbilities();
  for (const AbilityDef& def : abilityDefs) {
    abilities_.push_back(Ability(def));
  }

  ItemRegistry itemRegistry;
  itemRegistry.load(input);
  std::vector<ItemDef> itemDefs = itemRegistry.getItems();
  for (const ItemDef& def : itemDefs) {
    items_.push_back(Item(def));
  }

  DialogNodeRegistry dialogNodeRegistry;
  dialogNodeRegistry.load(input);
  std::vector<DialogNodeDef> dialogNodeDefs = dialogNodeRegistry.getDialogNodes();
  for (const DialogNodeDef& def : dialogNodeDefs) {
    dialogNodes_.push_back(DialogNode(def));
  }

  DialogChoiceRegistry dialogChoiceRegistry;
  dialogChoiceRegistry.load(input);
  std::vector<DialogChoiceDef> dialogChoiceDefs = dialogChoiceRegistry.getDialogChoices();
  for (const DialogChoiceDef& def : dialogChoiceDefs) {
    dialogChoices_.push_back(DialogChoice(def));
  }

  SceneRegistry sceneRegistry;
  sceneRegistry.load(input);
  std::vector<SceneDef> sceneDefs = sceneRegistry.getScenes();
  for (const SceneDef& def : sceneDefs) {
    scenes_.push_back(Scene(def));
  }

  GameRegistry gameRegistry;
  gameRegistry.load(input);
  game_.setIsGameStarted(gameRegistry.getGameStats().isGameStarted);
  game_.setIsGameLoopEnded(gameRegistry.getGameStats().isGameLoopEnded);
  game_.setIsGameEnded(gameRegistry.getGameStats().isGameEnded);
}

void ResourceSystem::saveGame(){

  std::ofstream output(fileName_);
  PlayerRegistry playerRegistry;
  PlayerDef playerDef = playerRegistry.toPlayerDef(player_);
  playerRegistry.setPlayer(playerDef);
  playerRegistry.save(output);

  LocationRegistry locationRegistry;
  std::vector<LocationDef> locationDefs = locationRegistry.toLocationDefs(locations_);
  locationRegistry.setLocations(locationDefs);
  locationRegistry.save(output);

  EnemyRegistry enemyRegistry;
  std::vector<EnemyDef> enemyDefs = enemyRegistry.toEnemyDefs(enemies_);
  enemyRegistry.setEnemies(enemyDefs);
  enemyRegistry.save(output);

  AbilityRegistry abilityRegistry;
  std::vector<AbilityDef> abilityDefs = abilityRegistry.toAbilityDefs(abilities_);
  abilityRegistry.setAbilities(abilityDefs);
  abilityRegistry.save(output);

  ItemRegistry itemRegistry;
  std::vector<ItemDef> itemDefs = itemRegistry.toItemDefs(items_);
  itemRegistry.setItems(itemDefs);
  itemRegistry.save(output);

  DialogNodeRegistry dialogNodeRegistry;
  std::vector<DialogNodeDef> dialogNodeDefs = dialogNodeRegistry.toDialogNodeDefs(dialogNodes_);
  dialogNodeRegistry.setDialogNodes(dialogNodeDefs);
  dialogNodeRegistry.save(output);

  DialogChoiceRegistry dialogChoiceRegistry;
  std::vector<DialogChoiceDef> dialogChoiceDefs = dialogChoiceRegistry.toDialogChoiceDefs(dialogChoices_);
  dialogChoiceRegistry.setDialogChoices(dialogChoiceDefs);
  dialogChoiceRegistry.save(output);

  SceneRegistry sceneRegistry;
  std::vector<SceneDef> sceneDefs = sceneRegistry.toSceneDefs(scenes_);
  sceneRegistry.setScenes(sceneDefs);
  sceneRegistry.save(output);

  GameRegistry gameRegistry;
  GameStatsDef gameDef = gameRegistry.toGameStatsDef(game_);
  gameRegistry.setGameStats(gameDef);
  gameRegistry.save(output);
}