#include <iostream>
#ifndef DIALOGNODE_H
#define DIALOGNODE_H
struct DialogNodeDef{
    int id;
    std::string name;
    std::string text;
    std::vector<int> choices;
    std::string description;
};

class DialogNode {
    public:
        DialogNode(const DialogNodeDef& def);
        int getId() const { return id; }
        void setId(int value) { id = value; }

        std::string getText() const { return text; }
        void setText(std::string value) {text = value; }

        std::string getDescription() const { return description; }
        void setDescription(std::string value) {description = value; }
         
        std::string getName() const { return name; }
        void setName(std::string value) { name = value; }

        void addChoice(const int& choiceId) {
            choices.push_back(choiceId);
        }
        void showChoices(){
            for (int i = 0; i < choices.size(); i++){
                std::cout << choices[i] << std::endl;
            }
        }
        void removeChoice(int choiceId) {
            auto it = std::find(choices.begin(), choices.end(), choiceId);
            if (it != choices.end()) {
                choices.erase(it);
            } 
        }
        std::vector<int> getChoices() const { return choices; }
    private:
    int id;
    std::string name;
    std::string text;
    std::vector<int> choices;
    std::string description;
};


class DialogNodeRegistry{
    public:
    void load(std::istream& is);
    std::vector<DialogNodeDef> getDialogNodes();
    void save(std::ostream &os);
    std::vector<DialogNodeDef> toDialogNodeDefs(const std::vector<DialogNode> &dialogNodes);
    void setDialogNodes(const std::vector<DialogNodeDef> &defs);
private:
    std::vector<DialogNodeDef> dialogNodes;
};
#endif