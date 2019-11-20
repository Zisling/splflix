//
// Created by zisling on 17/11/2019.
//
#include "include/Watchable.h"
#include "iostream"

/***
 *              Watchable
 ***/


//Watchable Constructor
Watchable::Watchable(long id, int length, const std::vector<std::string> &tags)
:id(id),length(length){
this->tags=tags;
}
//Watchable Copy Constructor
Watchable::Watchable(const Watchable &other)
:id(other.id),length(other.length) {

    for(const auto & item : other.tags)
    {
        tags.push_back(item);
    }

}
//Watchable Move Constructor
Watchable::Watchable(Watchable &&other)
:id(other.id),length(other.length) {

    for(const auto & item : other.tags)
    {
        tags.push_back(item);
    }

    other.length=0;
    other.tags.clear();

}

//Watchable Move Assignment Operator
Watchable &Watchable::operator=(Watchable &&other) {
    if(this != &other)
    {
        this->tags.clear();
        for(const auto & item : other.tags)
        {
            tags.push_back(item);
        }
        this->length=other.length;
        other.length=0;
        other.tags.clear();

    }
    return *this;
}

//Watchable Copy Assignment Operator
Watchable& Watchable::operator=(const Watchable &other) {
    std::cout<<"Watchable assign is called"<<std::endl;
    length=other.length;
    tags.clear();
    for (const auto &item : other.tags) {
        tags.push_back(item);
    }
    return *this;
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

void Watchable::setLength(int length) {
    Watchable::length = length;
}

void Watchable::setTags(const std::vector<std::string> &tags) {
    Watchable::tags = tags;
}





/**
                                             *Movies
 */


//Constructors
Movie::Movie(long id, int length, const std::vector<std::string> &tags, const std::string &name)
:Watchable(id,length,tags),name(name) {
}

//Copy Constructor
Movie::Movie(const Movie &other)
:Watchable(other),name(other.name) {
}

//Move Constructor
Movie::Movie(Movie &&other)
:Watchable(std::move(other)),name(other.name) {
}

//Movie Assignment Operator
Movie &Movie::operator=(Watchable &&other) {

}

//Copy Assignment Operator
Movie &Movie::operator=(const Watchable &other) {
    Watchable::operator=(other);
    const Movie *pMovie = dynamic_cast<const Movie*>(&other);
    std::cout<<"Movie assign is called"<<std::endl;
    this->name=pMovie->name;
    return *this;
}

std::string Movie::toString() const {
    return name;
}


Watchable *Movie::getNextWatchable(Session &) const {
    return nullptr;
}


/**
                                     * Episode
 */



//Constructors
Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,const std::vector<std::string> &tags)
                 :Watchable(id,length,tags),seriesName(seriesName),season(season),episode(episode),nextEpisodeId(0) {
}

//Copy Constructor
Episode::Episode(const Episode &other)
:Watchable(other),seriesName(other.seriesName),season(other.season),episode(other.episode),nextEpisodeId(other.nextEpisodeId){
}

//Move Constructor
Episode::Episode(Episode &&other):Watchable(std::move(other)),seriesName(other.seriesName),season(other.season),episode(other.episode),nextEpisodeId(other.nextEpisodeId) {

    other.season=0;
    other.episode=0;
    other.nextEpisodeId=0;

}


//Copy Assignment Operator
Episode &Episode::operator=(const Watchable &other) {
    Watchable::operator=(other);
    const Episode *pEpisode = dynamic_cast<const Episode*>(&other);
    std::cout<<"Episode assign is called"<<std::endl;
    seriesName=pEpisode->seriesName;
    season=pEpisode->season;
    episode=pEpisode->episode;
    nextEpisodeId=pEpisode->nextEpisodeId;

    return *this;
}




Watchable *Episode::getNextWatchable(Session &) const {
    return nullptr;
}

std::string Episode::toString() const {
    return seriesName+" S"+std::to_string(season)+"E"+std::to_string(episode);
}



