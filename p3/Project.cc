#include<iostream>
using namespace std;

#include "ToDo.h"
#include "Project.h"
#include "List.h"
#include "Task.h"

Project::Project(string name,string description=""){
    //completar
}

int Project::getId() const{
    //completar
}

string Project::getName() const{
    //completar
}

string Project::getDescription() const{
    //completar
}

int Project::getPosList(string name) const{
    //completar
}

bool Project::setId(int id) const{
    //completar
}

void Project::setDescription(string description){
    //completar
}

void Project::edit(string name="",string description=""){
    //completar
}

void Project::addList(string name=""){
    //completar
}

void Project::deleteList(string name=""){
    //completar
}

void addTaskToList(string name=""){
    //completar
}

void Project::deleteTaskFromList(string name=""){
    //completar
}

void Project::toggleTaskFromList(string name=""){
    //completar
}

void Project::menu(){
    //completar
}

string Project::summary() const{
    //completar
}

ostream& operator<<(ostream &os,const Project &project){
    //completar
}