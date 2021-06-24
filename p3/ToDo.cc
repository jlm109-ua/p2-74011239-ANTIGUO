#include "ToDo.h"

int ToDo::nextId=1;

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
    for(unsigned int i=0;i<projects.size();i++){
        if(name==projects[i]->getName()){
            return(i);
        }
    }
    return(-1);
}

int ToDo::getPosProject(int id) const{
    for(unsigned int i=0;i<projects.size();i++){
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
        throw(ERR_PROJECT_NAME);
    }else{
        project->setId(ToDo::nextId);
        ToDo::nextId++;
        projects.push_back(project);
    }
}

void ToDo::deleteProject(int id){
    if(id==0){
        Util::E_ID(); cin>>id;
        if(getPosProject(id)>=0){
            projects.erase(projects.begin()+getPosProject(id));
        }else{
            Util::error(ERR_ID);
        }
    }
}

void ToDo::setProjectDescription(string name,string description){
    if(getPosProject(name)>=0){
        projects[getPosProject(name)]->setDescription(description);
    }else{
        Util::error(ERR_ID);
    }
}

void ToDo::projectMenu(int id){
    do{
        Util::E_ID(); cin>>id;
    }while(id<=0);

    if(getPosProject(id)>=0){
        projects[id]->menu();
    }else{
        Util::error(ERR_ID);
    }
}

ostream& operator<<(ostream &os,const ToDo &toDo){
    for(unsigned int i=0;i<toDo.projects.size();i++){    
        os<<toDo.projects[i]->summary()<<endl;
    }
    return os;
}