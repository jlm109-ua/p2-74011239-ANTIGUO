#ifndef __TODO_H__
#define __TODO_H__

#include<iostream>
#include<vector>
using namespace std;

#include "Project.h"
#include "Util.h"

class ToDo{
    friend ostream& operator<<(ostream &o,const ToDo &program);
    protected:
        static const int nextId=1;
        string name;
        int getPosProject(string name) const;
        int getPosProject(int id) const;
        vector<Project*> projects;
    public:
        ToDo(string name);
        string getName() const;
        bool setName(string name);
        void addProject(Project *project);
        void deleteProject(int id=0);
        void setProjectDescription(string name,string description);
        void projectMenu(int id=0);
};

#endif