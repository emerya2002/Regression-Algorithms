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
    void print_vector(const std::vector<T> &vec)
    {
        std::cout << "[";
        for (long unsigned int i = 0; i < vec.size() - 1; ++i)
        {
            std::cout << vec[i] << ", ";
        }
        std::cout << vec[vec.size() - 1] << "]" << std::endl;
    }

    // Moves `test_amount` random entries from train_data into test_data
    void splitData(
        std::pair<std::vector<std::string>, std::vector<float> > &train_data,
        std::pair<std::vector<std::string>, std::vector<float> > &test_data,
        int test_amount);

} // namespace util

#endif
