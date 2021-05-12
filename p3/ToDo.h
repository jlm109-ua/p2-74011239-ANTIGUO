#include<iostream>
using namespace std;

#include "Project.h"
#include "Util.h"

class ToDo{
    friend void operator<<(ostream &,const ToDo &); //???
    protected:
        int nextId=1;
        string name;
    public:
        ToDo(string name);
        string getName() const;
        int getPosProject(string name) const;
        int getPosProject(int id) const;
        bool setName(string name);
        void addProject(Project *project); //?
        void deleteProject(int id=0);
        void setProjectDescription(string name,string description);
        void projectMenu(int id=0);
};