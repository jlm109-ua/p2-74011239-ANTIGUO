#include "ToDo.h"

ToDo::ToDo(string name){
    
}

string ToDo::getName() const{
    return name;
}

int ToDo::getPosProject(string name) const{
    //completar
    return(1);
}

int ToDo::getPosProject(int id) const{
    //completar
    return(1);
}

bool ToDo::setName(string name){
    //completar
    return(false);
}

void ToDo::addProject(Project *project){
    //completar
}

void ToDo::deleteProject(int id){
    //completar
}

void ToDo::setProjectDescription(string name,string description){
    //completar
}

void ToDo::projectMenu(int id){
    
}

ostream& operator<<(ostream &os,const ToDo &toDo){
    //completar
    return os;
}