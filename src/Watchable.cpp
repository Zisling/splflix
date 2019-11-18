//
// Created by zisling on 17/11/2019.
//
#include "include/Watchable.h"

Watchable::Watchable(long id, int length, const std::vector<std::string> &tags):id(id),length(length){
this->tags=tags;
}

Watchable::~Watchable() {
tags.clear();
}



Movie::Movie(long id, const std::string &name, int length, const std::vector<std::string> &tags):Watchable(id,length,tags),name(name) {

}

std::string Movie::toString() const {
    return std::string();
}

std::string Movie::toString(bool print_full) const {
    return name;
}


Watchable *Movie::getNextWatchable(Session &) const {
    return nullptr;
}

Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,
                 const std::vector<std::string> &tags):Watchable(id,length,tags),seriesName(seriesName),season(season),episode(episode) {

}

std::string Episode::toString(bool print_full) const {
    return seriesName+" S"+std::to_string(season)+"E"+std::to_string(episode);
}

Watchable *Episode::getNextWatchable(Session &) const {
    return nullptr;
}

std::string Episode::toString() const {
    return std::string();
}
