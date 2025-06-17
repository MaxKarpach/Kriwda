#include <iostream>

#ifndef SCENE_H
#define SCENE_H

struct SceneDef {
  int id;
  int dialogNodeId;
  char type;
  std::string text;
};

class Scene {
 public:
  Scene(const SceneDef& def);

  int getId() const { return id_; }
  void setId(int value) { id_ = value; }

  int getDialogNodeId() const { return dialogNodeId_; }
  void setDialogNodeId(int value) { dialogNodeId_ = value; }

  char getType() const { return type_; }
  void setType(char value) { type_ = value; }

  std::string getText() const { return text_; }
  void setText(std::string value) { text_ = value; }

 private:
  int id_;
  int dialogNodeId_;
  char type_;
  std::string text_;
};

class SceneRegistry {
 public:
  void load(std::istream& is);
  std::vector<SceneDef> getScenes();
  void save(std::ostream& os);
  std::vector<SceneDef> toSceneDefs(const std::vector<Scene>& scenes);
  void setScenes(const std::vector<SceneDef>& defs);

 private:
  std::vector<SceneDef> scenes;
};

#endif  
