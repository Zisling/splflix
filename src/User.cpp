

#include <include/User.h>
#include <iostream>
#include "algorithm"

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
    for (auto &item : history) {
        delete item;
    }

}

/***lengthRecommder***/
LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name) ,avg(0){
}

Watchable *LengthRecommenderUser::getRecommendation(Session &s) {
    Watchable *toRecommend = history[history.size() - 1]->getNextWatchable(s);
    if (toRecommend == nullptr){
        double i = history.size();
        avg = ((avg * (i - 1)) / i) + ((double) (history[history.size() - 1]->getLength()) / i);
        double minLen = std::numeric_limits<double>::max();
        for (const auto &item : s.getContent()) {
            if (std::abs(avg-(double)(item->getLength()))<minLen && std::find(history.begin(),history.end(),item)==history.end()){
            minLen=std::abs(avg-item->getLength());
            toRecommend=item;
            }
        }
}
    return toRecommend;
}



/***
 *rerun
 ***/
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
/***
 *genreRecommender
 ***/
GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name) {

}

Watchable *GenreRecommenderUser::getRecommendation(Session &s) {
    return nullptr;
}
