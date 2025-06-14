#include "../headerFiles/DialogNode.h" 
#include <iostream>

const int MAX_STRING_LEN = 255;

DialogNode::DialogNode(const DialogNodeDef& def):id_(def.id), name_(def.name), text_(def.text), choices_(def.choices), 
description_(def.description){}

std::vector<DialogNodeDef> DialogNodeRegistry::getDialogNodes(){
    return dialogNodes;
}

void DialogNodeRegistry::load(std::istream& is){
    int dialogNodesCount = 0;
    is >> dialogNodesCount;
    for (int i = 0; i < dialogNodesCount; i++)
    {
        DialogNodeDef dnd;
        is >> dnd.id;
        is.ignore(MAX_STRING_LEN, '\n');
        std::getline(is, dnd.name);
        std::getline(is, dnd.text);
    
        int choicesCount = 0;
        is >> choicesCount;
        for (int i = 0; i < choicesCount; i++) {
            int choiceId = 0;
            is >> choiceId;
            dnd.choices.push_back(choiceId);
        }
        is.ignore(MAX_STRING_LEN, '\n');
        std::getline(is, dnd.description);
        dialogNodes.push_back(dnd);
    }
}

void DialogNodeRegistry::save(std::ostream& os){
    os << dialogNodes.size() << std::endl;
    for (const DialogNodeDef& dnd : dialogNodes) {
        os << dnd.id << std::endl;
        os << dnd.name << std::endl;
        os << dnd.text << std::endl;
        os << dnd.choices.size() << std::endl;
        for (int i = 0; i < dnd.choices.size(); i++) {
            os << dnd.choices[i] << std::endl;
        }
        os << dnd.description << std::endl;
    }
}
std::vector<DialogNodeDef> DialogNodeRegistry::toDialogNodeDefs(const std::vector<DialogNode>& dialogNodes){
        std::vector<DialogNodeDef> dialogNodeDefs;
        
        for (const auto& dialogNode : dialogNodes) {
            DialogNodeDef def;
            def.id = dialogNode.getId();
            def.name = dialogNode.getName();
            def.text = dialogNode.getText();
            def.choices = dialogNode.getChoices();
            def.description = dialogNode.getDescription();
            dialogNodeDefs.push_back(def);
        }

        return dialogNodeDefs;
    }
void DialogNodeRegistry::setDialogNodes(const std::vector<DialogNodeDef>& defs) {
    dialogNodes = defs;
}