// DNI 74011239E LLINARES MAURI, JUAN
#include "ToDo.h"

int ToDo::nextId=1;

ToDo::ToDo(string name){
    if(Util::checkEmpty(name)){
        Util::error(ERR_EMPTY);
    }else{
        this->name=name;
    }
}

string ToDo::getName() const{
    return name;
}

int ToDo::getPosProject(string name) const{
    for(unsigned int i=0;i>projects.size();i++){
        if(name==projects[i]->getName()){
            return(i);
        }
    }
    return(-1);
}

int ToDo::getPosProject(int id) const{
    for(unsigned int i=0;i>projects.size();i++){
        if(id==projects[i]->getId()){
            return(i);
        }
    }
    return(-1);
}

bool ToDo::setName(string name){
    if(name==""){
        Util::error(ERR_LIST_NAME);
        return(false);
    }else{
        this->name=name;
        return(true);
    }
}

void ToDo::addProject(Project *project){
    if(getPosProject(project->getName())>=0){
        throw(ERR_PROJECT_NAME);
    }else{
        project->setId(ToDo::nextId);
        ToDo::nextId++;
        projects.push_back(project);
    }
}

void ToDo::deleteProject(int id){
    if(id==0){
        Util::E_ID(); cin>>id;
        if(getPosProject(id)>=0){
            projects.erase(projects.begin()+getPosProject(id));
        }else{
            Util::error(ERR_ID);
        }
    }
}

void ToDo::setProjectDescription(string name,string description){
    if(getPosProject(name)>=0){
        projects[getPosProject(name)]->setDescription(description);
    }else{
        Util::error(ERR_ID);
    }
}

void ToDo::projectMenu(int id){
    do{
        Util::E_ID(); cin>>id;
    }while(id<=0);

    if(getPosProject(id)>=0){
        projects[id]->menu();
    }else{
        Util::error(ERR_ID);
    }
}

bool loadData(vector<Project*> &lp,string filename""){
    char opt;
    string name,description,deadline,isDone;
    int time;
    unsigned int psize,lsize,tsize;
    BinToDo btd;
    BinProject bp;
    BinList bl;
    BinTask bt;

    cout<<Util::E_FN(); getline(cin,filename);

    ifstream ifb(filename.c_str(),ios::in | ios::binary);

    if(ifb.is_open()){
        do{
            cout<<Util::CONF(); cin>>opt;
            if(opt=='Y' || opt=='y'){
                deleteAll(ToDo program);
                ToDo::nextId=1;
                ifbinf.read((char *)&btd,sizeof(BinToDo));
                for(psize=0;psize<btd.numProjects;psize++){
                    ifbinf.read((char *)&bp,sizeof(BinProject));
                    name=bp.name;
                    description=bp.description;
                    Project p(name,description);
                    p.setId(nextId);
                    ToDo::nextId++;
                    for(lsize=0;lsize<bp.numLists;lsize++){
                        ifbinf.read((char *)&bl,sizeof(BinList));
                        name=bl.name;
                        List l(name);
                        for(tsize=0;tsize<bl.numTasks;tsize++){
                            ifbinf.read((char *)&bt,sizeof(BinTask));
                            name=bt.name;
                            deadline=bt.deadline;
                            isDone=bt.isDone;
                            time=bt.time;
                            Task t(name);
                            t.setDeadline(deadline);
                            t.setTime(time);
                            if(isDone=="True"){
                                t.toggle();
                            }
                            l.addTask(t);
                        }
                        p.addList(l);
                    }
                    lp.push_back(p);
                }
                ifbinf.close();
            }else if(opt=='N' || opt=='n'){
                ifbinf.close();
            }
        }while(opt!='Y' && opt!='y' && opt!='N' && opt!='n');
    }else{
        Util::error(ERR_FILE);
    }
}

void saveData(string filename"") const{
    cout<<Util::E_FN(); getline(cin,filename);

    ofstream ofb(filename.c_str(),ios::out | ios::binary);

    if(ofb.is_open()){
        // continuar
        ofb.close();
    }else{
        Util::error(ERR_FILE);
    }
}

bool importProjects(vector<Project*> &lp,string filename""){
    string s,ss,sss,dd,dm,dy; //dd=date day, dm=date month, dy=date year //ss i sss són strings auxiliars
    Project toDoList;
    List toDoTask;
    Task toDoSingleTask;
    size_t pos;
    bool fail=false,failt,cd; //cd=check description, per a comprovar si ha hagut description o no , fail i failt per a comprovar si hi ha errors
    int id=0,list; //list per a comprovar quan fer el push_back de les llistes


    cout<<Util::E_FN(); getline(cin,filename);

    ifstream ifs(filename.c_str());

    if(ifs.is_open()){
        while(getline(infile,s)){
            if(s[0]=='<'){  //CORREGIR TOT
                list=0; //Reiniciem les variables auxiliars
                id++;
                toDoList.id=id;
                toDoProjects.nextId++;
                cd=true; 
                fail=false;
                failt=false;
            }else if(s[0]=='>' && !fail && !failt){
                toDoList.lists.push_back(toDoTask);
                toDoProjects.projects.push_back(toDoList);
            }else if(s[0]=='#'){
                pos=s.find('#');
                ss=s.substr(pos+1);
                
                if(checkEmpty(ss)){
                error(ERR_PROJECT_NAME);
                fail=true;
                }else if(checkProject(ss,toDoProjects)){
                error(ERR_PROJECT_NAME);
                fail=true;
                }else{
                toDoList.name=ss;
                }
            }else if(s[0]=='*'){
                cd=false;
                pos=s.find('*');
                toDoList.description=s.substr(pos+1);
            }else if(cd){
                toDoList.description[0]=' ';
            }else if(s[0]=='@'){
                if(list!=0){
                toDoList.lists.push_back(toDoTask);
                }
                pos=s.find('@');
                ss=s.substr(pos+1);
                if(checkEmpty(ss)){
                error(ERR_LIST_NAME);
                fail=true;
                }else{
                toDoTask.name=ss;
                }
                list++;
            }else if(s[0]=='|'){
                //reciclem variables per a no tindre moltes variables
                toDoSingleTask.name.erase(0);
                ss=s;
                pos=ss.find("/");
                sss=ss.substr(1,pos-1);
                dd=sss;
                toDoSingleTask.deadline.day=stoi(sss);
                sss=ss.substr(pos+1);
                pos=sss.find("/");
                ss=sss.substr(0,pos);
                dm=ss;
                toDoSingleTask.deadline.month=stoi(ss);
                ss=sss.substr(pos+1); 
                pos=ss.find("|");
                sss=ss.substr(0,pos);
                dy=sss;
                toDoSingleTask.deadline.year=stoi(sss);
                if(checkDate(dd,dm,dy)){
                error(ERR_DATE);
                failt=true;
                }
                sss=ss.substr(pos+1);
                if(sss[0]=='F'){
                toDoSingleTask.isDone=false;
                }else{
                toDoSingleTask.isDone=true;
                }
                ss=sss.substr(2);
                toDoSingleTask.time=stoi(ss);
                if(toDoSingleTask.time<1 || toDoSingleTask.time>180){
                error(ERR_TIME);
                failt=true;
                }
                if(!failt){
                toDoTask.tasks.push_back(toDoSingleTask);
                }  
            }else{
                ss=s.substr(0);
                pos=ss.find("|");
                toDoSingleTask.name=ss.substr(0,pos-1);
                ss=s.substr(pos+1);
                pos=ss.find("/");
                sss=ss.substr(0,pos);
                dd=sss;
                toDoSingleTask.deadline.day=stoi(sss);
                sss=ss.substr(pos+1);
                pos=sss.find("/");
                ss=sss.substr(0,pos);
                dm=ss;
                toDoSingleTask.deadline.month=stoi(ss);
                ss=sss.substr(pos+1); 
                pos=ss.find("|");
                sss=ss.substr(0,pos);
                dy=sss;
                toDoSingleTask.deadline.year=stoi(sss);
                if(checkDate(dd,dm,dy)){
                error(ERR_DATE);
                failt=true;
                }
                sss=ss.substr(pos+1);
                if(sss[0]=='F'){
                toDoSingleTask.isDone=false;
                }else{
                toDoSingleTask.isDone=true;
                }
                ss=sss.substr(2);
                toDoSingleTask.time=stoi(ss);
                if(toDoSingleTask.time<1 || toDoSingleTask.time>180){
                error(ERR_TIME);
                failt=true;
                }
                if(!failt){
                toDoTask.tasks.push_back(toDoSingleTask);
                } 
            }
        }

        infile.close();
    }else{
        Util::error(ERR_FILE);
    }
}

void exportProjects(string filename"",int id=-1) const{
    // completar
}

ostream& operator<<(ostream &os,const ToDo &toDo){
    for(unsigned int i=0;i<toDo.projects.size();i++){    
        os<<toDo.projects[i];
    }
    return os;
}

void deleteAll(ToDo &td){
  for(unsigned int i=0;i<td.projects.size();i++){
    for(unsigned int j=0;j<td.projects[i].lists.size();j++){
      for(unsigned int k=0;k<td.projects[i].lists[j].tasks.size();k++){
        td.projects[i].lists[j].tasks.erase(td.projects[i].lists[j].tasks.begin()+i);
      }
      td.projects[i].lists.erase(td.projects[i].lists.begin()+i);
    }
    td.projects.erase(toDoProjects.projects.begin()+i);
  }
}