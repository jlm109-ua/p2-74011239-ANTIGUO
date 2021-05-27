#ifndef __PROJECT_H__
#define __PROJECT_H__

#include<iostream>
#include<vector>
#include<sstream>
using namespace std;

#include "List.h"
#include "Util.h"

class Project{
    friend ostream& operator<<(ostream &o,const Project &toDoList);
    protected:
        int id;
        string name;
        string description;
        int getPosList(string name) const;
        vector<List> lists;
    public:
        Project(string name,string description="");
        int getId() const;
        string getName() const;
        string getDescription() const;
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
};

#endif