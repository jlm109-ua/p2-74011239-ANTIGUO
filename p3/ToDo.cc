#include<iostream>
using namespace std;

#include "ToDo.h"
#include "Project.h"
#include "List.h"
#include "Task.h"

ToDo::ToDo(string name){
    //completar
}

string ToDo::getName() const{
    //completar
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
    //completar
}

ostream& operator<<(ostream &os,const ToDo &toDo){
    //completar
}