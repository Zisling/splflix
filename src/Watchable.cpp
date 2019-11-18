//
// Created by zisling on 17/11/2019.
//
#include "include/Watchable.h"


/***
 * Watchable
 ***/
//Watchable Constructor
Watchable::Watchable(long id, int length, const std::vector<std::string> &tags):id(id),length(length){
this->tags=tags;
}
//Watchable Copy Constructor
Watchable::Watchable(const Watchable &other):id(other.id),length(other.length) {

    for(const auto & item : other.tags)
    {
        tags.push_back(item);
    }

}
//Watchable Copy Assignment Operator
void Watchable::operator=(const Watchable &other) {
    length=other.length;
    tags.clear();
    for (const auto &item : other.tags) {
        tags.push_back(item);
    }
}


Watchable::~Watchable() {
tags.clear();
}

const long Watchable::getId() const {
    return id;
}

int Watchable::getLength() const {
    return length;
}

const std::vector<std::string> &Watchable::getTags() const {
    return tags;
}





/*
 *Movies
 */
//Constructors
Movie::Movie(long id, const std::string &name, int length, const std::vector<std::string> &tags):Watchable(id,length,tags),name(name) {

}

//Copy Constructor
Movie::Movie(const Movie &other):Watchable(other.getId(),other.getLength(),other.getTags()) {
    name=other.name;
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

/*
 * Episode
 */

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
