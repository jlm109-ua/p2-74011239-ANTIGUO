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

bool ToDo::loadData(vector<Project*> &lp,string filename""){ //REPASAR DIAPOSITIVA
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

void ToDo::saveData(string filename"") const{
    BinToDo btd;

    strcpy(btd.name,ToDo::name);
    btd.numProjects=ToDo::projects.size();

    cout<<Util::E_FN(); getline(cin,filename);

    ofstream ofb(filename.c_str(),ios::out | ios::binary);

    if(ofb.is_open()){
        ofb.write((const char*)&btd,sizeof(BinToDo));
        for(unsigned int i=0;i<btd.numProjects;i++){
            projects[i]->saveData(ofb); //està bé açò?
        }
        ofb.close();
    }else{
        Util::error(ERR_FILE);
    }
}

bool ToDo::importProjects(vector<Project*> &lp,string filename""){
    string namet,aux="";
    size_t pos;
    bool fail=false,failt,cd;
    int list;

    cout<<Util::E_FN(); getline(cin,filename);

    ifstream ifs(filename.c_str());

    if(ifs.is_open()){
        while(getline(ifs,s)){
            if(s[0]=='<'){
                list=0;
                ToDo::nextId++;
                cd=true; 
                fail=false;
                failt=false;
            }else if(s[0]=='>' && !fail && !failt){
                if(list>0){
                    p->addList(l);
                }
                this->projects.push_back(p);
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
                    Project *p=new Project(ss);
                    p->setId(ToDo::nextId);
                }
            }else if(s[0]=='*'){
                cd=false;
                pos=s.find('*');
                p->setDescription(s.substr(pos+1));
            }else if(cd){
                p->setDescription(aux);
            }else if(s[0]=='@'){
                if(list>0){
                    p->addList(l);
                }
                pos=s.find('@');
                ss=s.substr(pos+1);
                if(checkEmpty(ss)){
                    error(ERR_LIST_NAME);
                    fail=true;
                }else{
                    List l(ss);
                }
                list++;
            }else if(s[0]=='|'){
                Task t(aux);
                if(t.importTask(s)){
                    p->addTasktoList(l.getName(),t);
                }
            }else{
                ss=s.substr(0);
                pos=ss.find("|");
                namet=ss.substr(0,pos-1); 
                Task t(namet);
                if(t.importTask(s)){
                    p->addTasktoList(l.getName(),t);
                }
            }
        }

        ifs.close();
    }else{
        Util::error(ERR_FILE);
    }
}

void ToDo::exportProjects(string filename,int id) const{
    char opt;

    if(id==-1){
        do{
            cout<<Util::SAP(); cin>>opt;
            if(opt=='Y' || opt=='y'){
                //continuar
            }else if(opt=='N' || opt=='n'){
                //continuar    
            }
        }while(opt!='Y' && opt!='y' && opt!='N' && opt!='n');
    }else{
        if(checkId(projects,id)){
            //continuar
        }else{
            Util::error(ERR_ID);
        }
    }
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

void checkId(vector<Project *> projects,int id){
    for(unsigned int i=0;i<projects.size();i++){
        if(id==projects[i]->getId()){
            return(true);
        }
    }
    return(false);
}