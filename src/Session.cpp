#include "include/json.hpp"
#include "include/Session.h"
#include <iostream>
#include <fstream>
#include <include/Watchable.h>

using json = nlohmann::json;


Session::Session(const std::string &configFilePath):userMap() ,actionsLog(),activeUser(nullptr) {
//    id counter
    int count = 1;
//    init of json read file
    std::ifstream f(configFilePath);
    json myJson;
    f >> myJson;
//    loop on the type of content
    for (const auto &item : myJson.items()) {
//        crate movie obj and puse into content
        if (item.key()=="movies"){
            for (const auto &value : item.value()) {
                std::string name= value["name"];
                int length = value["length"];
//                crate a vector for the tags
                std::vector<std::string> *tags= new std::vector<std::string>;
                for (const auto &item1 : value["tags"]) {
                    tags->push_back(item1);
                }
//                push the new obj into content
                Watchable *toPush =new Movie(count,name,length,*tags);
                content.push_back((toPush));
                count++;
                delete tags;
            }
            }
//        crate episode obj
        if (item.key()=="tv_series"){
            for (const auto &value : item.value()) {
                std::string name= value["name"];
                int episode_length = value["episode_length"];
                std::vector<int> *seasons= new  std::vector<int>;
                std::vector<std::string> *tags= new std::vector<std::string>;
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
                delete tags;
            }
        }

        }

    }

Session::~Session() {
    for (const auto &item : content) {
        delete item;
    }for (const auto &item : userMap) {
        delete item.second;
    }for (const auto &item : actionsLog) {
        delete item;
    }
    delete activeUser;

}

void Session::start() {
    std::cout << "SPLFLIX is now on!"  << std::endl;
    std::string userCommand;
    while (userCommand!="exit"){
        std::cin>>userCommand;
        if (userCommand=="createuser"){
            CreateUser *toInsert = new CreateUser();
            toInsert->act(*this);
            actionsLog.push_back(toInsert);
}
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

void Session::insertNewUser(User *toinsert, std::string &name) {
    userMap[name]=toinsert;


}
