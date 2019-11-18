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
    Watchable(const Watchable& other);
    //Copy Assignment Operator
    void operator=(const Watchable& other);

    //Destructor
    virtual ~Watchable();

    //Getters
    const long getId() const;
    int getLength() const;
    const std::vector<std::string> &getTags() const;


    virtual std::string toString() const = 0;
    virtual Watchable* getNextWatchable(Session&) const = 0;
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
    Movie(const Movie &other);

    virtual std::string toString(bool print_full=false) const;
    virtual Watchable* getNextWatchable(Session&) const;

    std::string toString() const override;

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
    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags);
    virtual std::string toString(bool print_full=false) const;
    virtual Watchable* getNextWatchable(Session&) const;

    std::string toString() const override;

private:
    std::string seriesName;
    int season;
    int episode;
    long nextEpisodeId;
};

#endif
