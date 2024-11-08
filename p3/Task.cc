#include "Task.h"

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
    if(getIsDone()){
        this->isDone=false;
    }else{
        this->isDone=true;
    }
}

ostream& operator<<(ostream &os,const Task &task){
    Date dd=task.getDeadline();

    os<<"[";
    if(task.getIsDone()){
        os<<"X";
    }else{
        os<<" ";
    }
    os<<"] ";
    os<<"("<<task.getTime()<<") "<<dd.year<<"-"<<dd.month<<"-"<<dd.day<<" : "<<task.getName();
    
    return os;
}

bool Task::checkDate(string deadline){
    int day,month,year;
    float x,y,z;

    Util::saveDate(deadline,day,month,year);
   
    x=year%100;
    y=year%400;
    z=year%4;

    if(year<Util::KMINYEAR() || year>Util::KMAXYEAR()){
        return(true);
    }

    if(month<Util::KMINMONTH() || month>Util::KMAXMONTH()){
        return(true);
    }

    if(day<Util::KMINMONTH() || day>Util::KMAXDAY()){
        return(true);
    }

    switch(month){
        case 2: 
            if(day>Util::KMAXFEB()){
                return(true);
            }
            if(day==Util::KMAXFEB()){
                if(z!=0){
                    return(true);
                    break;
                }
                if(x==0){
                    if(y!=0){
                        return(true);
                    }
                }
            }
            break;
        case 4: 
            if(day>Util::KMAXDAY2()){
                return(true);
            }
            break;
        case 6: 
            if(day>Util::KMAXDAY2()){
                return(true);
            }
            break;
        case 9: 
            if(day>Util::KMAXDAY2()){
                return(true);
            }
            break;
        case 11:
            if(day>Util::KMAXDAY2()){
                return(true);
            }
            break;
    }
    return(false);
}