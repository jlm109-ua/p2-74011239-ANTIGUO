// DNI 74011239E LLINARES MAURI, JUAN
#include "Util.h"

void Util::error(Error e){
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
  }
}

bool Util::checkEmpty(string s){
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

void Util::saveDate(string deadline,int &day,int &month,int &year){
  string auxdeadline,sday,smonth,syear;
  size_t found=deadline.find('/');
  
  sday=deadline.substr(0,found);
  auxdeadline=deadline.substr(found+1);
  found=auxdeadline.find('/');
  smonth=auxdeadline.substr(0,found);
  syear=auxdeadline.substr(found+1);

  day=stoi(sday);
  month=stoi(smonth);
  year=stoi(syear);
}

int Util::KMINMONTH(){
  return(1);
};
int Util::KMAXMONTH(){
  return(12);
}
int Util::KMAXFEB(){
  return(29);
}
int Util::KMAXDAY2(){
  return(30);
}
int Util::KMAXDAY(){
  return(31);
}
int Util::KMINYEAR(){
  return(2000);
}
int Util::KMAXYEAR(){
  return(2100);
}
int Util::KMAXNAME(){
  return(20);
}
int Util::KMAXDESC(){
  return(40);
}
void Util::E_PN(){
  cout<<"Enter project name: "<<endl;
}
void Util::E_PD(){
  cout<<"Enter project description: "<<endl;
}
void Util::E_LN(){
  cout<<"Enter list name: "<<endl;
}
void Util::E_TN(){
  cout<<"Enter task name: "<<endl;
}
void Util::E_D(){
  cout<<"Enter project description: "<<endl;
}
void Util::E_DD(){
  cout<<"Enter deadline: ";
}
void Util::E_ET(){
  cout<<"Enter expected time: "<<endl;
}
string Util::N(){
  return("Name: ");
}
string Util::D(){
  return("Description: ");
}
string Util::TL(){
  return("Total left: ");
}
string Util::TD(){
  return("Total done: ");
}
string Util::MIN(){
  return("minutes");
}
string Util::HP(){
  return("Highest priority: ");
}
string Util::E_ID(){
  return("Enter project id: ");
}
string Util::E_FN(){
  return("Enter filename: ");
}
string Util::CONF(){
  return("Confirm [Y/N]?: ");
}
string Util::SAP(){
  return("Save all projects [Y/N]?: ");
}