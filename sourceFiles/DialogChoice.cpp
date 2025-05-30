#include "../headerFiles/DialogChoice.h" 
#include <iostream>

const int MAX_STRING_LEN = 255;

DialogChoice::DialogChoice(const DialogChoiceDef& def):id(def.id), text(def.text), nextNodeId(def.nextNodeId), nodeId(def.nodeId){}

std::vector<DialogChoiceDef> DialogChoiceRegistry::getDialogChoices(){
    return dialogChoices;
}

void DialogChoiceRegistry::load(std::istream& is){
    int dialogChoicesCount = 0;
    is >> dialogChoicesCount;
    for (int i = 0; i < dialogChoicesCount; i++){
    DialogChoiceDef dcd;
    is >> dcd.id;
    char buf[MAX_STRING_LEN + 1] = {0};
    is.getline(buf, MAX_STRING_LEN);
    memset(buf, 0, sizeof(buf));
    is.getline(buf, MAX_STRING_LEN);
    dcd.text = buf;
    is >> dcd.nextNodeId;
    is >> dcd.nodeId;
    dialogChoices.push_back(dcd);
    }
}

void DialogChoiceRegistry::save(std::ostream& os){
    os << dialogChoices.size() << std::endl;
    for (const DialogChoiceDef& dcd : dialogChoices) {
        os << dcd.id << std::endl;
        os << dcd.text << std::endl;
        os << dcd.nextNodeId << std::endl;
        os << dcd.nodeId << std::endl;
    }
}
std::vector<DialogChoiceDef> DialogChoiceRegistry::toDialogChoiceDefs(const std::vector<DialogChoice>& dialogChoices) {
        std::vector<DialogChoiceDef> dialogChoiceDefs;
        for (const auto& dialogChoice : dialogChoices) {
            DialogChoiceDef def;
            def.id = dialogChoice.getId();
            def.text = dialogChoice.getText();
            def.nextNodeId = dialogChoice.getNextNodeId();
            def.nodeId = dialogChoice.getNodeId();
            dialogChoiceDefs.push_back(def);
        }
        return dialogChoiceDefs;
}
void DialogChoiceRegistry::setDialogChoices(const std::vector<DialogChoiceDef>& defs) {
    dialogChoices = defs;
}