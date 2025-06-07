#include <iostream>
#ifndef DIALOGCHOICE_H
#define DIALOGCHOICE_H
struct DialogChoiceDef{
    int id;
    std::string text;
    int nextNodeId;
    bool isUsed;
};

class DialogChoice {
    public:
        DialogChoice(const DialogChoiceDef& def);
        int getId() const { return id; }
        void setId(int value) { id = value; }

        std::string getText() const { return text; }
        void setText(std::string value) {text = value; }

        int getNextNodeId() const { return nextNodeId; }
        void setNextNodeId(int value) { nextNodeId= value; }

        bool getIsUsed() const { return isUsed; }
        void setisUsed(bool value) { isUsed = value; }

    private:
    int id;
    std::string text;
    int nextNodeId;
    bool isUsed;
};

class DialogChoiceRegistry{
    public:
    void load(std::istream& is);
    std::vector<DialogChoiceDef> getDialogChoices();
    void save(std::ostream &os);
    std::vector<DialogChoiceDef> toDialogChoiceDefs(const std::vector<DialogChoice> &dialogChoices);
    void setDialogChoices(const std::vector<DialogChoiceDef> &defs);
private:
std::vector<DialogChoiceDef> dialogChoices;
};
#endif