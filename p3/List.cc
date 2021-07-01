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

vector<Task> List::getTasks() const{
    return(tasks);
}

unsigned List::getNumTasks() const{
    int n;
    vector<Task> tasks=getTasks();
    n=tasks.size();
    return(n);
}

unsigned List::getNumDone() const{
    int totdone=0;
    vector<Task> tasks=getTasks();

    for(unsigned int i=0;i<tasks.size();i++){
        if(tasks[i].getIsDone()){
            totdone+=1;
        }
    }
    return(totdone);
}

int List::getTimeTasks() const{
    int tottime=0;
    vector<Task> tasks=getTasks();

    for(unsigned int i=0;i<tasks.size();i++){
        tottime+=tasks[i].getTime();
    }
    return(tottime);
}

int List::getTimeDone() const{
    int tottimedone=0;
    vector<Task> tasks=getTasks();

    for(unsigned int i=0;i<tasks.size();i++){
        if(tasks[i].getIsDone()){
            tottimedone+=tasks[i].getTime();
        }
    }
    return(tottimedone);
}

int List::getPosTask(string name) const{
    vector<Task> tasks=getTasks();

    for(unsigned int i=0;i<tasks.size();i++){
        if(name==tasks[i].getName()){
            return (i);
        }
    }
    return (-1);
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
    tasks.push_back(task);
}

bool List::deleteTask(string name){
    bool val=false;

    for(unsigned int i=0;i<tasks.size();i++){
        if(name==tasks[i].getName()){
            tasks.erase(tasks.begin()+(i));
            val=true;
        }
    }
    if(val){
        return(true);
    }else{
        Util::error(ERR_TASK_NAME);
        return(false);
    }
}

bool List::toggleTask(string name){

    for(unsigned int i=0;i<tasks.size();i++){
        if(name==tasks[i].getName()){
            tasks[i].toggle();
        }
    }
    return(false);
}

ostream& operator<<(ostream &os,const List &list){
    os<<list.getName()<<endl;

    vector<Task> tasks=list.getTasks();
    for(unsigned int i=0;i<list.getNumTasks();i++){
        os<<tasks[i]<<endl;
    }
    return os;
}