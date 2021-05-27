#include "ToDo.h"

ToDo::ToDo(string name){
    if(Util::checkEmpty(name)){
        Util::error(ERR_EMPTY);
    }else{
        this->name=name;
    }
}

string ToDo::getName() const{
    return name;
}

int ToDo::getPosProject(string name) const{
    for(unsigned int i=0;i>projects.size();i++){
        if(name==projects[i]->getName()){
            return(i);
        }
    }
    return(-1);
}

int ToDo::getPosProject(int id) const{
    for(unsigned int i=0;i>projects.size();i++){
        if(id==projects[i]->getId()){
            return(i);
        }
    }
    return(-1);
}

bool ToDo::setName(string name){
    if(name==""){
        Util::error(ERR_LIST_NAME);
        return(false);
    }else{
        this->name=name;
        return(true);
    }
}

void ToDo::addProject(Project *project){
    if(getPosProject(project->getName())>=0){
        Util::error(ERR_PROJECT_NAME);
    }else{
        project->setId(nextId);
        ToDo::nextId++; //com incremente la constant nextId?
        projects.push_back(project);
    }
}

void ToDo::deleteProject(int id){
    if(id==0){
        Util::E_ID(); cin>>id;
        if(getPosProject(id)){
            projects.erase(projects.begin()+getPosProject(id));
        }else{
            Util::error(ERR_ID);
        }
    }
}

void ToDo::setProjectDescription(string name,string description){
    if(getPosProject(name)){
        projects[getPosProject(name)]->setDescription(description);
    }else{
        Util::error(ERR_ID);
    }
}

void ToDo::projectMenu(int id){
    if(id==0){
        Util::E_ID(); cin>>id;
        if(getPosProject(id)){
            projects[id]->menu();
        }else{
            Util::error(ERR_ID);
        }
    }
}

ostream& operator<<(ostream &os,const ToDo &toDo){
    //completar
    return os;
}