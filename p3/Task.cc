#include<iostream>
using namespace std;

#include "ToDo.h"
#include "Project.h"
#include "List.h"
#include "Task.h"

Task::Task(string name){
    //completar
}

string Task::getName() const{
    //completar
}

Date Task::getDeadline() const{
    //completar
} 

bool Task::getIsDone() const{
    //completar
}

int Task::getTime() const{
    //completar
}

void Task::setName(){
    //completar
}

bool Task::setDeadline(string deadline){
    //completar
}

bool Task::setTime(int time){
    //completar
}

void Task::toggle(){
    //completar
}

ostream& operator<<(ostream &os,const Task &task){
    //completar
}