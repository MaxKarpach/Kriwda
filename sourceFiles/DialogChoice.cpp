#include "../headerFiles/DialogChoice.h" 
#include <iostream>

const int MAX_STRING_LEN = 255;

DialogChoice::DialogChoice(const int &id,  const std::string &text, const int& nextNodeId, 
    const int &nodeId):id(id), text(text), nextNodeId(nextNodeId), nodeId(nodeId){}

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