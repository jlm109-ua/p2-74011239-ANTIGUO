// DNI 74011239E LLINARES MAURI, JUAN
#ifndef __TASK_H__
#define __TASK_H__

#include<iostream>
#include<vector>
using namespace std;

#include "Util.h"

struct Date{
  int day;
  int month;
  int year;
};

struct BinTask{
  char name[Util::KMAXNAME];
  Date deadline;
  bool isDone;
  int time;
};

class Task{
    friend ostream& operator<<(ostream &os,const Task &task);
    protected:
        string name;
        Date deadline;
        bool isDone;
        int time;
    public:
        Task(const BinTask &bt);
        Task(string name);
        string getName() const;
        Date getDeadline() const;
        bool getIsDone() const;
        int getTime() const;
        void setName(string name);
        bool setDeadline(string deadline);
        bool setTime(int time);
        void toggle();
        bool importTask(string task);
        string exportTask() const;
        BinTask toBinary() const;
        void saveData(ofstream &file) const;
};

#endif