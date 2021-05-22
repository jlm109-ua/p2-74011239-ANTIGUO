#include "Task.h"

const int KMINMONTH=1;
const int KMAXMONTH=12;
const int KMAXFEB=29;
const int KMAXDAY2=30;
const int KMAXDAY=31;
const int KMINYEAR=2000;
const int KMAXYEAR=2100;
const int KMAXNAME=20;
const int KMAXDESC=40;

bool checkDate(string deadline);

Task::Task(string name){
    this->name=name;
    time=1;
    deadline.day=1;
    deadline.month=1;
    deadline.year=2000;
    isDone=false;
}

string Task::getName() const{
    return name;
}

Date Task::getDeadline() const{
    return deadline;
} 

bool Task::getIsDone() const{
    return isDone;
}

int Task::getTime() const{
    return time;
}

void Task::setName(string name){
    this->name=name;
}

bool Task::setDeadline(string deadline){
    int dday,dmonth,dyear;

    if(checkDate(deadline)){
        Util::error(ERR_DATE);
        return(false);
    }else{
        Util::saveDate(deadline,dday,dmonth,dyear);
        Task::deadline.day=dday;
        Task::deadline.month=dmonth;
        Task::deadline.year=dyear;
        return(true);
    }
}

bool Task::setTime(int time){
    if(time<1 || time>180){
        Util::error(ERR_TIME);
        return(false);
    }else{
        this->time=time;
        return(true);
    }
}

void Task::toggle(){
    if(isDone){
        isDone=false;
    }else{
        isDone=true;
    }
}

ostream& operator<<(ostream &os,const Task &task){

    os<<"[";
    if(task.isDone){
        os<<"X";
    }else{
        os<<" ";
    }
    os<<"] ";
    os<<"("<<time<<") "<<task.deadline.year<<"-"<<task.deadline.month<<"-"<<task.deadline.day<<" : "<<task.name<<endl;
    
    return os;
}

bool checkDate(string deadline){

    int day,month,year,x,y,z,s; //x,y,z son auxiliars per a comprovar dades
    bool val=false;

    Util::saveDate(deadline,day,month,year);
   
    x=year%100;
    y=year%400;
    z=year%4;

    if(year<KMINYEAR || year>KMAXYEAR){
        val=true;
    }

    if(month<KMINMONTH || month>KMAXMONTH){
        val=true;
    }

    if(day<KMINMONTH || day>KMAXDAY){
        val=true;
    }

    switch(month){
        case 2: 
        if(day>KMAXFEB){
            val=true;
        }
        if(day==KMAXFEB){
            if(z!=0){
            val=true;
            break;
            }
            if(x==0){
            if(y==0){
            }else{
                val=true;
            }  
            }else{
            val=true;
            }
        }
        break;
        case 4: 
        if(day>KMAXDAY2){
            val=true;
        }
        break;
        case 6: 
        if(day>KMAXDAY2){
            val=true;
        }
        break;
        case 9: 
        if(day>KMAXDAY2){
            val=true;
        }
        break;
        case 11:
        if(day>KMAXDAY2){
            val=true;
        }
        break;
    }
return(val);
}