#pragma once

#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <memory>
#include <cmath>
#include <list>
#include <functional>
#include <cstring>

#define windowWidth 960
#define windowHeight 720

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
   return dynamic_cast<const Base*>(ptr) != nullptr;
}

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 3)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}