// DNI: 74011239E Nom: Juan Llinares Mauri

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string.h>

using namespace std;

struct Date{
  int day;
  int month;
  int year;
};

struct Task{
  string name;
  Date deadline;
  bool isDone;
  int time;
};

struct List{
  string name;
  vector<Task> tasks;
};

struct Project{
  int id;
  string name;
  string description;
  vector<List> lists;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME
};

void error(Error e){
  switch(e){
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_EMPTY:
      cout << "ERROR: empty string" << endl;
      break;
    case ERR_LIST_NAME:
      cout << "ERROR: wrong list name" << endl;
      break;
    case ERR_TASK_NAME:
      cout << "ERROR: wrong task name" << endl;
      break;
    case ERR_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_TIME:
      cout << "ERROR: wrong expected time" << endl;
  }
}

void showMainMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl 
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}

bool checkEmpty(List temp){ //Comprova si el .name dels tipus List està buit
bool val=false;//validació
  if(temp.name.length()==0){
    error(ERR_EMPTY);
    val=true;
  }
return(val);
}

bool checkList(List temp,Project toDoList,int &pos){ //Comprova si hi ha alguna llista amb el mateix nom i la posició en la que es troba
  bool val;
  pos=0;
  for(unsigned int i=0;i<toDoList.lists.size();i++){
    val=false;
    if(temp.name==toDoList.lists[i].name){  
      pos=i;  
      i=toDoList.lists.size();
      val=true;
    }
  }
return(val);
}

bool findList(List &temp,Project toDoList,int &pos){

  do{
  cout<<"Enter list name:"; getline(cin,temp.name); 
  }while(checkEmpty(temp));

  if(checkList(temp,toDoList,pos)){
  }else{
    return(false);
  }
return(true);
}


bool findTask(List temp,Task ttemp,int &pos){

  for(unsigned int i=0;i<temp.tasks.size();i++){
    if(temp.name==ttemp.name[i]){
      pos=i;
      i=temp.tasks.size();
      return(true);
    }
  }
return(false);
}

bool checkDate(Date dtemp){

  if(dtemp.year<2000 || dtemp.year>2100){
    return(true);
  }

  if(dtemp.month<1 || dtemp.month>12){
    return(true);
  }

  if(dtemp.day<1 || dtemp.day>31){
    return(true);
  }

  switch(dtemp.month){
    case 2: 
      if(dtemp.day>29){
        return(false);
      }
      if(dtemp.day==29){
        if(dtemp.year%100==0){
          if(dtemp.year%400==0){
            break;
          }else{
            return(false);
          }  
        }else{
          return(false);
        }
        if(dtemp.year%4!=0){
          return(false);
        }
      }
      break;
    case 4: 
      if(dtemp.day>30){
        return(false);
      }
      break;
    case 6: 
      if(dtemp.day>30){
        return(false);
      }
      break;
    case 9: 
      if(dtemp.day>30){
        return(false);
      }
      break;
    case 11:
      if(dtemp.day>30){
        return(false);
      }
      break;
  }


return(false);
}

void editProject(Project &toDoList){
  
  bool val=false;

  do{
    cout<<"Enter project name:"; getline(cin,toDoList.name);
    if(toDoList.name.length()==0){
      error(ERR_EMPTY);
      val=true;
    }
  }while(val);

  cout<<"Enter project description:"; getline(cin,toDoList.description);
}

void addList(Project &toDoList){
  
  List temp;
  bool val;

  do{
    val=false;
    cout<<"Enter list name:"; getline(cin,temp.name);
    if(temp.name.length()==0){
      error(ERR_EMPTY);
      val=true;
    }
  }while(val);
  
  for(unsigned int i=0;i<toDoList.lists.size();i++){
    if(temp.name==toDoList.lists[i].name){ 
      i=toDoList.lists.size();
      error(ERR_LIST_NAME);
    }else{
      toDoList.lists.push_back(temp);
    }
  }
}

void deleteList(Project &toDoList){

  List temp;
  int pos;
  
  if(findList(temp,toDoList,pos)){
    toDoList.lists.erase(toDoList.lists.begin()+pos);
  }else{
    error(ERR_LIST_NAME);
  } //borrar element de toDoList.lists //NO RECONOCE LA LISTA
}

void addTask(Project &toDoList){ //per acabar
  Date dtemp;
  Task ttemp;
  List temp;
  int pos,i;
  string sd,sm,sy //string day, string month i string year

  if(findList(temp,toDoList,pos)){
    cout<<"Enter task name: "; getline(cin,ttemp.name);
    cout<<"Enter deadline: ";
      getline(cin,sd,'/');  dtemp.day=stoi(sd);
      getline(cin,sm,'/');  dtemp.month=stoi(sm);
      getline(cin,sy,'\n'); dtemp.year=stoi(sy);
    if(checkDate(dtemp)){
      error(ERR_DATE);
    }else{
      temp.tasks.push_back(ttemp.name);
      ttemp.isDone=false;
      i=temp.tasks.size();
      ttemp.deadline.push_back(dtemp); //com guarde la deadline?? //és correcte??????
    }
  }else{
    error(ERR_LIST_NAME);
  }
}

void deleteTask(Project &toDoList){ //per acabar
  Task ttemp;
  List temp;
  int pos;

  if(findList(temp,toDoList,pos)){
    if(findTask(temp,ttemp,pos)){
      temp.tasks.erase(temp.tasks.begin()+pos);
    }else{
      error(ERR_TASK_NAME);
    }
  }else{
    error(ERR_LIST_NAME);
  }
}

void toggleTask(Project &toDoList){ //NO SÉ SI ESTÀ BÉ, PREGUNTAR
List temp;
Task ttemp;
int pos;

  if(findList(temp,toDoList,pos)){
    if(findTask(temp,ttemp,pos){
      if(ttemp.isDone[pos]==false){
        ttemp.isDone[pos]==true;
      }else{
        ttemp.isDone[pos]==false
      }
    }else{
      error(ERR_TASK_NAME);
    }
  }

}

void report(const Project &toDoList){ //PER ACABAR
  List temp;
  Task ttemp;

  cout<<"Name: "<<toDoList.name;
  cout<<"Description: "<<toDoList.description;
}

int main(){
  Project toDoList;
  toDoList.id=1;
  char option;
  
  do{
    showMainMenu();
    cin >> option;
    cin.get();
    
    switch(option){
      case '1': editProject(toDoList);
                break;
      case '2': addList(toDoList);
                break;
      case '3': deleteList(toDoList);
                break;
      case '4': addTask(toDoList);
                break;
      case '5': deleteTask(toDoList);
                break;
      case '6': toggleTask(toDoList);
                break;
      case '7': report(toDoList);
                break;
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');
  
  return 0;    
}
