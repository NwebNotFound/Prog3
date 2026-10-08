#ifndef ANALYZE_H
#define ANALYZE_H

#include <string>
#include <cmath>
inline int analyze(int value) {
    if (value == 0) return 1;
    
    int count = (value < 0) ? 1 : 0;
    long long temp = std::abs(static_cast<long long>(value));
    
    while (temp > 0) {
        count++;
        temp /= 10;
    }
    return count;
}

inline int analyze(const std::string& str) {
    return static_cast<int>(str.size());
}

inline int analyze(const char* str) {
    int count = 0;
    while (str[count] != '\0') {
        count++;
    }
    return count;
}

#endif // ANALYZE_H