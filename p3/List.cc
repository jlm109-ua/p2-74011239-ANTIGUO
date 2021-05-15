#include "List.h"

List::List(string name){
    //s'ha de llançar una excepció
    if(checkEmpty(name)){
        Util::error(ERR_EMPTY);
    }else{
        this->name=name;
    }
}

string List::getName() const[
    return name;
]

vector<Task> List::getTask() const{
    
}

unsigned List::getNumTasks() const{
    //completar
}

unsigned List::getNumDone() const{
    //completar
}

int List::getTimeTasks() const{
    //completar
}

int List::getTimeDone() const{
    //completar
}

int List::getPosTask(string name) const{
    //completar
}

bool List::setName(string name){
    //completar
}

void List::addTask(const Task &task){
    //completar
}

bool List::deleteTask(string name){
    //completar
}

bool List::toggleTask(string name){
    //completar
}

ostream& operator<<(ostream &os,const List &list){
    
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