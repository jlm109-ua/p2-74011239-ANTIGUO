#include "List.h"

List::List(string name){
    if(Util::checkEmpty(name)){
        throw ERR_EMPTY;
    }else{
        this->name=name;
    }
}

string List::getName() const{
    return name;
}

vector<Task> List::getTask() const{
    //???
}

unsigned List::getNumTasks() const{
    int n;
    n=tasks.size();
    return(n);
}

unsigned List::getNumDone() const{
    //???
    return(1);
}

int List::getTimeTasks() const{
    //???
    return(1);
}

int List::getTimeDone() const{
    //???
    return(1);
}

int List::getPosTask(string name) const{
    //???
}

bool List::setName(string name){
    if(Util::checkEmpty(name)){
        Util::error(ERR_EMPTY);
        return(false);
    }else{
        this->name=name;
        return(true);
    }
}

void List::addTask(const Task &task){
    //???
}

bool List::deleteTask(string name){
    //???
    return(false);
}

bool List::toggleTask(string name){
    //???
    return(false);
}

ostream& operator<<(ostream &os,const List &list){
    os<<list.getName()<<endl;
    for(unsigned int i=0;i<list.getNumTasks();i++){        
        os<<"[";
        if(list.tasks[i].getIsDone()){
            os<<"X";
        }else{
            os<<" ";
        }
        os<<"] ";
        os<<"("<<list.tasks[i].getTime()<<") "<<printDeadline(list.tasks[i].getDeadline())<<" : "<<list.tasks[i].getName<<endl;
    }
    return os;
}

void printDeadline(Date deadline){
    int day,month,year;
    //passar Date a string
    Util::saveDate(deadline,day,month,year);
    cout<<year<<"-"<<month<<"-"<<day;
}