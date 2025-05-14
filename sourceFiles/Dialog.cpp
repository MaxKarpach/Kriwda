#include "../headerFiles/Dialog.h" 
#include <iostream>

Dialog::Dialog(const DialogDef& def)
:id(def.id), currentNodeId(def.currentNodeId){}

std::vector<DialogDef> DialogRegistry::getDialogs(){
    return dialogs;
}

void Dialog::start(int& startNode) {
    currentNodeId = startNode;
}

void DialogRegistry::load(std::istream& is){
    int dialogsCount = 0;
    is >> dialogsCount;
    for (int i = 0; i < dialogsCount; i++){
        DialogDef dd;
    is >> dd.id;
    is >> dd.currentNodeId;
    dialogs.push_back(dd);
    }
}
void DialogRegistry::save(std::ostream& os){
    os << dialogs.size() << std::endl;
    for (const DialogDef& dd : dialogs) {
        os << dd.id << std::endl;
        os << dd.currentNodeId << std::endl;
    }
}