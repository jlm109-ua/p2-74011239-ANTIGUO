#include "Project.h"

Project::Project(string name,string description){
    if(Util::checkEmpty(name)){
        Util::error(ERR_EMPTY);
    }else{
        this->name=name;
        this->description=description;
        id=0;
    }
}

int Project::getId() const{
    return id;
}

string Project::getName() const{
    return name;
}

string Project::getDescription() const{
    return description;
}

int Project::getPosList(string name) const{
    //completar
    return(1);
}

bool Project::setId(int id){
    if(id<0){
        Util::error(ERR_ID);
        return(false);
    }else{
        return(true);
    }
}

void Project::setDescription(string description){
    this->description=description;
}

void Project::edit(string name,string description){
    //completar
}

void Project::addList(string name){
    try{
        List list(name);
        lists.push_back(list);
    }catch(Error e){
        Util::error(e);
    }
}

void Project::deleteList(string name){
    //???
}

void addTaskToList(string name){
    //???
}

void Project::deleteTaskFromList(string name){
    //completar
}

void Project::toggleTaskFromList(string name){
    //completar
}

void Project::menu(){
    //completar
}

string Project::summary() const{
    string a;
    //completar
    return (a);
}

ostream& operator<<(ostream &os,const Project &project){
    //completar
    return os;
}