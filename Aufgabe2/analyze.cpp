#include "analyze.h"
#include <cstring>
#include <iterator>

int analyze(int number){
    int count = (number <= 0) ? 1 : 0;

    while (number != 0){
        number /= 10;
        count++;
    }

    return count;
}

int analyze(const char* text){
    return std::strlen(text);
}

int analyze(const std::string& text){
    return text.size();
}