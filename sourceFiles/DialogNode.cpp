#include "../headerFiles/DialogNode.h" 
#include <iostream>

const int MAX_STRING_LEN = 255;

DialogNode::DialogNode(const int &id, const std::string &name, const std::string &text, const std::vector<int> &choices, 
    const int &dialogId):id(id), name(name), text(text), choices(choices), dialogId(dialogId){}

DialogNodeDef DialogNodeRegistry::getDialogNode(){
    return dialogNode;
}

void DialogNodeRegistry::load(std::istream& is){
    DialogNodeDef dnd;
    is >> dnd.id;
    is.ignore(); // <-- ВАЖНО! Очистить '\n' после считывания числа

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

    is >> dnd.dialogId;
    dialogNode = dnd;
}