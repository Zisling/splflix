

#include <include/User.h>
#include <iostream>


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
    history.clear();
}


/***
 *
 *                      length_Recommender_User
 *
 *
 *
 * ***/

LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name) {

}

Watchable *LengthRecommenderUser::getRecommendation(Session &s) {
    return nullptr;
}


/**
 *
 *              Rerun_Recommender_User
 *
 *
 */
RerunRecommenderUser::RerunRecommenderUser(const std::string &name) : User(name) {

}

Watchable *RerunRecommenderUser::getRecommendation(Session &s) {
    return history[0];
}



/**
 *
 *              Genre_Recommender_User
 *
 *
 */


GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name) {

}

Watchable *GenreRecommenderUser::getRecommendation(Session &s) {
    return nullptr;
}
