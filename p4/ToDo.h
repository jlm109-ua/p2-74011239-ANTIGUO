// DNI 74011239E LLINARES MAURI, JUAN
#ifndef __TODO_H__
#define __TODO_H__

#include<iostream>
#include<vector>
using namespace std;

#include "Project.h"
#include "Util.h"

struct BinToDo{
  char name[KMAXNAME];
  unsigned numProjects;
};

class ToDo{
    friend ostream& operator<<(ostream &o,const ToDo &program);
    protected:
        static int nextId;
        string name;
        int getPosProject(string name) const;
        int getPosProject(int id) const;
        vector<Project*> projects;
        void emptyProgram();
        bool checkId(vector<Project *> projects,int id) const;
        void exportOneProject(vector<Project *> projects,string filename,int id) const;
    public:
        ToDo(string name);
        string getName() const;
        bool setName(string name);
        void addProject(Project *project);
        void deleteProject(int id=0);
        void setProjectDescription(string name,string description);
        void projectMenu(int id=0);
        bool loadData(vector<Project*> &lp,string filename="");
        void saveData(string filename="") const;
        bool importProjects(vector<Project*> &lp,string filename="");
        void exportProjects(string filename="",int id=-1) const;
};

#endif