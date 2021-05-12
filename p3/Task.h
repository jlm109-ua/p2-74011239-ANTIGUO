#include<iostream>
using namespace std;

#include "Util.h"

struct Date{
  int day;
  int month;
  int year;
};

class Task{
    friend void operator<<(ostream &,Task &); //???
    protected:
        string name;
        Date deadline;
        bool isDone;
        int time;
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