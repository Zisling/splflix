#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
class Watchable;
class Session;
#include "include/Session.h"
class User{
public:
    //User Constructor
    User(const std::string& name);

    //User Copy Constructor
    User(const User& other);

    //User Move Constructor
    User(User&& other);

    //User Copy Assignment Operator
    virtual User&operator=(User&);

    //User Move Assignment Operator
    virtual User&operator=(User&&);


    virtual Watchable* getRecommendation(Session& s) = 0;

    std::string getName() const;
    std::vector<Watchable*> get_history() const;

    //User Destructor
    virtual ~User();

protected:
    std::vector<Watchable*> history;
private:
    const std::string name;
};


class LengthRecommenderUser : public User {
public:
    LengthRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
private:
    double avg;

};

class RerunRecommenderUser : public User {
public:
    RerunRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
private:
    unsigned long Index;
};

class GenreRecommenderUser : public User {
public:
    GenreRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
private:
};

#endif
