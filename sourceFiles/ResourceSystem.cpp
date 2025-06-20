#include "ResourceSystem.h"
#include <fstream>

ResourceSystem::ResourceSystem(Player& player,
                               std::vector<Location>& locations,
                               std::vector<Enemy>& enemies,
                               std::vector<Ability>& abilities,
                               std::vector<Item>& items,
                               std::vector<DialogNode>& dialog_nodes,
                               std::vector<DialogChoice>& dialog_choices,
                               std::vector<Scene>& scenes,
                               Game& game,
                               std::string& file_name)
    : player_(player),
      locations_(locations),
      enemies_(enemies),
      abilities_(abilities),
      items_(items),
      dialog_nodes_(dialog_nodes),
      dialog_choices_(dialog_choices),
      scenes_(scenes),
      game_(game),
      file_name_(file_name) {}

void ResourceSystem::download_data() {
  std::ifstream input(file_name_);

  PlayerRegistry player_registry;
  player_registry.load(input);
  player_ = player_registry.get_player();

  locations_.clear();
  enemies_.clear();
  abilities_.clear();
  items_.clear();
  dialog_nodes_.clear();
  dialog_choices_.clear();
  scenes_.clear();

  LocationRegistry location_registry;
  location_registry.load(input);
  std::vector<LocationDef> location_defs = location_registry.get_locations();
  for (const LocationDef& def : location_defs) {
    locations_.push_back(Location(def));
  }

  EnemyRegistry enemy_registry;
  enemy_registry.load(input);
  std::vector<EnemyDef> enemy_defs = enemy_registry.get_enemies();
  for (const EnemyDef& def : enemy_defs) {
    enemies_.push_back(Enemy(def));
  }

  AbilityRegistry ability_registry;
  ability_registry.load(input);
  std::vector<AbilityDef> ability_defs = ability_registry.get_abilities();
  for (const AbilityDef& def : ability_defs) {
    abilities_.push_back(Ability(def));
  }

  ItemRegistry item_registry;
  item_registry.load(input);
  std::vector<ItemDef> item_defs = item_registry.get_items();
  for (const ItemDef& def : item_defs) {
    items_.push_back(Item(def));
  }

  DialogNodeRegistry dialog_node_registry;
  dialog_node_registry.load(input);
  std::vector<DialogNodeDef> dialog_node_defs = dialog_node_registry.get_dialog_nodes();
  for (const DialogNodeDef& def : dialog_node_defs) {
    dialog_nodes_.push_back(DialogNode(def));
  }

  DialogChoiceRegistry dialog_choice_registry;
  dialog_choice_registry.load(input);
  std::vector<DialogChoiceDef> dialog_choice_defs = dialog_choice_registry.get_dialog_choices();
  for (const DialogChoiceDef& def : dialog_choice_defs) {
    dialog_choices_.push_back(DialogChoice(def));
  }

  SceneRegistry scene_registry;
  scene_registry.load(input);
  std::vector<SceneDef> scene_defs = scene_registry.get_scenes();
  for (const SceneDef& def : scene_defs) {
    scenes_.push_back(Scene(def));
  }

  GameRegistry game_registry;
  game_registry.load(input);
  const GameStatsDef& stats = game_registry.get_game_stats();
  game_.set_is_game_started(stats.is_game_started);
  game_.set_is_game_loop_ended(stats.is_game_loop_ended);
  game_.set_is_game_ended(stats.is_game_ended);
}

void ResourceSystem::save_game() {
  std::ofstream output(file_name_);

  PlayerRegistry player_registry;
  PlayerDef player_def = player_registry.to_player_def(player_);
  player_registry.set_player(player_def);
  player_registry.save(output);

  LocationRegistry location_registry;
  std::vector<LocationDef> location_defs = location_registry.to_location_defs(locations_);
  location_registry.set_locations(location_defs);
  location_registry.save(output);

  EnemyRegistry enemy_registry;
  std::vector<EnemyDef> enemy_defs = enemy_registry.to_enemy_defs(enemies_);
  enemy_registry.set_enemies(enemy_defs);
  enemy_registry.save(output);

  AbilityRegistry ability_registry;
  std::vector<AbilityDef> ability_defs = ability_registry.to_ability_defs(abilities_);
  ability_registry.set_abilities(ability_defs);
  ability_registry.save(output);

  ItemRegistry item_registry;
  std::vector<ItemDef> item_defs = item_registry.to_item_defs(items_);
  item_registry.set_items(item_defs);
  item_registry.save(output);

  DialogNodeRegistry dialog_node_registry;
  std::vector<DialogNodeDef> dialog_node_defs = dialog_node_registry.to_dialog_node_defs(dialog_nodes_);
  dialog_node_registry.set_dialog_nodes(dialog_node_defs);
  dialog_node_registry.save(output);

  DialogChoiceRegistry dialog_choice_registry;
  std::vector<DialogChoiceDef> dialog_choice_defs =
      dialog_choice_registry.to_dialog_choice_defs(dialog_choices_);
  dialog_choice_registry.set_dialog_choices(dialog_choice_defs);
  dialog_choice_registry.save(output);

  SceneRegistry scene_registry;
  std::vector<SceneDef> scene_defs = scene_registry.to_scene_defs(scenes_);
  scene_registry.set_scenes(scene_defs);
  scene_registry.save(output);

  GameRegistry game_registry;
  GameStatsDef game_def = game_registry.to_game_stats_def(game_);
  game_registry.set_game_stats(game_def);
  game_registry.save(output);
}
