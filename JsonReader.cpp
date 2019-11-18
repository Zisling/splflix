//
// Created by zisling on 18/11/2019.
//

#include "JsonReader.h"

#include <utility>

JsonReader::JsonReader(const std::string& path):tags_(new std::vector<std::string>),seasons_(new std::vector<int>),empty_(false) {
    std::ifstream f(path);
    f>>j_;
    type_iterator_ = j_.begin();
    i_=type_iterator_.value();
    watchable_iterator_= i_.begin();
    type_=type_iterator_.key();
    nextWatchable();


}

JsonReader::~JsonReader() {
    delete seasons_;
    delete tags_;
}


const json &JsonReader::getJ() const {
    return j_;
}

const std::string &JsonReader::getType() const {
    return type_;
}

const std::string &JsonReader::getName() const {
    return name_;
}

int JsonReader::getLength() const {
    return length_;
}

int JsonReader::getEpisodeLength() const {
    return episode_length_;
}

const std::vector<int> &JsonReader::getSeasons() const {
    return *seasons_;
}

const std::vector<std::string> &JsonReader::getTags() const {
    return *tags_;
}

void JsonReader::nextWatchable() {
        clean();
        type_=type_iterator_.key();
        if (type_.empty()){empty_=true;}
        if(type_=="movies"){
            name_=(*watchable_iterator_)["name"];
            length_=(*watchable_iterator_)["length"];
            for (const auto &item : (*watchable_iterator_)["tags"]) {
                tags_->push_back(item);
            }
        }
        else if(type_=="tv_series"){
            name_=(*watchable_iterator_)["name"];
            episode_length_=(*watchable_iterator_)["episode_length"];
            for (const auto &item : (*watchable_iterator_)["tags"]) {
                tags_->push_back(item);
            }
            for (const auto &item : (*watchable_iterator_)["seasons"]) {
                seasons_->push_back(item);
            }
        }
        push_next();

}

void JsonReader::push_next() {
    ++watchable_iterator_;
    if (watchable_iterator_ == i_.end()){
        ++type_iterator_;
        if (type_iterator_ != j_.end()) {
            i_=type_iterator_.value();
            watchable_iterator_ = i_.begin();
        }
    }
}

bool JsonReader::isEmpty() {
    return empty_;
}

void JsonReader::clean() {
    tags_->clear();
    seasons_->clear();
    episode_length_=-1;
    length_=-1;
    name_="";
}
