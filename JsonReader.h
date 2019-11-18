//
// Created by zisling on 18/11/2019.
//

#ifndef SPLFLIX_JSONREADER_H
#define SPLFLIX_JSONREADER_H

#include <iostream>
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;


class JsonReader {
public:
    JsonReader(const std::string& path);

    virtual ~JsonReader();


    const json &getJ() const;

    const std::string &getType() const;

    const std::string &getName() const;

    int getLength() const;

    int getEpisodeLength() const;

    const std::vector<int> &getSeasons() const;

    const std::vector<std::string> &getTags() const;

    bool isEmpty();

    void nextWatchable();


private:
    json j_;
    json::value_type i_;
    std::string type_;
    std::string name_;
    int length_;
    int episode_length_;
    bool empty_;
    std::vector<int > *seasons_;
    std::vector<std::string> *tags_;
    json::iterator type_iterator_;
    json::iterator watchable_iterator_;
    void push_next();
    void clean();
};


#endif //SPLFLIX_JSONREADER_H
