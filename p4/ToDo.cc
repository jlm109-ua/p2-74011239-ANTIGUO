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
    for(unsigned int i=0;i<projects.size();i++){
        if(name==projects[i]->getName()){
            return(i);
        }
    }
    return(-1);
}

int ToDo::getPosProject(int id) const{
    for(unsigned int i=0;i<projects.size();i++){
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

    int i=getPosProject(id);

    if(i>=0){
        projects[i]->menu();
    }else{
        Util::error(ERR_ID);
    }
}

bool ToDo::loadData(vector<Project*> &lp,string filename){
    char opt;
    string name,description,deadline,isDone;
    Date ddline;
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
                emptyProgram();
                ToDo::nextId=1;
                ifb.read((char *)&btd,sizeof(BinToDo));
                for(psize=0;psize<btd.numProjects;psize++){
                    ifb.read((char *)&bp,sizeof(BinProject));
                    name=bp.name;
                    description=bp.description;
                    Project *p=new Project(bp);
                    p->setId(nextId);
                    ToDo::nextId++;
                    for(lsize=0;lsize<bp.numLists;lsize++){
                        ifb.read((char *)&bl,sizeof(BinList));
                        name=bl.name;
                        List l(name);
                        for(tsize=0;tsize<bl.numTasks;tsize++){
                            ifb.read((char *)&bt,sizeof(BinTask));
                            name=bt.name;
                            ddline=bt.deadline;
                            deadline=ddline.day+'/'+ddline.month+'/'+ddline.year;
                            isDone=bt.isDone;
                            time=bt.time;
                            Task t(name);
                            if(t.setDeadline(deadline)){
                                if(t.setTime(time)){
                                    if(isDone=="True"){
                                        t.toggle();
                                    }
                                    l.addTask(t);
                                }
                            }
                        }
                        p->addList(l);
                    }
                    lp.push_back(p);
                }
                ifb.close();
                return(true);
            }else if(opt=='N' || opt=='n'){
                ifb.close();
                return(false);
            }
        }while(opt!='Y' && opt!='y' && opt!='N' && opt!='n');
    }else{
        Util::error(ERR_FILE);
        return(false);
    }
    return(true);
}

void ToDo::saveData(string filename) const{
    BinToDo btd;

    strcpy(btd.name,this->name.c_str());
    btd.numProjects=this->projects.size();

    cout<<Util::E_FN(); getline(cin,filename);

    ofstream ofb(filename.c_str(),ios::out | ios::binary);

    if(ofb.is_open()){
        ofb.write((const char*)&btd,sizeof(BinToDo));
        for(unsigned int i=0;i<btd.numProjects;i++){
            projects[i]->saveData(ofb);
        }
        ofb.close();
    }else{
        Util::error(ERR_FILE);
    }
}

bool ToDo::importProjects(vector<Project*> &lp,string filename){
    string namet,aux="",s,ss;
    size_t pos;
    bool cd;

    cout<<Util::E_FN(); getline(cin,filename);

    ifstream ifs(filename.c_str());

    if(ifs.is_open()){
        while(getline(ifs,s)){
            if(s[0]=='<'){
                ToDo::nextId++;
                cd=true;
                getline(ifs,s);
                if(s[0]=='#'){
                    pos=s.find('#');
                    Project *p=new Project(s.substr(pos+1));
                    getline(ifs,s);
                    if(s[0]=='*'){
                        cd=false;
                        pos=s.find('*');
                        p->setDescription(s.substr(pos+1));
                    }
                    getline(ifs,s);
                    if(s[0]=='@'){
                        if(cd){
                            p->setDescription(aux);
                        }
                        while(s[0]=='@'){
                            pos=s.find('@');
                            List l(s.substr(pos+1));
                            getline(ifs,s);
                            while(s[0]!='@' && s[0]!='>'){
                                if(s[0]=='|'){
                                    Task t(aux);
                                    if(t.importTask(s)){
                                        p->addTaskToList(l.getName(),t);
                                    }
                                }
                                else{
                                    ss=s.substr(0);
                                    pos=ss.find("|");
                                    namet=ss.substr(0,pos-1); 
                                    Task t(namet);
                                    if(t.importTask(s)){
                                        p->addTaskToList(l.getName(),t);
                                    }
                                }
                            }
                            p->addList(l);
                        }
                        try{
                            addProject(p);
                        }catch(Error e){}
                    }
                }
            }
        }
        ifs.close();
        return(true);
    }else{
        Util::error(ERR_FILE);
        return(false);
    }
}

void ToDo::exportProjects(string filename,int id) const{
    char opt;

    if(id==-1){
        do{
            cout<<Util::SAP(); cin>>opt;
            if(opt=='Y' || opt=='y'){
                ofstream ofb(filename.c_str());

                if(ofb.is_open()){
                    for(unsigned int i=0;i<projects.size();i++){
                        ofb<<"<"<<endl;
                        ofb<<projects[i]->exportProject();
                        ofb<<">"<<endl;
                    }
                    ofb.close();
                }else{
                    Util::error(ERR_FILE);
                }
            }else if(opt=='N' || opt=='n'){
                cout<<Util::E_ID(); cin>>id;
                if(checkId(projects,id)){
                    exportOneProject(projects,filename,id);
                }
            }
        }while(opt!='Y' && opt!='y' && opt!='N' && opt!='n');
    }else{
        if(checkId(projects,id)){
            exportOneProject(projects,filename,id); 
        }else{
        Util::error(ERR_ID);
        }
    }
}

ostream& operator<<(ostream &os,const ToDo &toDo){
    for(unsigned int i=0;i<toDo.projects.size();i++){    
        os<<toDo.projects[i]->summary()<<endl;
    }
    return os;
}

void ToDo::emptyProgram(){
    for(unsigned int i=0;i<projects.size();i++){
        projects.erase(projects.begin()+i);
    }
}

bool ToDo::checkId(vector<Project *> projects,int id) const{
    for(unsigned int i=0;i<projects.size();i++){
        if(id==projects[i]->getId()){
            return(true);
        }
    }
    return(false);
}

void ToDo::exportOneProject(vector<Project *> projects,string filename,int id) const{
    ofstream ofb(filename.c_str());

    if(ofb.is_open()){
        ofb<<"<"<<endl;
        ofb<<projects[id]->exportProject();
        ofb<<">"<<endl;
        ofb.close();
    }else{
        Util::error(ERR_FILE);
    }
}