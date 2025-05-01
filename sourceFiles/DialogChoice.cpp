#include "../headerFiles/DialogChoice.h" 
#include <iostream>

const int MAX_STRING_LEN = 255;

DialogChoice::DialogChoice(const DialogChoiceDef& def):id(def.id), text(def.text), nextNodeId(def.nextNodeId), nodeId(def.nodeId){}

DialogChoiceDef DialogChoiceRegistry::getDialogChoice(){
    return dialogChoice;
}

void DialogChoiceRegistry::load(std::istream& is){
    DialogChoiceDef dcd;
    is >> dcd.id;
    char buf[MAX_STRING_LEN + 1] = {0};
    is.getline(buf, MAX_STRING_LEN);
    memset(buf, 0, sizeof(buf));
    is.getline(buf, MAX_STRING_LEN);
    dcd.text = buf;
    is >> dcd.nextNodeId;
    is >> dcd.nodeId;
    dialogChoice = dcd;
}