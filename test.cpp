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


    User* hedi=new LengthRecommenderUser("hedi");
    User* zisling =hedi->copy();
    if (dynamic_cast<LengthRecommenderUser*>(zisling)!= nullptr){
        std::cout <<"it work" << std::endl;

    }
//    std::vector<std::string> *b = new std::vector<std::string>;
//
//    b->push_back("asd");
//    b->push_back("ebebjssdf");
//    Watchable *ter = new Movie(56, "Drac", 56, *b);
//    Movie *TERERR = new Movie(99, "LOL", 77, *b);
//    Movie *lala=new Movie(99,"LOL",77,*b);
//    Episode *tam=new Episode(12,"wtf",12,12,13,*b);
//    Episode *toto=new Episode(12,"wtf",12,12,13,*b);
//    *TERERR=std::move(*lala);
//    *toto=std::move(*tam);
//    *TERERR = *tam;
//
//
//    delete ter;
//    delete TERERR;

//    delete b;
//
//
//    Session s("/home/zisling/CLionProjects/splflix/config1.json");
//    s.start();
//    s.getActiveUser();
//    Session r(s);

//    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
//
//    std::cout << "Took " << duration << " seconds" << '\n';
}





  /*  JsonReader *a = new JsonReader("/home/zisling/CLionProjects/splflix/config2.json");
    while (!a->isEmpty()){
        std::cout <<a->getType() << std::endl;
        std::cout <<a->getName() << std::endl;
        a->nextWatchable();
    }
    delete a;*/






