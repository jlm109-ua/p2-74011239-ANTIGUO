// DNI: 74011239E Nom: Juan Llinares Mauri

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string.h>

using namespace std;

const int n1=1;
const int n4=4;
const int n12=12;
const int n29=29;
const int n30=30;
const int n31=31;
const int n100=100;
const int n400=400;
const int n2000=2000;
const int n2100=2100;

const string E_PN="Enter project name: ";
const string E_PD="Enter project description: ";
const string E_LN="Enter list name: ";
const string E_TN="Enter task name: ";
const string E_D="Enter deadline: ";
const string E_ET="Enter expected time: ";
const string N="Name: ";
const string D="Description: ";
const string TL="Total left: ";
const string TD="Total done: ";
const string MIN="minutes ";
const string HP="Highest priority: ";

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

bool checkEmpty(string s){ //Comprova si la string està buida o plena d'espais
bool val=false; 
string v=s; //string del mateix tamany que s per a comprovar que no s'introduisquen solament espais al nom
  if(s.length()==0){
    error(ERR_EMPTY);
    val=true;
  }
  for(unsigned int i=0;i<s.length();i++){
    v[i]=' ';
  }
  if(v==s){
      val=true;
  }
return(val);
}

bool checkList(string s,Project toDoList,int &pos){ //Comprova si hi ha alguna llista amb el mateix nom i la posició en la que es troba
  bool val=false;
  pos=0;

  for(unsigned int i=0;i<toDoList.lists.size();i++){
    if(s==toDoList.lists[i].name){  
      pos=i;  
      i=toDoList.lists.size();
      val=true;
    }
  }
return(val);
}

bool findList(string &s,Project toDoList,int &pos){
bool val=true;

  do{
  cout<<E_LN; getline(cin,s); 
  }while(checkEmpty(s));

  if(checkList(s,toDoList,pos)){
  }else{
    val=false;
  }
return(val);
}


bool findTask(List temp,Task ttemp,int &pos1,int &pos2,Project &toDoList){
string s;

  cout<<E_TN; getline(cin,s,'\n');

  for(unsigned int i=0;i<toDoList.lists[pos1].tasks.size();i++){
    if(s==toDoList.lists[pos1].tasks[i].name){ 
      pos2=i;
      i=toDoList.lists[pos1].tasks.size();
      return(true);
    }
  }
return(false);
}

bool checkDate(string sd,string sm,string sy){

  int day,month,year;

  day=stoi(sd);
  month=stoi(sm);
  year=stoi(sy);

  if(year<n2000 || year>n2100){
    return(true);
  }

  if(month<n1 || month>n12){
    return(true);
  }

  if(day<n1 || day>n31){
    return(true);
  }

  switch(month){
    case 2: 
      if(day>n29){
        return(false);
      }
      if(day==n29){
        if(year%n100==0){
          if(year%n400==0){
            break;
          }else{
            return(false);
          }  
        }else{
          return(false);
        }
        if(year%n4!=0){
          return(false);
        }
      }
      break;
    case 4: 
      if(day>n30){
        return(false);
      }
      break;
    case 6: 
      if(day>n30){
        return(false);
      }
      break;
    case 9: 
      if(day>n30){
        return(false);
      }
      break;
    case 11:
      if(day>n30){
        return(false);
      }
      break;
  }


return(false);
}

void editProject(Project &toDoList){
  string s;

  do{
    cout<<E_PN; getline(cin,s);
  }while(checkEmpty(s));

  toDoList.name=s;
  cout<<E_PD; getline(cin,toDoList.description);
}

void addList(Project &toDoList){ 
  List temp;
  string s;
  int pos,i;

  i=toDoList.lists.size();

  if(toDoList.lists.size()==0){
    do{
      cout<<E_LN; getline(cin,s);
    }while(checkEmpty(s));
    toDoList.lists.push_back(temp);
    toDoList.lists[0].name=s;
  }else{
    if(findList(s,toDoList,pos)){
      error(ERR_LIST_NAME);
    }else{
      toDoList.lists.push_back(temp);
      toDoList.lists[i].name=s;
    }
  }
}

void deleteList(Project &toDoList){
  List temp;
  string s;
  int pos;
  
  if(findList(s,toDoList,pos)){
    toDoList.lists.erase(toDoList.lists.begin()+pos);
  }else{
    error(ERR_LIST_NAME);
  }
}

void addTask(Project &toDoList){
  Task ttemp;
  List temp;
  int pos,i,time=0;
  string s,t,sd,sm,sy; //t=string per al nom de task, sd=string day, sm=string month i sy=string year

  if(findList(s,toDoList,pos)){
    cout<<E_TN; getline(cin,t,'\n');
    cout<<E_D;
      getline(cin,sd,'/');
      getline(cin,sm,'/');
      getline(cin,sy,'\n');
    if(checkDate(sd,sm,sy)){
      error(ERR_DATE);
    }else{
      cout<<E_ET; cin>>time;
      if(time<1 || time>180){
        error(ERR_TIME);
      }else{
        toDoList.lists[pos].tasks.push_back(ttemp);
        i=toDoList.lists[pos].tasks.size()-1;
        toDoList.lists[pos].tasks[i].name=t;
        toDoList.lists[pos].tasks[i].time=time;
        toDoList.lists[pos].tasks[i].isDone=false;
        toDoList.lists[pos].tasks[i].deadline.day=stoi(sd);
        toDoList.lists[pos].tasks[i].deadline.month=stoi(sm);
        toDoList.lists[pos].tasks[i].deadline.year=stoi(sy);
     }
    }
  }else{
    error(ERR_LIST_NAME);
  }
}

void deleteTask(Project &toDoList){ 
  Task ttemp;
  List temp;
  int pos,i;
  string s;

  if(findList(s,toDoList,pos)){
    if(findTask(temp,ttemp,pos,i,toDoList)){
      toDoList.lists[pos].tasks.erase(toDoList.lists[pos].tasks.begin()+pos);
    }else{
      error(ERR_TASK_NAME);
    }
  }else{
    error(ERR_LIST_NAME);
  }
}

void toggleTask(Project &toDoList){
List temp;
Task ttemp;
int pos1,pos2;
string s;

  if(findList(s,toDoList,pos1)){
    if(findTask(temp,ttemp,pos1,pos2,toDoList)){
      if(toDoList.lists[pos1].tasks[pos2].isDone){
        toDoList.lists[pos1].tasks[pos2].isDone=false;
      }else{
        toDoList.lists[pos1].tasks[pos2].isDone=true; 
      }
    }else{
      error(ERR_TASK_NAME);
    }
  }
}

void report(const Project &toDoList){ //CANVIAR HIGHEST PRIORITY!
  List temp;
  Task ttemp;
  int tottimed=0,tottimel=0,countd=0,countl=0,sd=0,sm=0,sy=0; //tottimed=temps total de tasques fetes, tottimel=temps total de tasques per acabar, countd=comptador de tasques fetes, countl=comptador de tasques per fer
  string s;
  bool aux=false; //auxiliar per a imprimir el Highest priority

  cout<<N<<toDoList.name<<endl;
  cout<<D<<toDoList.description<<endl;
  
  for(unsigned int i=0;i<toDoList.lists.size();i++){
    cout<<toDoList.lists[i].name<<endl;
    if(toDoList.lists[i].tasks.size()==0){
    }else{
      for(unsigned int j=0;j<toDoList.lists[i].tasks.size();j++){
        aux=true;
        cout<<"[";
        if(toDoList.lists[i].tasks[j].isDone==true){
          cout<<"X";
          countd++;
          tottimed+=toDoList.lists[i].tasks[j].time;
        }else{
          cout<<" ";
          tottimel+=toDoList.lists[i].tasks[j].time; 
          countl++;
          if((i==0) && (j==0)){
          sy=toDoList.lists[i].tasks[j].deadline.year;
          sm=toDoList.lists[i].tasks[j].deadline.month;
          sd=toDoList.lists[i].tasks[j].deadline.day;
          s=toDoList.lists[i].tasks[j].name;
          }else{
            if(sy<=toDoList.lists[i].tasks[j].deadline.year){
              if(sm<=toDoList.lists[i].tasks[j].deadline.month){
                if(sd<toDoList.lists[i].tasks[j].deadline.day){
                  sy=toDoList.lists[i].tasks[j].deadline.year;
                  sm=toDoList.lists[i].tasks[j].deadline.month;
                  sd=toDoList.lists[i].tasks[j].deadline.day;
                  s=toDoList.lists[i].tasks[j].name;
                }
              }
            }
          }
        }
        cout<<"] ";
        cout<<"("<<toDoList.lists[i].tasks[j].time<<") "<<toDoList.lists[i].tasks[j].deadline.year<<"-"<<toDoList.lists[i].tasks[j].deadline.month<<"-"<<toDoList.lists[i].tasks[j].deadline.day<<" : "<<toDoList.lists[i].tasks[j].name<<endl;
      }
    }
  }
  
  cout<<TL<<countl<<" ("<<tottimel<<" "<<MIN<<")"<<endl;
  cout<<TD<<countd<<" ("<<tottimed<<" "<<MIN<<")"<<endl;
  if(aux){
    cout<<HP<<s<<" "<<"("<<sy<<"-"<<sm<<"-"<<sd<<")"<<endl;
  }else{
  }
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
