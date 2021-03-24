#include <ctime>
#include <sstream>
#include <iostream>


void PrintCurrentTime() {
    std::time_t now = std::time(nullptr);
    std::cout << std::asctime(std::localtime(&now));
}
