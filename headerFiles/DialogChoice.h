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
        int getId() const { return id_; }
        void setId(int value) { id_ = value; }

        std::string getText() const { return text_; }
        void setText(std::string value) {text_ = value; }

        int getNextNodeId() const { return nextNodeId_; }
        void setNextNodeId(int value) { nextNodeId_= value; }

        bool getIsUsed() const { return isUsed_; }
        void setisUsed(bool value) { isUsed_ = value; }

    private:
    int id_;
    std::string text_;
    int nextNodeId_;
    bool isUsed_;
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