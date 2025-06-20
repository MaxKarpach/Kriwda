#include "Scene.h"

const int max_string_len = 255;

Scene::Scene(const SceneDef& def)
    : id_(def.id),
      dialog_node_id_(def.dialog_node_id),
      type_(def.type),
      text_(def.text) {}

std::vector<SceneDef> SceneRegistry::get_scenes() {
    return scenes_;
}

void SceneRegistry::load(std::istream& is) {
    int scenes_count = 0;
    is >> scenes_count;

    for (int i = 0; i < scenes_count; i++) {
        SceneDef sd;
        is >> sd.id;
        is >> sd.dialog_node_id;
        is >> sd.type;
        is.ignore(max_string_len, '\n');
        std::getline(is, sd.text);
        scenes_.push_back(sd);
    }
}

void SceneRegistry::save(std::ostream& os) {
    os << scenes_.size() << std::endl;

    for (const SceneDef& sd : scenes_) {
        os << sd.id << std::endl;
        os << sd.dialog_node_id << std::endl;
        os << sd.type << std::endl;
        os << sd.text << std::endl;
    }
}

std::vector<SceneDef> SceneRegistry::to_scene_defs(const std::vector<Scene>& scenes) {
    std::vector<SceneDef> scene_defs;

    for (const auto& scene : scenes) {
        SceneDef def;
        def.id = scene.get_id();
        def.dialog_node_id = scene.get_dialog_node_id();
        def.type = scene.get_type();
        def.text = scene.get_text();
        scene_defs.push_back(def);
    }

    return scene_defs;
}

void SceneRegistry::set_scenes(const std::vector<SceneDef>& defs) {
    scenes_ = defs;
}
