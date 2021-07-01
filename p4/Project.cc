// DNI 74011239E LLINARES MAURI, JUAN
#include "Project.h"

const string N="Name: ";
const string D="Description: ";
const string TL="Total left: ";
const string TD="Total done: ";
const string MIN="minutes";
const string HP="Highest priority: ";

Project::Project(const BinProject &bp){
    this->name=bp.name;
    this->description=bp.description;
    this->id=0;
}

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
    for(unsigned int i=0;i<lists.size();i++){
         if(name==lists[i].getName()){
             return(i);
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
        if(Util::checkEmpty(name)){
            Util::error(ERR_EMPTY);
        }
    }while(Util::checkEmpty(name));

    Util::E_PD(); getline(cin,description);

    setName(name);
    setDescription(description);
}

void Project::addList(string name){
    try{
        do{
            Util::E_LN(); getline(cin,name);
            if(Util::checkEmpty(name)){
                Util::error(ERR_EMPTY);
            }
        }while(Util::checkEmpty(name));
        if(!checkList(lists,name)){
            List list(name);
            lists.push_back(list);
        }else{
            Util::error(ERR_LIST_NAME);
        }
    }catch(Error e){
        Util::error(e);
    }
}

void Project::deleteList(string name){
    int pos;

    do{
        Util::E_LN(); getline(cin,name);
        if(Util::checkEmpty(name)){
            Util::error(ERR_EMPTY);
        }
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

    if(checkList(lists,namel)){
        Util::E_TN(); getline(cin,name);
        Util::E_DD(); getline(cin,deadline);
        Task task(name);
        if(task.setDeadline(deadline)){
            Util::E_ET(); cin>>time;
            if(task.setTime(time)){
                lists[getPosList(namel)].addTask(task);
            }
        }
    }else{
        Util::error(ERR_LIST_NAME);
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
        }else{
            Util::error(ERR_TASK_NAME);
        }
    }else{
        Util::error(ERR_LIST_NAME);
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
        }else{
            Util::error(ERR_TASK_NAME);
        }
    }else{
        Util::error(ERR_LIST_NAME);
    }
}

void Project::menu(){
    char opc;
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
            case '1':
                edit(name="",description="");
                break;
            case '2':
                addList(name="");
                break;
            case '3':
                deleteList(name="");
                break;
            case '4':
                addTaskToList(name="");
                break;
            case '5':
                deleteTaskFromList(name="");
                break;
            case '6':
                toggleTaskFromList(name="");
                break;
            case '7':
                cout<<*this<<endl;
                break;
            case 'b':
                break;
            default:
                Util::error(ERR_OPTION);
        }
    }while(opc!='b');
}

string Project::summary() const{
    int totdone=0,tot=0;
    totTasks(lists,totdone,tot);
    string summ,sid,stotdone,stot;
    stringstream ssid,sstotdone,sstot;
    ssid<<this->id;
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

string Project::exportProject() const{
    string ep;

    if(Util::checkEmpty(description)){
        ep='#'+getName();
        for(unsigned int i=0;i<lists.size();i++){
            ep=ep+'\n';
            ep=ep+lists[i].exportList();
        }
    }else{
        ep='#'+getName()+'\n'+'*'+getDescription();
        for(unsigned int i=0;i<lists.size();i++){
            ep=ep+'\n';
            ep=ep+lists[i].exportList();
        }
    }
}

void Project::addList(const List &list){
    string namel=list.getName();
    if(!checkList(lists,namel)){
        lists.push_back(list);
    }
}

void Project::addTaskToList(string name,const Task &task){
    if(!checkList(lists,name)){
        lists[getPosList(name)].addTask(task);
    }
}

BinProject Project::toBinary() const{
    string namep=getName(),descp=getDescription();
    BinProject bp;

    if(namep.size()>=KMAXNAME){
        strncpy(bp.name,namep.c_str(),KMAXNAME);
        bp.name[KMAXNAME]='\0';
    }else{
        strcpy(bp.name,namep.c_str());
    }

    if(descp.size()>=KMAXDESC){
        strncpy(bp.description,descp.c_str(),KMAXDESC);
        bp.description[KMAXDESC]='\0';
    }else{
        strcpy(bp.description,descp.c_str());
    }

    bp.numLists=lists.size();

    return (bp);
}

void Project::saveData(ofstream &file) const{
    BinProject bp=toBinary();

    file.write((const char*)&bp,sizeof(BinProject));
    for(unsigned int i=0;i<bp.numLists;i++){
        this->lists[i].saveData(file); //??? està bé?
    }
}

ostream& operator<<(ostream &os,const Project &project){
    string s;
    Date deadline;
    int tottime=0,tottimed=0,sy=0,sm=0,sd=0,count=0,countd=0,cont=0;
    bool aux=false;

    os<<N<<project.getName()<<endl;
    if(!Util::checkEmpty(project.getDescription())){
        os<<D<<project.getDescription()<<endl;
    }

    for(unsigned int i=0;i<project.lists.size();i++){
        os<<project.lists[i];
        vector<Task> tasks=project.lists[i].getTasks();
        for(unsigned int j=0;j<project.lists[i].getNumTasks();j++){  
            if(tasks[j].getIsDone()){
                countd++;
                tottimed+=tasks[j].getTime();
            }else{
                count++;
                tottime+=tasks[j].getTime();

                deadline=tasks[j].getDeadline();

                if(cont==0){
                    aux=true;
                    cont++;
                    sy=deadline.year;
                    sm=deadline.month;
                    sd=deadline.day;
                    s=tasks[j].getName();
                }
                if(deadline.year<sy){
                    sy=deadline.year;
                    sm=deadline.month;
                    sd=deadline.day;
                    s=tasks[j].getName();
                }else if(deadline.month<sm){
                    sy=deadline.year;
                    sm=deadline.month;
                    sd=deadline.day;
                    s=tasks[j].getName();
                }else if(deadline.day<sd && deadline.month<sm && deadline.year<=sy){
                    sy=deadline.year;
                    sm=deadline.month;
                    sd=deadline.day;
                    s=tasks[j].getName();
                }else if(deadline.day==sd && deadline.month==sm && deadline.year==sy){
                    sy=deadline.year;
                    sm=deadline.month;
                    sd=deadline.day;
                    s=tasks[j].getName();
                }
            }
        }
    }
  
    os<<Util::TL()<<count<<" ("<<tottime<<" "<<Util::MIN()<<")"<<endl;
    os<<Util::TD()<<countd<<" ("<<tottimed<<" "<<Util::MIN()<<")"<<endl;
    if(aux){
        os<<HP<<s<<" "<<"("<<sy<<"-"<<sm<<"-"<<sd<<")"<<endl;
    }else{
    }
    return os;
}

bool Project::checkList(vector<List> lists,string name){
    if(lists.size()>0){
        for(unsigned int i=0;i<lists.size();i++){
            if(name==lists[i].getName()){
                return(true);
            }
        }
    }else if(lists.size()==0){
        return(false);
    }
    return(false);
}

bool Project::checkTask(vector<Task> tasks,string name,string namel){
    if(!tasks.size()==0){
        for(unsigned int i=0;i<tasks.size();i++){
            if(name==tasks[i].getName()){    
                return(true);
            }
        }
    }
    return(false);
}

void Project::totTasks(vector<List> lists,int &totdone,int &tot) const{
    for(unsigned int i=0;i<lists.size();i++){
        totdone+=lists[i].getNumDone();
        tot+=lists[i].getNumTasks();
    }
}