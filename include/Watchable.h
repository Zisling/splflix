#ifndef WATCHABLE_H_
#define WATCHABLE_H_

#include <string>
#include <vector>


class Session;
/**
 *
 *
 * Watchable
 *
 *
 */
class Watchable{
public:
    //Constructors//
    Watchable(long id, int length, const std::vector<std::string>& tags);
    //Copy Constructor
    Watchable(const Watchable& other);
    //Move Constructor
    Watchable(Watchable &&other);
    //Copy Assignment Operator
    Watchable&operator=(const Watchable& other);
    //Move Assignment Operator
    Watchable&operator=(Watchable &&other);

    //Destructor
    virtual ~Watchable();

    //copy
    virtual Watchable* copy()=0;
    //steal
    virtual Watchable* steal()=0;

    //Getters
    const long getId() const;
    int getLength() const;
    const std::vector<std::string> &getTags() const;

    //Setters
    void setLength(int length);
    void setTags(const std::vector<std::string> &tags);


    virtual std::string toString() const = 0;
    virtual Watchable* getNextWatchable(Session&) const = 0;
    virtual std::string getName() const=0;

private:
    const long id;
    int length;
    std::vector<std::string> tags;

};

/**
 *
 *
 * Movie
 *
 *
 */

class Movie : public Watchable{
public:
    //Constructors
    Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags);
    //Copy Constructor
    Movie(const Movie &other);
    //Move Constructor
    Movie(Movie &&other);


    //Move Assignment Operator
    Movie&operator=(Movie &&other);

    //Copy Assignment Operator
    Movie&operator=(const Movie& other);

    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;
    virtual std::string getName() const override ;

    //copy
    virtual Watchable* copy();

    Watchable *steal() override;


private:
    std::string name;
};

/***
 *
 * Episode
 *
 *
 ***/
class Episode: public Watchable{
public:

    //Constructors
    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags);
    //Copy Constructor
    Episode(const Episode &other);
    //Move Constructor
    Episode(Episode &&other);


    //Copy Assignment Operator
    Episode&operator=(const Episode &other);

    //Move Assignment Operator
    Episode&operator=(Episode &&other);

    //copy
    virtual Watchable* copy();

    //Methods
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;
    virtual std::string getName() const override ;

    void setNextEpisodeId(long nextEpisode);

    Watchable *steal() override;

private:
    std::string seriesName;
    int season;
    int episode;
    long nextEpisodeId;
};

#endif
