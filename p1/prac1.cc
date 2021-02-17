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

int checkEmpty(string s){ //Comprova si la string està buida
int val=0;//validació
  if(s.length()==0){
    error(ERR_EMPTY);
    val=1;
  }
return(val);
}

int checkList(string s,Project toDoList){ //Comprova si hi ha alguna llista amb el mateix nom
  int val=0;
  for(unsigned int i=0;i<toDoList.lists.size();i++){
    if(strcmp(s,toDoList.lists[i])==0){    
     error(ERR_LIST_NAME);
     i=toDoList.lists.size();
     val=1;
    }
  }
return(val);
}

void editProject(Project &toDoList){
  do{
  cout<<"Enter project name:"; getline(cin,toDoList.name);
  }while(checkEmpty(toDoList.name)==1);

  cout<<"Enter project description:"; getline(cin,toDoList.description);
}

void addList(Project &toDoList){
  string temp_name;
  do{
    do{
      cout<<"Enter list name:"; getline(cin,temp_name);
    }while(checkEmtpy(temp_name)==1); //Els valors 1 signifiquen que es produeix un error en la inserció del nom
  }while(checkList(temp_name,toDoList)==1);
  //afegir el nom al final de lists augmentant el tamany de lists
}

void deleteList(Project &toDoList){
  //borrar element de toDoList
}

void addTask(Project &toDoList){
}

void deleteTask(Project &toDoList){
}

void toggleTask(Project &toDoList){
}

void report(const Project &toDoList){
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
