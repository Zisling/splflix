#include "json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;
template<class UnaryFunction>
void recursive_iterate(const json& j, UnaryFunction f) {
    for (auto it = j.begin(); it != j.end(); ++it) {
        if (it->is_structured()) {
            recursive_iterate(*it, f);
        } else {
            f(it);
        }
    }
}
int main() {
    std::ifstream f("/home/zisling/CLionProjects/splflix/config1.json");
    json j;
    f>>j;
//    recursive_iterate(j,[](json::const_iterator it){
//        std::cout <<*it << std::endl;
//
//    });
    std::cout <<j.is_structured() << std::endl;
    for (const json &item : j) {
        std::cout << item.is_structured() << std::endl;
        for (const auto &item2 : item) {
                std::cout <<item2["name"] << std::endl;
                std::cout <<item2["tags"] << std::endl;
        }

    }

}