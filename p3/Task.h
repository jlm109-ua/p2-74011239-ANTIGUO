#include<iostream>
using namespace std;

struct Date{
  int day;
  int month;
  int year;
};

class List{
    //afegir friend
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
        bool setDeadline(deadline string);
        bool setTime(int time);
        void toggle();
};