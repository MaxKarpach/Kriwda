#include "../headerFiles/DialogNode.h" 
#include <iostream>

const int MAX_STRING_LEN = 255;

DialogNode::DialogNode(const DialogNodeDef& def):id(def.id), name(def.name), text(def.text), choices(def.choices){}

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
        is.ignore();
    
        char buf1[MAX_STRING_LEN + 1] = {0};
        is.getline(buf1, MAX_STRING_LEN);
        dnd.name = buf1;
    
        char buf2[MAX_STRING_LEN + 1] = {0};
        is.getline(buf2, MAX_STRING_LEN);
        dnd.text = buf2;
    
        int choicesCount = 0;
        is >> choicesCount;
        for (int i = 0; i < choicesCount; i++) {
            int choiceId = 0;
            is >> choiceId;
            dnd.choices.push_back(choiceId);
        }
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
    }
}