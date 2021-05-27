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
  size_t found=0;
  int s;

  s=deadline.find('/');
  if(found!=string::npos){
    sday=deadline.substr(0,s);
  }
  auxdeadline=deadline.substr(s+1);
  s=deadline.find('/');
  if(found!=string::npos){
    smonth=auxdeadline.substr(0,s);
    syear=auxdeadline.substr(s+1);
  }

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
void Util::E_ET(){
  cout<<"Enter expected time: "<<endl;
}
void Util::N(){
  cout<<"Name: "<<endl;
}
void Util::D(){
  cout<<"Description: "<<endl;
}
void Util::TL(){
  cout<<"Total left: "<<endl;
}
void Util::TD(){
  cout<<"Total done: "<<endl;
}
void Util::MIN(){
  cout<<"minutes"<<endl;
}
void Util::HP(){
  cout<<"Highest priority: "<<endl;
}
void Util::E_ID(){
  cout<<"Enter project id: "<<endl;
}