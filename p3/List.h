#include<iostream>
using namespace std;

#include "Task.h"

class List{
    friend void operator<<(ostream &,List &); //???    protected:
        string name;
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
        void addTask(const Task &task); //està bé???
        bool deleteTask(string name);
        bool toggleTask(string name);
};