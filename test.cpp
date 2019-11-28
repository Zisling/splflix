#include "include/Session.h"
#include "include/json.hpp"
#include <iostream>
#include "include/Watchable.h"
#include "include/Action.h"
#include <cstdio>
#include <ctime>
using json = nlohmann::json;

int main() {


    std::clock_t start;
    double duration;

    start = std::clock();


//    std::vector<std::string> *b = new std::vector<std::string>;
//
//    b->push_back("asd");
//    b->push_back("ebebjssdf");
//    Watchable *ter = new Movie(56, "Drac", 56, *b);
//    Watchable *TERERR = new Movie(99, "LOL", 77, *b);
//    Watchable *lala=new Movie(99,"LOL",77,*b);
//    Watchable *tam=new Episode(12,"wtf",12,12,13,*b);
//    Watchable *toto=new Episode(12,"wtf",12,12,13,*b);
//    *TERERR=std::move(*lala);
//    *toto=std::move(*tam);
//    *TERERR = *tam;
//    Watchable *re =TERERR->steal();

//    Session sess9("/home/zisling/CLionProjects/splflix/config2.json");
//    sess9.start();
//    Session y=Session(sess9);
//    for(int i=0;i<9999;i++)
//    y=sess9;
//    Session a=std::move(sess9);
//    y=std::move(a);

    auto *a =new GenreRecommenderUser("hedi");
    auto *b =new GenreRecommenderUser("zisling");
    GenreRecommenderUser* c = new GenreRecommenderUser(*a);
    GenreRecommenderUser* d = new GenreRecommenderUser(std::move(*b));
    *c = *d;
    *c =std::move(*a);

    delete a;
    delete b;
    delete c;
    delete d;




    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;


    std::cout << "Took " << duration << " seconds" << '\n';
}











