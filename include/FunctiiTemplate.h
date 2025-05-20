#ifndef FUNCTIITEMPLATE_H
#define FUNCTIITEMPLATE_H

#include <vector>

template <class T>
bool isInVector(std::vector<T> vect, T obj)
{
    return std::find(vect.begin(), vect.end(), obj) != vect.end();
}

#endif