

#include <include/User.h>
#include <limits>
#include <algorithm>




/*
 * TODO
 * add five to all
 * add copy and steal to all
 * clean all comments
 * */




tagCountPair::tagCountPair(int count, std::string tag) {
    m_count=count;
    m_tag=tag;
}

const int tagCountPair::getCount() const {
    return m_count;
}

const std::string tagCountPair::getTag() const {
    return m_tag;
}

void tagCountPair::setCount(int count) {
    this->m_count=count;
}

//tagCountPair comprator -compares numerically and then lexiographicly
bool tagCountPairComprator::operator()(const tagCountPair &tagPair1, const tagCountPair &tagPair2) {

        if(tagPair1.getCount()>tagPair2.getCount())
            return true;
        if(tagPair1.getCount()==tagPair2.getCount()) {
            if (tagPair1.getTag() < tagPair2.getTag()) {
                return true;
            }
        }
    return false;
}


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
        delete item;
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

void User::setName(const std::string &name) {
    User::name = name;
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

GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name),genreCounterMap(),tagSet(),tagCountVector() {

}

//Todo: search for user most popular tag, with a Tag set to the genreMap
Watchable *GenreRecommenderUser::getRecommendation(Session &s) {
    Watchable* toRecommend= history[history.size() - 1]->getNextWatchable(s);
    for (const auto &item : s.getContent()) {
        for (const auto &tag : item->getTags()) {
            if(genreCounterMap[tag]==0){
            tagSet.insert(tag);
            genreCounterMap[tag]=0;}
        }

    }
    for (const auto &tag : history[history.size()-1]->getTags()) {
       genreCounterMap[tag]++;
        tagSet.insert(tag);
    }

    tagCountVector.reserve(tagSet.size());

    for (const auto &tag : tagSet) {
        bool toinsert=true;

        for (tagCountPair &item : tagCountVector) {
            if(item.getTag()==tag) {
                toinsert = false;
                item.setCount(genreCounterMap[tag]);
            }
        }
        if(toinsert)
        tagCountVector.emplace_back(tagCountPair(genreCounterMap[tag],tag));
    }
    std::sort(tagCountVector.begin(),tagCountVector.end(),tagCountPairComprator());

    if(toRecommend == nullptr){

        //for each watchable in content, checks if watchable has the popular tag, and checks if the watchable is already in the user watch history
        bool inHistory = true;
        for (int i = 0; i <tagCountVector.size()&toRecommend== nullptr&inHistory ; ++i) {
            for (int k = 0 ; k<s.getContent().size()&inHistory; ++k) {
                const auto content = s.getContent()[k];
                for (const auto &item : content->getTags()) {
                    if (tagCountVector[i].getTag()==item){
                        bool tmp = false;
                        for (int j = 0; j < history.size()&&!tmp; ++j) {
                            if (history[j]->toString()==content->toString()){
                                tmp= true;
                            }}
                            if (!tmp){
                                toRecommend=content;
                                inHistory= false;}
                    }
                }
            }
        }

//        for (const auto &watchable : s.getContent()) {
//            if((toRecommend== nullptr)&&std::find(watchable->getTags().begin(),watchable->getTags().end(),(tagCountVector[0].getTag()))!=watchable->getTags().end()&std::find(history.begin(),history.end(),watchable)==history.end())
//            toRecommend=watchable;
//        }

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
