#include "../include/Session.h"
#include <iostream>
#include <fstream>
#include "../include/Watchable.h"

using json = nlohmann::json;




//Session Constructor
Session::Session(const std::string &configFilePath):userMap() ,actionsLog(),activeUser(nullptr) {
//    TODO add a function so it will look better
//    id counter
    int count = 1;
//    init of json read file
    std::ifstream f(configFilePath);
    json myJson;
    f >> myJson;
    auto *tags= new std::vector<std::string>;
    tags->reserve(10);
//    loop on the type of content
    for (const auto &item : myJson.items()) {
//        crate movie obj and push into content
        if (item.key()=="movies"){
            for (const auto &value : item.value()) {
                std::string name= value["name"];
                int length = value["length"];
//                crate a vector for the tags
                for (const auto &item1 : value["tags"]) {
                    tags->push_back(item1);
                }
//                push the new obj into content
                Watchable *toPush =new Movie(count,name,length,*tags);
                content.push_back((toPush));
                count++;
                tags->clear();
            }
            }
//        crate episode obj
        if (item.key()=="tv_series"){
            for (const auto &value : item.value()) {
                std::string name= value["name"];
                int episode_length = value["episode_length"];
                auto*seasons= new  std::vector<int>;
                seasons->reserve(20);
//                crate tags vector
                for (const auto &item1 : value["tags"]) {
                    tags->push_back(item1);
                }
//                crate a vector for the amount of episode per season
                for (const auto &item1 : value["seasons"]) {
                    seasons->push_back(item1);
                }
//                crate the obj and push to content
                for (unsigned long i = 1; i < seasons->size()+1; ++i) {
                    for (int j = 1; j < seasons->at(i-1)+1; ++j) {
                        content.push_back(new Episode(count,name,episode_length,i,j,*tags));
                        count++;
                    }
                }
                delete seasons;
                tags->clear();
            }
        }

        }
    delete tags;

    }
//    copy constructor
Session::Session(const Session &otherSess){
    activeUser= nullptr;
    copy(otherSess);
}

//Session copy Assignment operator
Session &Session::operator=(const Session &otherSess) {
    if(this!=&otherSess)
    {
        this->clear();
        this->copy(otherSess);
    }
    return *this;
}
//Copy helper function
Session *Session::copy(const Session &otherSess) {
    this->content.reserve(otherSess.content.size());
    for (const auto &otherContent : otherSess.content) {
        this->content.emplace_back(otherContent->copy());}
    this->actionsLog.reserve(otherSess.actionsLog.size());
    for (const auto &item : otherSess.actionsLog) {
        actionsLog.emplace_back(item->copy());
    }
    for (const auto &map : otherSess.userMap) {
        userMap[map.first]=map.second->copy();
    }
    activeUser=userMap[otherSess.activeUser->getName()];
    return this;
}
//move constructor
Session::Session(Session &&other){
    if(this!=&other){
        activeUser= nullptr;
        this->steal((other));}
}
//move operator
Session &Session::operator=(Session &&other) {
    if(this!=&other){
    this->clear();
    steal(other);}
    return *this;
}

Session *Session::steal(Session &other) {
    content=std::move(other.content);
    actionsLog=std::move(other.actionsLog);
    userMap=std::move(other.userMap);
    std::swap(activeUser,other.activeUser);
    other.clear();
    return this;
}

//Session Destructor
Session::~Session() {
   this->clear();
}

//Starts SPLFLIX and handles inputs
void Session::start() {
    if (userMap["default"]== nullptr&&activeUser== nullptr){
        User* defaultUser = new LengthRecommenderUser("default");
        activeUser=defaultUser;
        userMap["default"]=defaultUser;
    }
    std::cout << "SPLFLIX is now on!"  << std::endl;
    std::string userCommand;
    while (userCommand!="exit"){
        std::cin>>userCommand;
        if (userCommand=="createuser"){act(new CreateUser);}
        else if (userCommand=="changeuser"){act(new ChangeActiveUser());}
        else if (userCommand=="deleteuser"){act(new DeleteUser());}
        else if (userCommand=="dupuser"){act(new DuplicateUser());}
        else if (userCommand=="content"){act(new PrintContentList());}
        else if (userCommand=="watchhist"){act(new PrintWatchHistory());}
        else if (userCommand=="watch"){act(new Watch());}
        else if (userCommand=="log"){act(new PrintActionsLog());}
        else if (userCommand=="exit"){act(new Exit());}
        else{std::cin.clear();
            std::cout <<"command doesn't exist" << std::endl;}
        }

        }

const std::vector<Watchable *> &Session::getContent() const {
    return content;
}

const std::vector<BaseAction *> &Session::getActionsLog() const {
    return actionsLog;
}

const std::unordered_map<std::string, User *> &Session::getUserMap() const {
    return userMap;
}

User *Session::getActiveUser() const {
    return activeUser;
}

void Session::act(BaseAction *action) {
    action->act(*this);
    actionsLog.push_back(action);
}

void Session::insertNewUser(User *toInsert, std::string &name) {
    userMap[name]=toInsert;
}

void Session::changeActiveUser(std::string &name) {
    activeUser=userMap[name];
}

void Session::deleteUser(std::string &name) {
    User* a = (userMap[name]);
    userMap.erase(name);
    delete a;
}

void Session::dupuser(std::string &oldName, std::string &newName) {
    User* toInsert = userMap[oldName]->copy();
    toInsert->setName(newName);
    userMap[newName]=toInsert;
}

void Session::clear() {
    {
        activeUser= nullptr;
        for (const auto &item : content) {
            delete item;
        }
        content.clear();
        for (const auto &item1 : actionsLog) {
            delete item1;
        }
        actionsLog.clear();
        for (const auto &item3 : userMap) {
            delete item3.second;
        }
        actionsLog.clear();
}
}



