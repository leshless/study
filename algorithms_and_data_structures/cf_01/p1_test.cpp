#include <iostream>
#include <vector>

#include "list.h"

int main() {
    auto list = List();
    std::cout << list.head << " " << list.tail << std::endl;

    list.push_back(1);
    std::cout << list.head << " " << list.tail << std::endl;

    list.push_back(2);
    std::cout << list.head << " " << list.tail << std::endl;
    
    std::cout << list.empty() << std::endl;
}