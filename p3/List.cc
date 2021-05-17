#include "List.h"

List::List(string name){
    if(checkEmpty(name)){
        throw ERR_EMPTY;
    }else{
        this->name=name; //fer-ho així o amb setName()???
    }
}

string List::getName() const[
    return name;
]

vector<Task> List::getTask() const{
    //???
}

unsigned List::getNumTasks() const{
    //???
}

unsigned List::getNumDone() const{
    //???
}

int List::getTimeTasks() const{
    //???
}

int List::getTimeDone() const{
    //???
}

int List::getPosTask(string name) const{
    //???
}

bool List::setName(string name){
    if(checkEmpty(name)){
        Util::error(ERR_EMPTY);
        return(false);
    }else{
        this->name=name;
        return(true);
    }
}

void List::addTask(const Task &task){
    //???
}

bool List::deleteTask(string name){
    //???
}

bool List::toggleTask(string name){
    //???
}

ostream& operator<<(ostream &os,const List &list){
    os<<name<<endl;
    //fer un bucle per a que imprimisca el nombre de tasques?
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