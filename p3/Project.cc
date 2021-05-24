#include "Project.h"

bool checkList(string s);

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
    int pos;
    for(unsigned int i=0;i<lists.size();i++){
         if(name==lists[i].getName()){
             pos=i;
             return(pos);
         }
    }
    return(-1);
}

bool Project::setId(int id){
    if(id<0){
        Util::error(ERR_ID);
        return(false);
    }else{
        this->id=id;
        return(true);
    }
}

bool Project::setName(string name){
    if(Util::checkEmpty(name)){
        Util::error(ERR_EMPTY);
        return(false);
    }else{
        this->name=name;
        return(true);
    }
}

void Project::setDescription(string description){
    this->description=description;
}

void Project::edit(string name,string description){
    string s;
    
    do{
        Util::E_PN(); getline(cin,name);
    }while(Util::checkEmpty(name));

    Util::E_PD(); getline(cin,description);

    this->name=name;
    this->description=description;
}

void Project::addList(string name){
    try{
        do{
        Util::E_TN; getline(cin,name);
        }while(checkList(name));
        List list(name);
        lists.push_back(list);
    }catch(Error e){
        Util::error(e);
    }
}

void Project::deleteList(string name){
    int pos;

    do{
        Util::E_LN(); getline(cin,name);
    }while(Util::checkEmpty(name));

    if(getPosList(name)==-1){
        Util::error(ERR_LIST_NAME);
    }else{
        pos=getPosList(name);
        lists.erase(lists.begin()+pos);
    }
}

void Project::addTaskToList(string name){
    string deadline;
    int time,pos;
    //FER LA COMPROBACIÓ DE QUE NO ESTÀ REPETIDA LA LLISTA
    do{
        Util::E_LN(); getline(cin,name);
    }while(Util::checkEmpty(name));

    Util::E_TN(); getline(cin,name);
    Util::E_D(); getline(cin,deadline);
    Util::E_ET(); cin>>time;
    
    Task task(name);
    task.setDeadline(deadline);
    task.setTime(time);
    //ACABAR
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

bool checkList(string s){
  bool val=false;

  for(unsigned int i=0;i<lists.size();i++){
    if(s==lists[i].name){  
      Util::error(ERR_LIST_NAME);  
      return(true);
    }
  }
return(false);
}