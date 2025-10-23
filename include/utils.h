#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <random>

namespace Utils {
    
    int generateID();

   
    double randomDouble(double min, double max);

    
    bool chance(double probability);

    
    std::string currentDateTime();
}

#endif 
