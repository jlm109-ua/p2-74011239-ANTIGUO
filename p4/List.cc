// DNI 74011239E LLINARES MAURI, JUAN
#include "List.h"

List::List(const BinList &bl){
    this->name=bl.name;
}

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
    int pos;
    vector<Task> tasks=getTasks();

    for(unsigned int i=0;i<tasks.size();i++){
        if(name==tasks[i].getName()){
            pos=i;
            return (pos);
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
    bool found=false;
    int pos;
    vector<Task> tasks=getTasks();

    for(unsigned int i=0;i<tasks.size();i++){
        if(name==tasks[i].getName()){
            pos=i;
            tasks.erase(tasks.begin()+pos);
            found=true;
            return(true);
        }
    }
    if(!found){
        Util::error(ERR_TASK_NAME);
        return(false);
    }
}

bool List::toggleTask(string name){
    vector<Task> tasks=getTasks();

    for(unsigned int i=0;i<tasks.size();i++){
        if(name==tasks[i].getName()){
            tasks[i].toggle();
        }
    }
    return(false);
}

string List::exportList() const{
    string el;
    BinList bl=toBinary();
    vector<Task> tasks=getTasks();

    // funciona el "\n" en una string?
    // he de demanar una BinList per a poder fer la cadena? (fer "BinList=toBinary()")

    el=el+'@'+bl.name; //????

    for(unsigned int i=0;/*és posible llevar el int quan és unsigned?*/i<bl.numTasks;i++){
        BinTask bt=tasks[i].exportTask();
        el=el+'\n'+bt;
    }
}

BinList List::toBinary() const{
    vector<Task> tasks=getTasks();
    string namel=getName();
    BinList bl;

    if(namel.size>Util::KMAXNAME){
        // ???
    }else{

    }

    // bl.name
    bl.numTasks=getNumTasks();
}

void List::saveData(ofstream &file) const{
    // completar
}



ostream& operator<<(ostream &os,const List &list){
    string s;
    
    os<<list.getName()<<endl;

    vector<Task> tasks=list.getTasks();
    for(unsigned int i=0;i<list.getNumTasks();i++){
        os<<tasks[i];
    }
    return os;
}