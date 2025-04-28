#include <iostream>
#ifndef DIALOG_H
#define DIALOG_H
struct DialogDef{
    int id;
    int currentNodeId;
};

class Dialog{
public:
    Dialog(const int &id, const int &currentNodeId);

    int getId() const { return id; }
    void setId(int value) { id = value; }
    int getCurrentNodeId() const { return currentNodeId; }
    void setCurrentNodeId(int value) { currentNodeId = value; }
    void start(int& startNode);

private:
int id;
int currentNodeId;
};


class DialogRegistry{
    public:
    void load(std::istream& is);
    DialogDef getDialog();
private:
DialogDef dialog;
};
#endif