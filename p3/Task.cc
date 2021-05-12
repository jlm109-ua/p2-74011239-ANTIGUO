#include "Task.h"

Task::Task(string name){
    this->name=name;
    time=1;
    deadline.day=1;
    deadline.month=1;
    deadline.year=2000;
    isDone=false;
}

string Task::getName() const{
    return(Task::name);
}

Date Task::getDeadline() const{
    return(Task::deadline);
} 

bool Task::getIsDone() const{
    return(Task::isDone);
}

int Task::getTime() const{
    return(Task::time);
}

void Task::setName(string name){
    this->name=name;
}

bool Task::setDeadline(string deadline){
    checkDate(deadline);
}

bool Task::setTime(int time){
    //completar
}

void Task::toggle(){
    //completar
}

ostream& operator<<(ostream &os,const Task &task){
    //completar
}

bool checkDate(string deadline){

    int day,month,year,x,y,z,s; //x,y,z son auxiliars per a comprovar dades
    bool val=false;
    string auxdeadline;

    s=deadline.find('/');
    if(found!=deadline::npos){
        day=deadline.substr(0,s);
    }
    auxdeadline=deadline.substr(s+1);
    s=deadline.find('/');
    if(found!=deadline::npos){
        month=auxdeadline.substr(0,s);
    }
    auxdeadline=auxdeadline.substr()

    //CONTINUAR AMB LA FECHA

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