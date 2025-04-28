#include "../headerFiles/Dialog.h" 
#include <iostream>

Dialog::Dialog(const int &id,const int& currentNodeId)
:id(id), currentNodeId(currentNodeId){}

DialogDef DialogRegistry::getDialog(){
    return dialog;
}

void Dialog::start(int& startNode) {
    currentNodeId = startNode;
}

void DialogRegistry::load(std::istream& is){
    DialogDef dd;
    is >> dd.id;
    is >> dd.currentNodeId;
    dialog = dd;
}