#include "ToDo.h"

ToDo::ToDo(string name){
    
}

string ToDo::getName() const{
    return(ToDo::name);
}

int ToDo::getPosProject(string name) const{
    //completar
}

int ToDo::getPosProject(int id) const{
    //completar
}

bool ToDo::setName(string name){
    //completar
}

void ToDo::addProject(Project *project){
    //completar
}

void ToDo::deleteProject(int id=0){
    //completar
}

void ToDo::setProjectDescription(name,description){
    //completar
}

void ToDo::projectMenu(int id=0){
    
}

ostream& operator<<(ostream &os,const ToDo &toDo){
    //completar
}