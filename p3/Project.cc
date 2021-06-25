#include "Project.h"

bool checkList(vector<List> lists,string s);
bool checkTask(vector<Task> tasks,string name,string namel);
void totTasks(vector<List> lists,int &totdone,int &tot);

const string N="Name: ";
const string D="Description: ";
const string TL="Total left: ";
const string TD="Total done: ";
const string MIN="minutes";
const string HP="Highest priority: ";

Project::Project(string name,string description){
    if(Util::checkEmpty(name)){
        Util::error(ERR_EMPTY);
    }else{
        this->name=name;
        this->description=description;
        id=0;
    }
}

int Project::getId() const{
    return id;
}

string Project::getName() const{
    return name;
}

string Project::getDescription() const{
    return description;
}

int Project::getPosList(string name) const{
    int pos;
    for(unsigned int i=0;i<lists.size();i++){
         if(name==lists[i].getName()){
             pos=i;
             return(pos);
         }
    }
    return(-1);
}

bool Project::setId(int id){
    if(id>=0){
        this->id=id;
        return(true);
    }else{
        Util::error(ERR_ID);
        return(false);
    }
}

bool Project::setName(string name){
    if(Util::checkEmpty(name)){
        Util::error(ERR_EMPTY);
        return(false);
    }else{
        this->name=name;
        return(true);
    }
}

void Project::setDescription(string description){
    this->description=description;
}

void Project::edit(string name,string description){
    do{
        Util::E_PN(); getline(cin,name);
    }while(Util::checkEmpty(name));

    Util::E_PD(); getline(cin,description);

    setName(name); //falla (supose que al checkEmpty)
    setDescription(description);
}

void Project::addList(string name){
    try{
        do{
        Util::E_LN(); getline(cin,name);
        }while(checkList(lists,name));//falla
        List list(name);
        lists.push_back(list);
    }catch(Error e){
        Util::error(e);
    }
}

void Project::deleteList(string name){
    int pos;

    do{
        Util::E_LN(); getline(cin,name);
    }while(Util::checkEmpty(name));

    if(getPosList(name)==-1){
        Util::error(ERR_LIST_NAME);
    }else{
        pos=getPosList(name);
        lists.erase(lists.begin()+pos);
    }
}

void Project::addTaskToList(string name){
    string deadline,namel;
    int time;

    do{
        Util::E_LN(); getline(cin,namel);
    }while(Util::checkEmpty(namel));

    if(!checkList(lists,namel)){
        Util::E_TN(); getline(cin,name);
        Util::E_D(); getline(cin,deadline);
        Task task(name);
        if(task.setDeadline(deadline)){
            Util::E_ET(); cin>>time;
            if(task.setTime(time)){
                lists[getPosList(namel)].addTask(task);
            }
        }
    }
}

void Project::deleteTaskFromList(string name){
    string namel;

    do{
        Util::E_LN(); getline(cin,namel);
    }while(Util::checkEmpty(namel));

    if(checkList(lists,namel)>=0){
        vector<Task> tasks=lists[getPosList(namel)].getTasks();

        Util::E_TN(); getline(cin,name);
        if(checkTask(tasks,name,namel)){
            lists[getPosList(namel)].deleteTask(name);
        }
    }
}

void Project::toggleTaskFromList(string name){
    string namel;

    do{
        Util::E_LN(); getline(cin,namel);
    }while(Util::checkEmpty(namel));

    if(checkList(lists,namel)){
        vector<Task> tasks=lists[getPosList(namel)].getTasks();

        Util::E_TN(); getline(cin,name);
        if(checkTask(tasks,name,namel)){
            lists[getPosList(namel)].toggleTask(name);
        }
    }
}

void Project::menu(){
    int opc;
    string name,description;

    do{
        cout<<"1- Edit project"<<endl
            <<"2- Add list"<<endl
            <<"3- Delete list"<<endl 
            <<"4- Add task"<<endl
            <<"5- Delete task"<<endl
            <<"6- Toggle task"<<endl
            <<"7- Report"<<endl
            <<"b- Back to main menu"<<endl
            <<"Option: ";
        cin>>opc;
        cin.get();

        switch(opc){
            case 1:
                edit(name="",description="");
                break;
            case 2:
                addList(name="");
                break;
            case 3:
                deleteList(name="");
                break;
            case 4:
                addTaskToList(name="");
                break;
            case 5:
                deleteTaskFromList(name="");
                break;
            case 6:
                toggleTaskFromList(name="");
                break;
            case 7:
                cout<<*this<<endl;
                break;
            case 'b':
                break;
            default:
                Util::error(ERR_OPTION);
                break;
        }
    }while(opc!='b');
}

string Project::summary() const{ //ARREGLAR
    int totdone=0,tot=0,id=this->id;
    totTasks(lists,totdone,tot);
    string summ,sid,stotdone,stot;
    stringstream ssid,sstotdone,sstot;
    ssid<<id;
    sid=ssid.str();
    sstotdone<<totdone;
    stotdone=sstotdone.str();
    sstot<<tot;
    stot=sstot.str();

    summ+="(";
    summ+=sid;
    summ+=") ";
    summ+=name;
    summ+=" [";
    summ+=stotdone;
    summ+="/";
    summ+=stot;
    summ+="]";

    return (summ); 
}

ostream& operator<<(ostream &os,const Project &project){
    string s,ss;
    Date deadline;
    int tottime=0,tottimed=0,sy=0,sm=0,sd=0,count=0,countd=0;
    bool aux=false;

    os<<N<<project.getName()<<endl;
    if(!Util::checkEmpty(project.getDescription())){
        os<<D<<project.getDescription()<<endl;
    }

    for(unsigned int i=0;i<project.lists.size();i++){
        os<<project.lists[i];
        vector<Task> tasks=project.lists[i].getTasks();
        for(unsigned int j=0;i<project.lists[i].getNumTasks();j++){  
            
            deadline=tasks[j].getDeadline();

            if(sy>deadline.year){
                sy=deadline.year;
                sm=deadline.month;
                sd=deadline.day;
                ss=project.lists[i].getName();
            }else if(sm>deadline.month){
                sy=deadline.year;
                sm=deadline.month;
                sd=deadline.day;
                ss=project.lists[i].getName();
            }else if(sd>deadline.day && sm>deadline.month && sy>=deadline.year){
                sy=deadline.year;
                sm=deadline.month;
                sd=deadline.day;
                ss=project.lists[i].getName();
            }

        }
    }
  
    os<<TL<<count<<" ("<<tottime<<" "<<MIN<<")"<<endl;
    os<<TD<<countd<<" ("<<tottimed<<" "<<MIN<<")"<<endl;
    if(aux){
        os<<HP<<s<<" "<<"("<<sy<<"-"<<sm<<"-"<<sd<<")"<<endl;
    }else{
    }
    return os;
}

bool checkList(vector<List> lists,string name){
    if(lists.size()>0){
        for(unsigned int i=0;i<lists.size();i++){
            if(name==lists[i].getName()){  
                Util::error(ERR_LIST_NAME);  
                return(true);
            }
        }
    }
    return(false);
}

bool checkTask(vector<Task> tasks,string name,string namel){
    if(!tasks.size()==0){
        for(unsigned int i=0;i<tasks.size();i++){
            if(name==tasks[i].getName()){  
                Util::error(ERR_LIST_NAME);  
                return(true);
            }
        }
    }
    return(false);
}

void totTasks(vector<List> lists,int &totdone,int &tot){
    for(unsigned int i=0;i<lists.size();i++){
        totdone+=lists[i].getNumDone();
        tot+=lists[i].getNumTasks();
    }
}