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
    vector<Task> tasks;
    tasks=getTasks();
    n=tasks.size();
    return(n);
}

unsigned List::getNumDone() const{
    int totdone=0;
    
    for(unsigned int i=0;i<getNumTasks();i++){
        /*if(ací vull comprovar el isDone de la task però no sé com accedir a ella){ //??? Com accedisc a les tasques?
        //tasks[i]???
        //Task::getIsDone???

        }*/
    }
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
    return(1);
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
    //???
    return(false);
}

bool List::toggleTask(string name){
    //???
    return(false);
}

ostream& operator<<(ostream &os,const List &list){
    string s;
    Date deadline;
    
    os<<list.getName()<<endl;

    for(unsigned int i=0;i<list.getNumTasks();i++){  
        deadline=list.tasks[i].getDeadline();
        s.push_back(deadline.year);
        s.push_back('-');
        s.push_back(deadline.month);
        s.push_back('-');
        s.push_back(deadline.day);      
        os<<"[";
        if(list.tasks[i].getIsDone()){
            os<<"X";
        }else{
            os<<" ";
        }
        os<<"] ";
        os<<"("<<list.tasks[i].getTime()<<") "<<s<<" : "<<list.tasks[i].getName()<<endl;
    }
    return os;
}