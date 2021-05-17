#ifndef __LIST_H__
#define __LIST_H__

#include<iostream>
#include<vector>
using namespace std;

#include "Util.h"
#include "Task.h"

class List{
    friend void operator<<(ostream &o,const List &toDoTask);
    protected:
        string name;
        vector<Task> toDoSingleTask;
    public:
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
};

#endif