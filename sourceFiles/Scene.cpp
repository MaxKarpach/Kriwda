#include "../headerFiles/Scene.h" 
#include <iostream>
#include <climits>

const int MAX_STRING_LEN = 255;

Scene::Scene(const SceneDef& def)
:id_(def.id),dialogNodeId_(def.dialogNodeId), type_(def.type), text_(def.text){}

std::vector<SceneDef> SceneRegistry::getScenes(){
    return scenes;
}

void SceneRegistry::load(std::istream& is){
    int scenesCount = 0;
    is >> scenesCount;
    for (int i = 0; i < scenesCount;i++){
        SceneDef sd;
        is >> sd.id;
        is >> sd.dialogNodeId;
        is >> sd.type;
        is.ignore(MAX_STRING_LEN, '\n');
        std::getline(is, sd.text);
        scenes.push_back(sd);
    }
}
void SceneRegistry::save(std::ostream& os){
    os << scenes.size() << std::endl;
    for (const SceneDef& sd :scenes) {
        os << sd.id << std::endl;
        os << sd.dialogNodeId << std::endl;
        os << sd.type << std::endl;
        os << sd.text << std::endl;
    }
}
std::vector<SceneDef> SceneRegistry::toSceneDefs(const std::vector<Scene>& scenes) {
    std::vector<SceneDef> sceneDefs;
    for (const auto& scene : scenes) {
        SceneDef def;
        def.id = scene.getId();
        def.dialogNodeId = scene.getDialogNodeId();
        def.type = scene.getType();
        def.text = scene.getText();
        sceneDefs.push_back(def);
    }
    return sceneDefs;
}
void SceneRegistry::setScenes(const std::vector<SceneDef>& defs){
    scenes = defs;
}