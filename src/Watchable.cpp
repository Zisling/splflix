//
// Created by zisling on 17/11/2019.
//
#include "include/Watchable.h"
#include "iostream"
#include "include/Session.h"

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



//Watchable Copy Assignment Operator
Watchable& Watchable::operator=(const Watchable &other) {
    if(this!=&other) {
        std::cout << "Watchable assign is called" << std::endl;
        length = other.length;
        tags.clear();
        for (const auto &item : other.tags) {
            tags.push_back(item);
        }
    }
    return *this;
}

//Watchable Move Assignment Operator
Watchable &Watchable::operator=(Watchable &&other) {
    if(this != &other)
    {
        this->tags=std::move(other.tags);
//        for(const auto & item : other.tags)
//        {
//            tags.push_back(item);
//        }
        this->length=other.length;
        other.length=0;
//        other.tags.clear();

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
Movie::Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags)
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

//Move Assignment Operator
Movie &Movie::operator=(Movie &&other) {
    if((this!=&other)) {
        this->name = other.name;
        Watchable::operator=(std::move(other));
    }
    return *this;

}

//Copy Assignment Operator
Movie &Movie::operator=(const Movie &other)  {
    if((this!=&other)) {
        Watchable::operator=(other);
        std::cout << "Movie assign is called" << std::endl;
        this->name = other.name;
    }
    return *this;
}

//Movie To String Function
std::string Movie::toString() const {
    return name;
}


//Movie getName Function
std::string Movie::getName() const {
    return name;
}

Watchable *Movie::getNextWatchable(Session &) const {
    return nullptr;
}

Watchable *Movie::copy() {
    return new Movie(*this);
}

Watchable *Movie::steal() {
    return new Movie (std::move(*this));
}



/**
                                     * Episode
 */



//Constructors
Episode::Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags)
                 :Watchable(id,length,tags),seriesName(seriesName),season(season),episode(episode),nextEpisodeId(0) {
}

//Copy Constructor
Episode::Episode(const Episode &other)
:Watchable(other),seriesName(other.seriesName),season(other.season),episode(other.episode),nextEpisodeId(other.nextEpisodeId){
}

//Move Constructor
Episode::Episode(Episode &&other)
:Watchable(std::move(other)),seriesName(other.seriesName),season(other.season),episode(other.episode),nextEpisodeId(other.nextEpisodeId)
{

    other.season=0;
    other.episode=0;
    other.nextEpisodeId=0;

}

//Move Assignment Operator
Episode &Episode::operator=(Episode &&other) {
    if((this!=&other))
    {
        this->seriesName = std::move(other.seriesName);
        this->season=other.season;
        this->episode=other.episode;
        this->nextEpisodeId=other.nextEpisodeId;
        other.season=0;
        other.episode=0;
        other.nextEpisodeId=0;
        Watchable::operator=(std::move(other));
    }
    return *this;
}

//Copy Assignment Operator
Episode &Episode::operator=(const Episode &other) {
    if((this!=&other)) {
        Watchable::operator=(other);
        std::cout << "Episode assign is called" << std::endl;
        seriesName = other.seriesName;
        season = other.season;
        episode = other.episode;
        nextEpisodeId = other.nextEpisodeId;
    }
    return *this;
}


//Episode getName function
std::string Episode::getName() const {
    return seriesName;
}

//Episode getNextWatchable function
Watchable *Episode::getNextWatchable(Session &s) const {
    const std::vector<Watchable*>& vec_Watchables(s.getContent());
    if(vec_Watchables.size()<this->getId()) {
        std::string toCheck = vec_Watchables[this->getId()]->getName();
        if (this->getName() == toCheck) {
            return vec_Watchables[this->getId()];
        }
    }
    else
        return nullptr;

    return nullptr;
}


//Episode To String Function
std::string Episode::toString() const {
    return seriesName+" S"+std::to_string(season)+"E"+std::to_string(episode);
}


Watchable *Episode::copy() {
    return new Episode(*this);
}

Watchable *Episode::steal() {
    return new Episode(std::move(*this));
}
