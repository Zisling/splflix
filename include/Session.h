#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "../include/Action.h"
#include "../include/json.hpp"


class User;
class Watchable;
#include "../include/User.h"
#include "../include/Watchable.h"
class Session{
public:
//  Constructor
    Session(const std::string &configFilePath);
//  Copy Constructor
    Session(const Session&);
//  Move Constructor
    Session(Session &&other);
//  Copy Assignment operator
    Session&operator=(const Session&);
//  Move Assignment operator
    Session&operator=(Session&& other);

    //clear
    void clear();
//steal
    Session* steal(Session &otherSess);

    ~Session();
    void start();
    Session* copy(const Session &);
    const std::vector<Watchable *> &getContent() const;

    const std::vector<BaseAction *> &getActionsLog() const;

    const std::unordered_map<std::string, User *> &getUserMap() const;

    User *getActiveUser() const;

    void insertNewUser(User *toInsert, std::string &name);
    void changeActiveUser(std::string &name);
    void deleteUser(std::string &name);
    void dupuser(std::string &oldName, std::string &newName);
    void act(BaseAction *action);
    void watch();
    void insertAction(BaseAction *action);
    static bool toRecommend(Watchable* recommend);

private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;

    User* activeUser;
};
#endif
