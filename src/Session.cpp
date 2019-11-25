#include "include/json.hpp"
#include "include/Session.h"
#include <iostream>
#include <fstream>
#include <include/Watchable.h>

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
    std::vector<std::string> *tags= new std::vector<std::string>;
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
                std::vector<int> *seasons= new  std::vector<int>;
//                crate tags vector
                for (const auto &item1 : value["tags"]) {
                    tags->push_back(item1);
                }
//                crate a vector for the amount of episode per season
                for (const auto &item1 : value["seasons"]) {
                    seasons->push_back(item1);
                }
//                crate the obj and push to content
                for (int i = 1; i < seasons->size()+1; ++i) {
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
//Session Copy Constructor
//TODO:
Session::Session(const Session &otherSess){
this->content.reserve(otherSess.content.size());
    for (const auto &otherContent : otherSess.content) {
            Watchable *toEmplace=otherContent->copy();
            this->content.emplace_back(toEmplace);}
        }


//Session Destructor
Session::~Session() {
    activeUser= nullptr;
    for (const auto &item : content) {
        delete item;
    }
    for (const auto &item1 : actionsLog) {
        delete item1;
    }
    for (const auto &item3 : userMap) {
        delete item3.second;
    }
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
    std::cout <<action->toString() << std::endl;
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



