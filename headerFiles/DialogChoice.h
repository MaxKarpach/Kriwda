#include <iostream>
#ifndef DIALOGCHOICE_H
#define DIALOGCHOICE_H
struct DialogChoiceDef{
    int id;
    std::string text;
    int nextNodeId;
    int nodeId;
};

class DialogChoice {
    public:
        DialogChoice(const int &id, const std::string &text, const int &nextNodeId,const int &nodeId);
        int getId() const { return id; }
        void setId(int value) { id = value; }

        std::string getText() const { return text; }
        void setText(std::string value) {text = value; }

        int getNextNodeId() const { return nextNodeId; }
        void setNextNodeId(int value) { nextNodeId= value; }

        int getNodeId() const { return nodeId; }
        void setNodeId(int value) { nodeId= value; }
    private:
    int id;
    std::string text;
    int nextNodeId;
    int nodeId;
};


class DialogChoiceRegistry{
    public:
    void load(std::istream& is);
    DialogChoiceDef getDialogChoice();
private:
DialogChoiceDef dialogChoice;
};
#endif