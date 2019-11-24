

#include <include/User.h>
#include <limits>
#include <algorithm>




/*
 * TODO
 * add five to all
 * add copy and steal to all
 * clean all comments
 * */

/*TagCountPair::TagCountPair(int count, std::string string) {
    this->count=count;
    this->Tag=std::move(string);
}*/

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
        item= nullptr;
    }
    history.clear();
}

void User::insertToHistory(Watchable *insert) {
    history.emplace_back(insert);
}

void User::PrintHistory() {
    unsigned long id = 0;
    for (const auto &item : history) {
        id++;
        std::cout <<id<<". "<<item->toString() << std::endl;

    }
}

User *User::copy() {
    return nullptr;
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

User *LengthRecommenderUser::copy() {
    return new LengthRecommenderUser(*this);
}

LengthRecommenderUser::LengthRecommenderUser(const LengthRecommenderUser &other):User(other),avg(other.avg) {
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

User *RerunRecommenderUser::copy() {
    return new RerunRecommenderUser(*this);
}

RerunRecommenderUser::RerunRecommenderUser(const RerunRecommenderUser &other):User(other), Index(other.Index){
}


/**
 *
 *              Genre_Recommender_User
 *
 *
 */

GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name),genreCounterMap(),tagSet() {
}

//Todo: search for user most popular tag, with a Tag set to the genreMap
Watchable *GenreRecommenderUser::getRecommendation(Session &s) {
    int maxReturn=0;
    Watchable* toRecommend= history[history.size() - 1]->getNextWatchable(s);
    for (const auto &tag : history[history.size()-1]->getTags()) {

       genreCounterMap[tag]++;
        tagSet.insert(tag);
    }

    if(toRecommend == nullptr){
        //Start of Finding the Tag to Recommend
        std::string tagToRecommend;
        std::string tagPrev;
        for (const auto &item : tagSet) {
            if(maxReturn<(genreCounterMap[item]))
            {
                maxReturn=genreCounterMap[item];
                tagToRecommend=item;
            }
            else if(maxReturn==genreCounterMap[item])
            {
                if(std::string(item)>std::string(tagPrev))
                    tagToRecommend=item;
            }
            tagPrev=item;
        }
        //End of Finding the Tag to Recommend

        //for each watchable in content, checks if watchable has the popular tag, and checks if the watchable is already in the user watch history
        for (const auto &watchable : s.getContent()) {
            if((toRecommend== nullptr)&&std::find(watchable->getTags().begin(),watchable->getTags().end(),tagToRecommend)!=watchable->getTags().end()&std::find(history.begin(),history.end(),watchable)==history.end())
            toRecommend=watchable;
        }

        //toRecommend=content with same genre, if more genres has the same popularity(cardinality) choose by lexicographic order,
        //choose a watchable with same tag that wasn't already watched,->>>Content/history
        //if there is no such content with this genre tag, it will search for the next biggest tag and so on
    }
    return toRecommend;
}

User *GenreRecommenderUser::copy() {
    return new GenreRecommenderUser(*this);
}
//@TODO need a fix to the vectors
GenreRecommenderUser::GenreRecommenderUser(const GenreRecommenderUser &other):User(other),genreCounterMap(other.genreCounterMap),tagSet(other.tagSet) {
}

/*Watchable *GenreRecommenderUser::getRecommendation(Session &s) {
    Watchable* toRecommend= history[history.size() - 1]->getNextWatchable(s);
    int i=0;
    for (const auto &tag : history[history.size()-1]->getTags()) {
        if(std::find(tagCountVector.begin(),tagCountVector.end(),)==tagCountVector.end())
          tagCountVector.emplace_back(TagCountPair(0,tag));
        else
            tagCountVector[i].count++;
        i=0;
    }
    if(!(std::is_sorted(tagCountVector.begin(),tagCountVector.end())))
        std::sort(tagCountVector.begin(),tagCountVector.end());



    if(toRecommend== nullptr)
    {

    }


    return toRecommend;
}*/