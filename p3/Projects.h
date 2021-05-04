#include<iostream>
using namespace std;

class Project{
    //afegir friend
    protected:
        int id;
        string name;
        string description;
    public:
        Project(string name,string description="");
        int getId() const;
        string getName() const;
        string getDescription() const;
        int getPosList(string name) const;
        bool setId(int id);
        bool setName(string name);
        void setDescription(string description);
        void edit(string name="",string description=""); //?
        void addList(string name="");
        void deleteList(string name="");
        void addTaskToList(string name="");
        void deleteTaskFromList(string name="");
        void toggleTaskFromList(string name="");
        void menu();
        string summary() const;
}