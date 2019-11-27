#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
class Watchable;
class Session;
#include "../include/Session.h"

struct tagCountPair{
private:
    int m_count;
    std::string m_tag;
public:
    tagCountPair(int count,std::string tag);
    const int getCount() const;
    const std::string getTag() const;
    void setCount(int);
};

struct tagCountPairComprator{
    bool operator ()(const tagCountPair &tagPair1, const tagCountPair &tagPair2);
};
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
    User&operator=(const User&);

    //User Move Assignment Operator
    User&operator=(User&&);


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
//    copy constructor
    LengthRecommenderUser(const LengthRecommenderUser& other);
//    move constructor
    LengthRecommenderUser(LengthRecommenderUser&& other);
//    copy assigment
    LengthRecommenderUser&operator=(const LengthRecommenderUser&other);
//    move assigment
    LengthRecommenderUser&operator=(LengthRecommenderUser&&);
private:
    double avg;

};

class RerunRecommenderUser : public User {
public:
    RerunRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
    virtual  User* copy();
//    copy constructor
    RerunRecommenderUser(const RerunRecommenderUser& other);
//    move constructor
    RerunRecommenderUser(RerunRecommenderUser&& other);
//    copy assigment
    RerunRecommenderUser&operator=(const RerunRecommenderUser&other);
//    move assigment
    RerunRecommenderUser&operator=(RerunRecommenderUser&&);
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
      std::vector<tagCountPair> tagCountVector;
};

#endif
