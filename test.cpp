#include "json.hpp"
#include <iostream>
#include <fstream>
#include "JsonReader.h"
#include "include/Watchable.h"
using json = nlohmann::json;

int main() {
    std::vector<std::string> *b= new std::vector<std::string>;

    b->push_back("asd");
    b->push_back("ebebjssdf");
    Watchable *ter = new Movie(56,"ter",56,*b);


    JsonReader *a = new JsonReader("/home/zisling/CLionProjects/splflix/config2.json");
    while (!a->isEmpty()){
        std::cout <<a->getType() << std::endl;
        std::cout <<a->getName() << std::endl;
        a->nextWatchable();
    }
    delete a;

}





