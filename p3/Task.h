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

class Task{
    friend ostream& operator<<(ostream &os,const Task &task);
    protected:
        string name;
        Date deadline;
        bool isDone;
        int time;
        bool checkDate(string deadline);
    public:
        Task(string name);
        string getName() const;
        Date getDeadline() const;
        bool getIsDone() const;
        int getTime() const;
        void setName(string name);
        bool setDeadline(string deadline);
        bool setTime(int time);
        void toggle();
};

#endif