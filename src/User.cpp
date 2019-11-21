

#include <include/User.h>


/**
 *
 *                    User
 *
 */

//User Contructor
User::User(const std::string &name)
:name(name),history() {
}

//User Copy Constructor
User::User(const User &other)
:name(other.name) {
    for (const auto &item : other.history) {
        this->history.push_back(item);
    }
}

//User Move Constructor
User::User(User &&other)
:name(other.name) {
    for (const auto &item : other.history) {
        this->history.push_back(item);
    }
    other.history.clear();
}

//User Copy Assignment Operator
User &User::operator=(User &other) {
    if(this!=&other)
    {
        this->history.clear();
        for (const auto &item : other.history) {
            this->history.push_back(item);
        }
    }
    return *this;
}
//User Move Assignment Operator
User &User::operator=(User &&other) {
    if(this!=&other)
    {
        this->history.clear();
        for (const auto &item : other.history) {
            this->history.push_back(item);
        }
        other.history.clear();
    }
    return *this;
}

//User getName
std::string User::getName() const {
    return name;
}
//User getHistory
std::vector<Watchable *> User::get_history() const {
    return history;
}
//User Destructor
User::~User() {
    for (auto &item : history) {
        delete item;
    }
}


/***
 *
 *                      length_Recommender_User
 *
 *
 *
 * ***/

LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name) ,avg(0){
}

Watchable *LengthRecommenderUser::getRecommendation(Session &s) {
    Watchable *toRecommend = history[history.size() - 1]->getNextWatchable(s);
    double i = history.size();
    avg = ((avg * (i - 1)) / i) + ((double) (history[history.size() - 1]->getLength()) / i);
    if (toRecommend == nullptr){
        std::unordered_set<Watchable*> search_set(history.begin(),history.end());
        double minLen = std::numeric_limits<double>::max();
        for (const auto &item : s.getContent()) {
            if (std::abs(avg-(double)(item->getLength()))<minLen && search_set.find(item)==search_set.end()){
            minLen=std::abs(avg-item->getLength());
            toRecommend=item;
            }
        }
        search_set.clear();
    }
    return toRecommend;
}




/**
 *
 *              Rerun_Recommender_User
 *
 *
 */
RerunRecommenderUser::RerunRecommenderUser(const std::string &name) : User(name), Index(0) {

}

Watchable *RerunRecommenderUser::getRecommendation(Session &s) {
    Watchable* toRecommend= history[history.size() - 1]->getNextWatchable(s);
    if(toRecommend == nullptr){
        toRecommend = history[Index];
    Index= (Index + 1) % history.size();
    }
    return toRecommend;
}



/**
 *
 *              Genre_Recommender_User
 *
 *
 */


GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name), genreCounterMap() {
}

Watchable *GenreRecommenderUser::getRecommendation(Session &s) {
    Watchable* toRecommend= history[history.size() - 1]->getNextWatchable(s);
    for (const auto &tag : history[history.size()-1]->getTags()) {
        genreCounterMap[tag]++;
    }
    if(toRecommend == nullptr){

    }
    return toRecommend;
}
