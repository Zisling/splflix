#include "json.hpp"
#include <iostream>
#include <fstream>
#include "JsonReader.h"

using json = nlohmann::json;

int main() {


//    std::vector<std::string> a;
//    std::vector<std::string> q;
//    std::ifstream f("/home/zisling/CLionProjects/splflix/config1.json");
//    json j;
//    f>>j;
//    json::iterator b = j.begin();
//    json::value_type c;
//    if(b.key()=="movies"){
//        if (b.value().is_structured()){
//            c=b.value();
//        }
//        json::iterator p = (c.begin());
//        std::cout <<(*p)["name"] << std::endl;
//}
    JsonReader *a = new JsonReader("/home/zisling/CLionProjects/splflix/config1.json");
    while (!a->isEmpty()){
        std::cout <<a->getType() << std::endl;
        std::cout <<a->getName() << std::endl;
        a->nextWatchable();
    }
    delete a;

}





