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


    std::vector<std::string> *b = new std::vector<std::string>;

    b->push_back("asd");
    b->push_back("ebebjssdf");
    Watchable *ter = new Movie(56, "Drac", 56, *b);
    Watchable *TERERR = new Movie(99, "LOL", 77, *b);
    Watchable *lala=new Movie(99,"LOL",77,*b);
    Watchable *tam=new Episode(12,"wtf",12,12,13,*b);
    Watchable *toto=new Episode(12,"wtf",12,12,13,*b);
//    *TERERR=std::move(*lala);
//    *toto=std::move(*tam);
    *TERERR = *tam;
    Watchable *re =TERERR->steal();

    Session s("/home/nir/CLionProjects/splflix/config2.json");
    s.start();
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;


    std::cout << "Took " << duration << " seconds" << '\n';
}











