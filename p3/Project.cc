#include "Project.h"

Project::Project(string name,string description=""){
    if(checkEmpty(name)){
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
}

bool Project::setId(int id) const{
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

void Project::edit(string name="",string description=""){
    //completar
}

void Project::addList(string name=""){
    try{
        List::List(name);//???
    }catch(Error e){
        Util::error(e);
    }
}

void Project::deleteList(string name=""){
    //???
}

void addTaskToList(string name=""){
    //???
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

bool checkEmpty(string s){
  bool val=false; 
  string v=s;
    if(s.length()==0){
      val=true;
    }else{
      for(unsigned int i=0;i<s.length();i++){
        v[i]=' ';
      }
      if(v==s){
          val=true;
      }
    }
  return(val);
}