#include "include/Session.h"
#include "include/json.hpp"
#include <iostream>
#include "include/Watchable.h"
#include "include/Action.h"
using json = nlohmann::json;

int main() {
    std::vector<std::string> *b= new std::vector<std::string>;
//
    b->push_back("asd");
    b->push_back("ebebjssdf");
    Movie *ter = new Movie(56, "Drac", 56, *b);

    Watchable *teroor = new Movie((*ter));

    std::cout<<teroor->getLength()<<std::endl;

//Session s("/home/zisling/CLionProjects/splflix/config1.json");
//    const std::vector<Watchable*>& cont = s.getContent();
//    for (const auto &item : cont) {
//        std::cout <<item->getId()<< " " << item->getLength()<<item->toString() << std::endl;

    }



  /*  JsonReader *a = new JsonReader("/home/zisling/CLionProjects/splflix/config2.json");
    while (!a->isEmpty()){
        std::cout <<a->getType() << std::endl;
        std::cout <<a->getName() << std::endl;
        a->nextWatchable();
    }
    delete a;*/






