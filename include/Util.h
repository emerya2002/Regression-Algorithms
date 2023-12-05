// Utility functions that could be shared between both regression files
#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <iostream>

namespace util
{

    // Declare test function
    void test();

    // Prints a vector in the form "[a, b, ..., y, z]"
    template <typename T>
    void print_vector(const std::vector<T> &vec);

} // namespace util

#endif
