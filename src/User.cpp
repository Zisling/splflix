

#include <include/User.h>
#include <iostream>

/*User abst*/
User::User(const std::string &name):name(name),history() {

}

std::string User::getName() const {
    return name;
}

std::vector<Watchable *> User::get_history() const {
    return history;
}

User::~User() {
    history.clear();

}

/***lengthRecommder***/
LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name) {

}

Watchable *LengthRecommenderUser::getRecommendation(Session &s) {
    return nullptr;
}

/***
 *rerun
 ***/
RerunRecommenderUser::RerunRecommenderUser(const std::string &name) : User(name) {

}

Watchable *RerunRecommenderUser::getRecommendation(Session &s) {
    return nullptr;
}
/***
 *genreRecommender
 ***/
GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name) {

}

Watchable *GenreRecommenderUser::getRecommendation(Session &s) {
    return nullptr;
}
