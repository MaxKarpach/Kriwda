#include "../headerFiles/Scene.h" 
#include <iostream>
#include <climits>

const int MAX_STRING_LEN = 100;

Scene::Scene(const SceneDef& def)
:id(def.id), dialogNodeId(def.dialogNodeId){}

std::vector<SceneDef> SceneRegistry::getScenes(){
    return scenes;
}

void SceneRegistry::load(std::istream& is){
    int scenesCount = 0;
    is >> scenesCount;
    for (int i = 0; i < scenesCount;i++){
        SceneDef ed;
        is >> ed.id;
        is >> ed.dialogNodeId;
        scenes.push_back(ed);
    }
}
void SceneRegistry::save(std::ostream& os){
    os << scenes.size() << std::endl;
    for (const SceneDef& sd :scenes) {
        os << sd.id << std::endl;
        os << sd.dialogNodeId << std::endl;
    }
}
std::vector<SceneDef> SceneRegistry::toSceneDefs(const std::vector<Scene>& scenes) {
    std::vector<SceneDef> sceneDefs;
    for (const auto& scene : scenes) {
        SceneDef def;
        def.id = scene.getId();
        def.dialogNodeId = scene.getDialogNodeId();
        sceneDefs.push_back(def);
    }
    return sceneDefs;
}
void SceneRegistry::setScenes(const std::vector<SceneDef>& defs){
    scenes = defs;
}