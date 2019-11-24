#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
class Watchable;
class Session;
#include "include/Session.h"

/*struct TagCountPair
{
    std::string Tag;
    int count;
    TagCountPair(int,std::string);

};*/

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
    void insertToHistory(Watchable* insert);

    //User Destructor
    virtual ~User();
    void PrintHistory();
//    copy function;
    virtual  User* copy()=0;

    void setName(const std::string &name);

protected:
    std::vector<Watchable*> history;
private:
    std::string name;
};


class LengthRecommenderUser : public User {
public:
    LengthRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
    virtual  User* copy();
    LengthRecommenderUser(const LengthRecommenderUser& other);
private:
    double avg;

};

class RerunRecommenderUser : public User {
public:
    RerunRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
    virtual  User* copy();
    RerunRecommenderUser(const RerunRecommenderUser& other);
private:
    unsigned long Index;
};

class GenreRecommenderUser : public User {
public:
    GenreRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
    virtual  User* copy();
    GenreRecommenderUser(const GenreRecommenderUser& other);
private:
    std::unordered_map<std::string,int> genreCounterMap;
    std::unordered_set<std::string> tagSet;
//      std::vector<TagCountPair> tagCountVector;
};

#endif
