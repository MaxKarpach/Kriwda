#include <iostream>
#ifndef SCENE_H
#define SCENE_H
struct SceneDef{
    int id;
    int dialogNodeId;
};

class Scene {
public:
    Scene(const SceneDef& def);

    int getId() const { return id; }
    void setId(int value) { id = value; }

    int getDialogNodeId() const { return dialogNodeId; }
    void setDialogNodeId(int value) { dialogNodeId = value; }


private:
    int id;
    int dialogNodeId;
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