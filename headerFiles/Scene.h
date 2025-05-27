#include <iostream>
#ifndef SCENE_H
#define SCENE_H
struct SceneDef{
    int id;
    int dialogNodeId;
    char type;
    std::string text;
};

class Scene {
public:
    Scene(const SceneDef& def);

    int getId() const { return id; }
    void setId(int value) { id = value; }

    int getDialogNodeId() const { return dialogNodeId; }
    void setDialogNodeId(int value) { dialogNodeId = value; }

    char getType() const { return type; }
    void setType(char value) { type = value; }

    std::string getText() const { return text; }
    void setText(std::string value) {text = value; }

private:
    int id;
    int dialogNodeId;
    char type;
    std::string text;
};


class SceneRegistry{
    public:
    void load(std::istream& is);
    std::vector<SceneDef> getScenes();
    void save(std::ostream &os);
    std::vector<SceneDef> toSceneDefs(const std::vector<Scene> &scenes);
    void setScenes(const std::vector<SceneDef>& defs);
private:
    std::vector<SceneDef> scenes;
};
#endif