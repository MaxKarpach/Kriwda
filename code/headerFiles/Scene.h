#include <iostream>

#ifndef SCENE_H
#define SCENE_H

struct SceneDef {
  int id;
  int dialog_node_id;
  char type;
  std::string text;
};

class Scene {
 public:
  Scene(const SceneDef& def);

  int get_id() const { return id_; }
  void set_id(int value) { id_ = value; }

  int get_dialog_node_id() const { return dialog_node_id_; }
  void set_dialog_node_id(int value) { dialog_node_id_ = value; }

  char get_type() const { return type_; }
  void set_type(char value) { type_ = value; }

  std::string get_text() const { return text_; }
  void set_text(std::string value) { text_ = value; }

 private:
  int id_;
  int dialog_node_id_;
  char type_;
  std::string text_;
};

class SceneRegistry {
 public:
  void load(std::istream& is);
  std::vector<SceneDef> get_scenes();
  void save(std::ostream& os);
  std::vector<SceneDef> to_scene_defs(const std::vector<Scene>& scenes);
  void set_scenes(const std::vector<SceneDef>& defs);

 private:
  std::vector<SceneDef> scenes_;
};

#endif
