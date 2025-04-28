#include <iostream>
#ifndef DIALOGNODE_H
#define DIALOGNODE_H
struct DialogNodeDef{
    int id;
    std::string name;
    std::string text;
    std::vector<int> choices;
    int dialogId;
};

class DialogNode {
    public:
        DialogNode(const int &id, const std::string &name, const std::string &text, const std::vector<int> &choices,
             const int &dialogId);
        int getId() const { return id; }
        void setId(int value) { id = value; }

        std::string getText() const { return text; }
        void setText(std::string value) {text = value; }
         
        std::string getName() const { return name; }
        void setName(std::string value) { name = value; }

        int getDialogId() const { return dialogId; }
        void setDialogId(int value) { dialogId= value; }

        void addChoice(const int& choiceId) {
            choices.push_back(choiceId);
        }
    private:
    int id;
    std::string name;
    std::string text;
    std::vector<int> choices;
    int dialogId;
};


class DialogNodeRegistry{
    public:
    void load(std::istream& is);
    DialogNodeDef getDialogNode();
private:
DialogNodeDef dialogNode;
};
#endif