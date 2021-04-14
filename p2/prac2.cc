// DNI: 74011239E Nom: Juan Llinares Mauri

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string.h>
#include <fstream>

using namespace std;

const int KMINMONTH=1;
const int KMAXMONTH=12;
const int KMAXFEB=29;
const int KMAXDAY2=30;
const int KMAXDAY=31;
const int KMINYEAR=2000;
const int KMAXYEAR=2100;
const int KMAXNAME=20;
const int KMAXDESC=40;

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
const string MIN="minutes";
const string HP="Highest priority: ";
const string E_ID="Enter project id: ";
const string E_FN="Enter filename: ";
const string SAP="Save all projects [Y/N]?: ";
const string CONF="Confirm [Y/N]?: ";
const char argi[]="-i";
const char argl[]="-l";

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

struct ToDo{
  int nextId;
  string name;
  vector<Project> projects;
};

struct BinTask{
  char name[KMAXNAME];
  Date deadline;
  bool isDone;
  int time;
};

struct BinList{
  char name[KMAXNAME];
  unsigned numTasks;
};

struct BinProject{
  char name[KMAXNAME];
  char description[KMAXDESC];
  unsigned numLists;
};

struct BinToDo{
  char name[KMAXNAME];
  unsigned numProjects;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME,
  ERR_ID,
  ERR_PROJECT_NAME,
  ERR_FILE,
  ERR_ARGS
};

/* DECLARACIÓ DE TOTS ELS MÒDULS/FUNCIONS */

void error(Error e);
void showMainMenu();
void showProjectMenu();
bool checkEmpty(string s);
bool checkList(string s,ToDo &toDoProjects,int &pos,const int id);
bool findList(string &s,ToDo &toDoProjects,int &pos,const int id);
bool findTask(string &s2,int &pos1,int &pos2,ToDo &toDoProjects,const int id);
bool delDupes(string s2,int &pos1,ToDo &toDoProjects,const int id);
bool checkDate(string sd,string sm,string sy);
bool checkProject(string s,ToDo &toDoProjects);
bool checkId(const int id,ToDo &toDoProjects);
void deleteAll(ToDo &toDoProjects);
void exportProjectFunct(ToDo &toDoProjects,int id,ofstream offile);
void importArg(string s,ToDo &toDoProjects);
void loadArg(string s,ToDo &toDoProjects);
void argManag(int argc,char *argv[],ToDo &todoProjects);
void editProject(ToDo &toDoProjects,int id);
void addList(ToDo &toDoProjects,int id);
void deleteList(ToDo &toDoProjects,int id);
void addTask(ToDo &toDoProjects,int id);
void deleteTask(ToDo &toDoProjects,int id);
void toggleTask(ToDo &toDoProjects,int id);
void report(const ToDo &toDoProjects,const int id);
void projectMenu(ToDo &toDoProjects);
void addProject(ToDo &toDoProjects);
void deleteProject(ToDo &toDoProjects);
void importProjects(ToDo &toDoProjects);
void exportProjects(ToDo &toDoProjects);
void loadData(ToDo &toDoProjects);
void saveData(ToDo &toDoProjects);
void summary(ToDo &toDoProjects);
void convertProjects(ToDo &toDoProjects);

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
      break;
    case ERR_ID:
      cout << "ERROR: wrong project id" << endl;
      break;
    case ERR_PROJECT_NAME:
      cout << "ERROR: wrong project name" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_ARGS:
      cout << "ERROR: wrong arguments" << endl;
  }
}

void showMainMenu(){
  cout << "1- Project menu" << endl
       << "2- Add project" << endl
       << "3- Delete project" << endl 
       << "4- Import projects" << endl
       << "5- Export projects" << endl
       << "6- Load data" << endl
       << "7- Save data" << endl
       << "8- Summary" << endl
       << "q- Quit" << endl
       << "Option: ";
}

void showProjectMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl 
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "b- Back to main menu" << endl
       << "Option: ";
}

bool checkEmpty(string s){ //Comprova si la string està buida o plena d'espais
  bool val=false; 
  string v=s; //string del mateix tamany que s per a comprovar que no s'introduisquen solament espais al nom
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

bool checkList(string s,ToDo &toDoProjects,int &pos,const int id){ //Comprova si hi ha alguna llista amb el mateix nom i la posició en la que es troba
  bool val=false;
  pos=0;

  for(unsigned int i=0;i<toDoProjects.projects[id].lists.size();i++){
    if(s==toDoProjects.projects[id].lists[i].name){  
      pos=i;  
      i=toDoProjects.projects[id].lists.size();
      val=true;
    }
  }
return(val);
}

bool findList(string &s,ToDo &toDoProjects,int &pos,const int id){
  bool val=true;

    do{
      cout<<E_LN; getline(cin,s); 
      if(checkEmpty(s)){
        error(ERR_EMPTY);
      }    
    }while(checkEmpty(s));

    if(checkList(s,toDoProjects,pos,id)){
    }else{
      val=false;
    }
  return(val);
}

bool findTask(string &s2,int &pos1,int &pos2,ToDo &toDoProjects,const int id){
  string s;

    cout<<E_TN; getline(cin,s,'\n');

    s2=s;

    for(unsigned int i=0;i<toDoProjects.projects[id].lists[pos1].tasks.size();i++){
      if(s==toDoProjects.projects[id].lists[pos1].tasks[i].name){ 
        pos2=i;
        i=toDoProjects.projects[id].lists[pos1].tasks.size();
        return(true);
      }
    }
  return(false);
}

bool delDupes(string s2,int &pos1,ToDo &toDoProjects,const int id){

  for(unsigned int i=0;i<toDoProjects.projects[id].lists[pos1].tasks.size();i++){
    if(s2==toDoProjects.projects[id].lists[pos1].tasks[i].name){ 
      toDoProjects.projects[id].lists[pos1].tasks.erase(toDoProjects.projects[id].lists[pos1].tasks.begin()+i);
      i-=i; //perquè al borrar la tasca el vector es redueix en tamany i ens saltaríem una posició d'aquest si s'esborra algún duplicat on pot haver-hi un altre duplicat
    }
  }
return(false);
}

bool checkDate(string sd,string sm,string sy){

  int day,month,year,x,y,z; //x,y,z son auxiliars per a comprovar dades
  bool val=false;

  day=stoi(sd);
  month=stoi(sm);
  year=stoi(sy);

  x=year%100;
  y=year%400;
  z=year%4;

  if(year<KMINYEAR || year>KMAXYEAR){
    val=true;
  }

  if(month<KMINMONTH || month>KMAXMONTH){
    val=true;
  }

  if(day<KMINMONTH || day>KMAXDAY){
    val=true;
  }

  switch(month){
    case 2: 
      if(day>KMAXFEB){
        val=true;
      }
      if(day==KMAXFEB){
        if(z!=0){
          val=true;
          break;
        }
        if(x==0){
          if(y==0){
          }else{
            val=true;
          }  
        }else{
          val=true;
        }
      }
      break;
    case 4: 
      if(day>KMAXDAY2){
        val=true;
      }
      break;
    case 6: 
      if(day>KMAXDAY2){
        val=true;
      }
      break;
    case 9: 
      if(day>KMAXDAY2){
        val=true;
      }
      break;
    case 11:
      if(day>KMAXDAY2){
        val=true;
      }
      break;
  }


return(val);
}

bool checkProject(string s,ToDo &toDoProjects){

  if(toDoProjects.nextId==0){
  }else{
    for(unsigned int i=0;i<=toDoProjects.projects.size();i++){
      if(s==toDoProjects.projects[i].name){
        error(ERR_PROJECT_NAME);
        return(true);
      }
    }
  }
  return(false);
}

bool checkId(const int id,ToDo &toDoProjects){
  bool val=false;

  for(unsigned int i=0;i<toDoProjects.projects.size();i++){
    if(id==toDoProjects.projects[i].id){
      val=true;
    }
  }

  return(val);
}

void deleteAll(ToDo &toDoProjects){
  for(unsigned int i=toDoProjects.projects.size();i>0;i--){
    toDoProjects.projects.erase(toDoProjects.projects.begin()+i);
  }
}

void convertProjects(ToDo &toDoProjects){

  // UTILITZAR STRNCPY!!!!!!!!!!!!!!

  /*BinToDo binToDoProjects;

  for(unsigned int i=0;i<toDoProjects.projects.size();i++){

    if(toDoProjects.projects[i].name.length()>19){
      for(unsigned int i2=0;i2<20;i2++){

        if(i2!=19){
          //binToDoProjects[i].name[i2]=toDoProjects.projects[i].name[i2]; ??????????
        }else{
          //binToDoProjects[i].name[i2]='\0';
        }
      }
    }

    if(toDoProjects.projects[i].description.length()>49){
      for(unsigned int j=0;j<50;j++){

        if(j!=49){
          // ???
        }else{
          // ???
        }
      }
    }

    for(unsigned int k=0;k<toDoProjects.projects[i].lists.size();k++){

      if(toDoProjects.projects[i].lists[k].name.size()>19){
        for(unsigned int k2=0;k2<20;k++){

          if(k2!=19){
            // ???
          }else{
            // ???
          }
        }
      }

      for(unsigned int k3=0;k3<toDoProjects.projects[i].lists[k2].tasks.size();k3++){

        if(toDoProjects.projects[i].lists[k].tasks[k3].name.size()>19){
          for(unsigned int k4=0;k4<20;k4++){
              
            if(k4!=19){
              // ???
            }else{
              // ???
            }
          }
        }
      }

    //PREGUNTAR COM ES PODEN GUARDAR DIFERENTS PROJECTS; DIFERENTS STRUCTS????
    }
  }*/
}

void exportProjectsFunct(ToDo &toDoProjects,int id,ofstream offile){
  int val1,val2; //valor auxiliars per al for

  if(id==-1){
    val1=0;
    val2=toDoProjects.projects.size();
  }else{
    val1=id;
    val2=id+1;
  }

  for(int i=val1;i<val2;i++){
    offile<<"<"<<endl;
    offile<<"#"<<toDoProjects.projects[i].name<<endl;
        
    if(!checkEmpty(toDoProjects.projects[i].description)){
      offile<<"*"<<toDoProjects.projects[i].description<<endl;
    }
          
    if(toDoProjects.projects[i].lists.size()!=0){
      for(unsigned int j=0;j<toDoProjects.projects[i].lists.size();j++){
        offile<<"@"<<toDoProjects.projects[i].lists[j].name<<endl;

        if(toDoProjects.projects[i].lists[j].tasks.size()!=0){
        for(unsigned int k=0;k<toDoProjects.projects[i].lists[j].tasks.size();k++){
          offile<<toDoProjects.projects[i].lists[j].tasks[k].name<<"|"<<toDoProjects.projects[i].lists[j].tasks[k].deadline.day<<"/"<<toDoProjects.projects[i].lists[j].tasks[k].deadline.month<<"/"<<toDoProjects.projects[i].lists[j].tasks[k].deadline.year<<"|";
                  
          if(toDoProjects.projects[i].lists[j].tasks[k].isDone){
            offile<<"T|";
          }else{
            offile<<"F|";
          }
          offile<<toDoProjects.projects[i].lists[j].tasks[k].time<<endl;
          }
        }
      }
    }
    offile<<">"<<endl;
  }
}

void importArg(string s,ToDo &toDoProjects){


  cout<<"Argument -i introduït"<<endl; //PROVA
  // COMPLETAR IMPORT PROJECT DES DE ARGUMENT

}

void loadArg(string s,ToDo &toDoProjects){


  cout<<"Argument -l introduït"<<endl; //PROVA
  // COMPLETAR BINARY IMPORT PROJECT DES DE ARGUMENT

  // PREGUNTAR PEL CAS "prac2 -i -l hola" PER QUÈ AL NEMIVER POSA QUE SOLAMENT S'HA INTRODUIT UN ELEMENT? argc=1??????

}

void argManag(int argc,char *argv[],ToDo &toDoProjects){
  int conti=0,contl=0; //Usem contadors per a comprovar que no s'haja escrit el mateix argument dues vegades
  string s;

  for(int i=1;i<argc;i++){
    if(strcmp(argv[i],argi)==0){
      conti++;
    }else if(strcmp(argv[i],argl)==0){
      contl++;
    }else if(conti==1){
      conti++;
      if((strcmp(argv[i],argi)==0)){
        error(ERR_ARGS);
      }else if(strcmp(argv[i],argl)==0){
        error(ERR_ARGS);
      }else{
        s=argv[i];
        importArg(s,toDoProjects);
      }
    }else if(contl==1){
      contl++;
      if((strcmp(argv[i],argi)==0)){
        error(ERR_ARGS);
      }else if(strcmp(argv[i],argl)==0){
        error(ERR_ARGS);
      }else{
        s=argv[i];
        loadArg(s,toDoProjects);
      }
    }else{
      error(ERR_ARGS);
    }
  }
}

/* OPCIONS DEL MENU VISIBLES */

void editProject(ToDo &toDoProjects,int id){ //actualització pendent
  string s;

  do{
    cout<<E_PN; getline(cin,s);
    if(checkEmpty(s)){
      error(ERR_EMPTY);
    }  
  }while(checkEmpty(s));

  toDoProjects.projects[id].name=s;
  cout<<E_PD; getline(cin,toDoProjects.projects[id].description);
}

void addList(ToDo &toDoProjects,int id){ //actualització pendent
  List temp;
  string s;
  int pos,i;

  i=toDoProjects.projects[id].lists.size();

  if(toDoProjects.projects[id].lists.size()==0){
    do{
      cout<<E_LN; getline(cin,s);
      if(checkEmpty(s)){
        error(ERR_EMPTY);
      } 
    }while(checkEmpty(s));
    toDoProjects.projects[id].lists.push_back(temp);
    toDoProjects.projects[id].lists[0].name=s;
  }else{
    if(findList(s,toDoProjects,pos,id)){
      error(ERR_LIST_NAME);
    }else{
      toDoProjects.projects[id].lists.push_back(temp);
      toDoProjects.projects[id].lists[i].name=s;
    }
  }
}

void deleteList(ToDo &toDoProjects,int id){ //actualització pendent
  List temp;
  string s;
  int pos;
  
  if(findList(s,toDoProjects,pos,id)){
    toDoProjects.projects[id].lists.erase(toDoProjects.projects[id].lists.begin()+pos);
  }else{
    error(ERR_LIST_NAME);
  }
}

void addTask(ToDo &toDoProjects,int id){ //actualització pendent
  Task ttemp;
  List temp;
  int pos,i,time=0;
  string s,t,sd,sm,sy; //t=string per al nom de task, sd=string day, sm=string month i sy=string year

  if(findList(s,toDoProjects,pos,id)){
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
        toDoProjects.projects[id].lists[pos].tasks.push_back(ttemp);
        i=toDoProjects.projects[id].lists[pos].tasks.size()-1;
        toDoProjects.projects[id].lists[pos].tasks[i].name=t;
        toDoProjects.projects[id].lists[pos].tasks[i].time=time;
        toDoProjects.projects[id].lists[pos].tasks[i].isDone=false;
        toDoProjects.projects[id].lists[pos].tasks[i].deadline.day=stoi(sd);
        toDoProjects.projects[id].lists[pos].tasks[i].deadline.month=stoi(sm);
        toDoProjects.projects[id].lists[pos].tasks[i].deadline.year=stoi(sy);
     }
    }
  }else{
    error(ERR_LIST_NAME);
  }
}

void deleteTask(ToDo &toDoProjects,int id){ //actualització pendent
  Task ttemp;
  List temp;
  int pos1,pos2;
  string s,s2;

  if(findList(s,toDoProjects,pos1,id)){
    if(findTask(s2,pos1,pos2,toDoProjects,id)){
      toDoProjects.projects[id].lists[pos1].tasks.erase(toDoProjects.projects[id].lists[pos1].tasks.begin()+pos2);
      delDupes(s2,pos1,toDoProjects,id);
    }else{
      error(ERR_TASK_NAME);
    }
  }else{
    error(ERR_LIST_NAME);
  }
}

void toggleTask(ToDo &toDoProjects,int id){ //actualització pendent
List temp;
Task ttemp;
int pos1,pos2;
string s,s2;
  
  if(findList(s,toDoProjects,pos1,id)){
    if(findTask(s2,pos1,pos2,toDoProjects,id)){
      for(unsigned int i=pos2;i<toDoProjects.projects[id].lists[pos1].tasks.size();i++){
        if(s2==toDoProjects.projects[id].lists[pos1].tasks[i].name && toDoProjects.projects[id].lists[pos1].tasks[i].isDone){ 
          toDoProjects.projects[id].lists[pos1].tasks[i].isDone=false;
        }else if(s2==toDoProjects.projects[id].lists[pos1].tasks[i].name && toDoProjects.projects[id].lists[pos1].tasks[i].isDone==false){
          toDoProjects.projects[id].lists[pos1].tasks[i].isDone=true;
        }
      }
    }else{
      error(ERR_TASK_NAME);
    }
  }else{
    error(ERR_LIST_NAME);
  }
}

void report(const ToDo &toDoProjects,const int id){ //actualització pendent
  List temp;
  Task ttemp;
  int tottimed=0,tottimel=0,countd=0,countl=0,sd=0,sm=0,sy=0; //tottimed=temps total de tasques fetes, tottimel=temps total de tasques per acabar, countd=comptador de tasques fetes, countl=comptador de tasques per fer
  string s,s2,s3;
  bool aux=false; //auxiliar per a imprimir el Highest priority

  cout<<N<<toDoProjects.projects[id].name<<endl;
  s2=toDoProjects.projects[id].name;
  for(unsigned int i=0;i<toDoProjects.projects[id].name.length();i++){
    s2[i]=' ';
  }
  s3=toDoProjects.projects[id].description;
  for(unsigned int i=0;i<toDoProjects.projects[id].description.length();i++){
    s3[i]=' ';
  }
  if(s2.length()==0 || s2==toDoProjects.projects[id].name || s3==toDoProjects.projects[id].description || s3.length()==0){ 
  }else{
    cout<<D<<toDoProjects.projects[id].description<<endl;
  }

  for(unsigned int i=0;i<toDoProjects.projects[id].lists.size();i++){
    cout<<toDoProjects.projects[id].lists[i].name<<endl;
    if(toDoProjects.projects[id].lists[i].tasks.size()==0){
    }else{
      for(unsigned int j=0;j<toDoProjects.projects[id].lists[i].tasks.size();j++){
        aux=true;
        cout<<"[";
        if(toDoProjects.projects[id].lists[i].tasks[j].isDone==true){
          cout<<"X";
          countd++;
          tottimed+=toDoProjects.projects[id].lists[i].tasks[j].time;
        }else{
          cout<<" ";
          tottimel+=toDoProjects.projects[id].lists[i].tasks[j].time; 
          countl++;
          if(sm==0 || ((i==0) && (j==0))){
            sy=toDoProjects.projects[id].lists[i].tasks[j].deadline.year;
            sm=toDoProjects.projects[id].lists[i].tasks[j].deadline.month;
            sd=toDoProjects.projects[id].lists[i].tasks[j].deadline.day;
            s=toDoProjects.projects[id].lists[i].tasks[j].name;
          }else{
            if(toDoProjects.projects[id].lists[i].tasks[j].deadline.year<sy){
              sy=toDoProjects.projects[id].lists[i].tasks[j].deadline.year;
              sm=toDoProjects.projects[id].lists[i].tasks[j].deadline.month;
              sd=toDoProjects.projects[id].lists[i].tasks[j].deadline.day;
              s=toDoProjects.projects[id].lists[i].tasks[j].name;
            }else if(toDoProjects.projects[id].lists[i].tasks[j].deadline.year==sy){
              if(toDoProjects.projects[id].lists[i].tasks[j].deadline.month<sm){
                sy=toDoProjects.projects[id].lists[i].tasks[j].deadline.year;
                sm=toDoProjects.projects[id].lists[i].tasks[j].deadline.month;
                sd=toDoProjects.projects[id].lists[i].tasks[j].deadline.day;
                s=toDoProjects.projects[id].lists[i].tasks[j].name;
              }else if(sm==toDoProjects.projects[id].lists[i].tasks[j].deadline.month){
                if(toDoProjects.projects[id].lists[i].tasks[j].deadline.day<sd){
                  sy=toDoProjects.projects[id].lists[i].tasks[j].deadline.year;
                  sm=toDoProjects.projects[id].lists[i].tasks[j].deadline.month;
                  sd=toDoProjects.projects[id].lists[i].tasks[j].deadline.day;
                  s=toDoProjects.projects[id].lists[i].tasks[j].name;
                }
              }
            }
          }
        }
      cout<<"] ";
      cout<<"("<<toDoProjects.projects[id].lists[i].tasks[j].time<<") "<<toDoProjects.projects[id].lists[i].tasks[j].deadline.year<<"-"<<toDoProjects.projects[id].lists[i].tasks[j].deadline.month<<"-"<<toDoProjects.projects[id].lists[i].tasks[j].deadline.day<<" : "<<toDoProjects.projects[id].lists[i].tasks[j].name<<endl;
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

void projectMenu(ToDo &toDoProjects,Project &toDoList){
  int id;

  cout<<E_ID; cin>>id;

  id-=1;

  if(toDoProjects.projects.size()==0){
    error(ERR_ID);
  }else{
    if(id<=toDoProjects.nextId && id>=0){
      char option2;

      do{
        showProjectMenu();
        cin >> option2;
        cin.get();
        
        switch(option2){
          case '1': editProject(toDoProjects,id);
                    break;
          case '2': addList(toDoProjects,id);
                    break;
          case '3': deleteList(toDoProjects,id);
                    break;
          case '4': addTask(toDoProjects,id);
                    break;
          case '5': deleteTask(toDoProjects,id);
                    break;
          case '6': toggleTask(toDoProjects,id);
                    break;
          case '7': report(toDoProjects,id);
                    break;
          case 'b': break;
          default: error(ERR_OPTION);
        }
      }while(option2!='b');
    }else{
      error(ERR_ID);
    }
  }
}

void addProject(ToDo &toDoProjects){
  Project toDoList;
  string s;

  do{
    cout<<E_PN; getline(cin,s);
    if(checkEmpty(s)){
      error(ERR_EMPTY);
    } 
  }while(checkEmpty(s));

  if(checkProject(s,toDoProjects)){
  }else{
    toDoList.name=s;

    cout<<E_PD; getline(cin,toDoList.description);

    toDoProjects.nextId+=1;
    toDoList.id=toDoProjects.nextId;
    toDoProjects.projects.push_back(toDoList);
  }
}

void deleteProject(ToDo &toDoProjects){
  unsigned int id;

  cout<<E_ID; cin>>id;

  id-=1;

  if(id>toDoProjects.projects.size()){
    error(ERR_ID);
  }else{
    toDoProjects.projects.erase(toDoProjects.projects.begin()+id);
  }
}

void importProjects(ToDo &toDoProjects){
  string s,spn,spd,sd,sm,sy,sln,stn,sid,st,f="f",t="t"; //spn=save project name, spd=save project description, sd,sm i sy per a la data, sln=save list name, stn=save task name, sid=save isDone, st=save time
  int id=-1,list=-1,task=-1,time,pos; //inicialitzats en -1 per a que quan llisca el primer projecte, llista o tasca comence pel número 0
  char c;
  Project toDoList;
  List toDoTask;
  Task tTask;

  cout<<E_FN<<endl; getline(cin,s);

  ifstream infile(s.c_str());

  if(infile.is_open()){

    // LLEGIR LINIA PER LINIA I COMPROVAR CARÀCTER; SUBSTR STRING

    do{
      infile.get(c);

      if(c=='>'){
        id++;
      }else if(c=='<'){
      }

      infile.get(c);

      if(c=='#'){
        getline(infile,spn);

        if(checkProject(spn,toDoProjects)){
          while(c!='>'){
            infile.get(c);
          }
        }else{
          infile.get(c);

        if(c=='*'){
          getline(infile,spd);
          infile.get(c);
        }else{
          spd[0]=' ';
        }

          if(c=='@'){
            while(c!='>'){
              list++;
              getline(infile,sln);

              if(checkList(sln,toDoProjects,pos,id)){
                while(c!='@'){
                  task++;
                  getline(infile,stn,'|');
                  getline(infile,sd,'/');
                  getline(infile,sm,'/');
                  getline(infile,sy,'|');

                  if(checkDate(sd,sm,sy)){
                    getline(infile,sid,'|');
                    getline(infile,st);
                    time=stoi(st);

                    if(time>1 && time<180){
                      toDoTask.name=sln;
                      tTask.name=stn;
                      tTask.deadline.day=stoi(sd);
                      tTask.deadline.month=stoi(sm);
                      tTask.deadline.year=stoi(sy);
                      if(sid==f){
                        tTask.isDone=false;
                      }else if(sid==t){
                        tTask.isDone=true;
                      }
                      toDoList.name=spn;
                      toDoList.description=spd;
                      tTask.time=time;
                      toDoTask.tasks.push_back(tTask);
                      toDoList.lists.push_back(toDoTask);
                      toDoProjects.projects.push_back(toDoList);
                    }else{
                      error(ERR_TIME);
                    }
                  }else{
                    error(ERR_DATE);
                  }
                }
              }else{
                error(ERR_LIST_NAME);
              }
            }
            toDoList.name=spn;
            toDoList.description=spd;
            toDoProjects.projects.push_back(toDoList);
          }
        }
      }
    }while(!infile.eof());

    infile.close();
  }else{
    error(ERR_FILE);
  }
}

void exportProjects(ToDo &toDoProjects){
  char opt;
  unsigned int id,val1,val2; //val1 i val2 son valors auxiliars per al for
  string fn;

  cout<<SAP; cin>>opt;
  cin.get();

  do{
    if(opt=='Y' || opt=='y'){
      id=-1;
      cout<<E_FN; getline(cin,fn);
    }else if(opt=='N' || opt=='n'){
      cout<<E_ID; cin>>id;
      cin.get();

      if(checkId(id,toDoProjects)){
        cout<<E_FN; getline(cin,fn);
      }else{
        error(ERR_ID);
      }
    }
  }while(opt!='Y' && opt!='y' && opt!='N' && opt!='n');

  ofstream offile(fn.c_str());

  if(id==-1){
    val1=0;
    val2=toDoProjects.projects.size();
  }else{
    val1=id;
    val2=id+1;
  }

  if(offile.is_open()){
    for(int i=val1;i<val2;i++){
      offile<<"<"<<endl;
      offile<<"#"<<toDoProjects.projects[i].name<<endl;
          
      if(!checkEmpty(toDoProjects.projects[i].description)){
        offile<<"*"<<toDoProjects.projects[i].description<<endl;
      }
            
      if(toDoProjects.projects[i].lists.size()!=0){
        for(unsigned int j=0;j<toDoProjects.projects[i].lists.size();j++){
          offile<<"@"<<toDoProjects.projects[i].lists[j].name<<endl;

          if(toDoProjects.projects[i].lists[j].tasks.size()!=0){
          for(unsigned int k=0;k<toDoProjects.projects[i].lists[j].tasks.size();k++){
            offile<<toDoProjects.projects[i].lists[j].tasks[k].name<<"|"<<toDoProjects.projects[i].lists[j].tasks[k].deadline.day<<"/"<<toDoProjects.projects[i].lists[j].tasks[k].deadline.month<<"/"<<toDoProjects.projects[i].lists[j].tasks[k].deadline.year<<"|";
                    
            if(toDoProjects.projects[i].lists[j].tasks[k].isDone){
              offile<<"T|";
            }else{
              offile<<"F|";
            }
            offile<<toDoProjects.projects[i].lists[j].tasks[k].time<<endl;
            }
          }
        }
      }
      offile<<">"<<endl;
    }
    offile.close();
  }else{
      error(ERR_FILE);
  }
}

void loadData(ToDo &toDoProjects){
  string s;
  char opt;

  cout<<E_FN; getline(cin,s);

  ifstream ifbinf(s.c_str(),ios::in | ios::binary);

  if(ifbinf.is_open()){
    do{
      cout<<CONF; cin>>opt;

      if(opt=='Y' || opt=='y'){
        deleteAll(toDoProjects);


        //COMPLETAR BINARI
      
      
      }else if(opt=='N' || opt=='n'){
        ifbinf.close();
      }
    }while(opt!='Y' && opt!='y' && opt!='N' && opt!='n');

  }else{
    error(ERR_FILE);
  }


}

void saveData(ToDo &toDoProjects){
  string s;

  cout<<E_FN; getline(cin,s);

  ofstream ofbinf(s.c_str(),ios::out | ios::binary);

  if(ofbinf.is_open()){
    convertProjects(toDoProjects);

    // COMPLETAR BINARI

    //strncpy PER A COPIAR CADENES

    //bucle per a emplenar bintask etc

  }else{
    error(ERR_FILE);
  }
  
}

void summary(ToDo &toDoProjects){
  int ttask=0,dtask=0; //ttask=total tasks, dtask=tasks done

  for(unsigned int i=0;i<toDoProjects.projects.size();i++){
    cout<<"("<<toDoProjects.projects[i].id<<") "<<toDoProjects.projects[i].name<<" ";

    for(unsigned int j=0;j<toDoProjects.projects[i].lists.size();j++){
      for(unsigned int k=0;k<toDoProjects.projects[i].lists[j].tasks.size();k++){
        ttask++;
        if(toDoProjects.projects[i].lists[j].tasks[k].isDone){
          dtask++;
        }
      }
    }
    cout<<"["<<dtask<<"/"<<ttask<<"]"<<endl;
  } 
}

int main(int argc,char *argv[]){
  ToDo toDoProjects; //variable ToDo per a controlar els projectes
  toDoProjects.nextId=0;
  char option;
  Project toDoList;
  toDoProjects.nextId=0;

  argManag(argc,argv,toDoProjects);

  do{
    showMainMenu();
    cin >> option;
    cin.get();
    
    switch(option){
      case '1': projectMenu(toDoProjects,toDoList);
                break;
      case '2': addProject(toDoProjects);
                break;
      case '3': deleteProject(toDoProjects);
                break;
      case '4': importProjects(toDoProjects);
                break;
      case '5': exportProjects(toDoProjects);
                break;
      case '6': loadData(toDoProjects);
                break;
      case '7': saveData(toDoProjects);
                break;
      case '8': summary(toDoProjects);
                break;
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');
  
  return 0;    
}