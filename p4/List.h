// DNI 74011239E LLINARES MAURI, JUAN
#ifndef __LIST_H__
#define __LIST_H__

#include<iostream>
#include<vector>
using namespace std;

#include "Util.h"
#include "Task.h"

struct BinList{
  char name[Util::KMAXNAME];
  unsigned numTasks;
};

class List{
    friend ostream& operator<<(ostream &o,const List &toDoTask);
    protected:
        string name;
        vector<Task> tasks;
    public:
        List(const BinList &bl);
        List(string name);
        string getName() const;
        vector<Task> getTasks() const;
        unsigned getNumTasks() const;
        unsigned getNumDone() const;
        int getTimeTasks() const;
        int getTimeDone() const;
        int getPosTask(string name) const;
        bool setName(string name);
        void addTask(const Task &task);
        bool deleteTask(string name);
        bool toggleTask(string name);
        string exportList() const;
        BinList toBinary() const;
        void saveData(ofstream &file) const;
};

#endif