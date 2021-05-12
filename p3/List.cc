#include "List.h"

List::List(string name){
    //completar
}

string List::getName() const[
    //completar
]

vector<Task> List::getTask() const{
    //completar
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
    //completar
}