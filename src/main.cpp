#include "LinearRegression.h"
#include "LogisticRegression.h"
#include "Parser.h"
#include "Util.h"
// #include <iostream>

void test_headers() {
    // Verifies that all header files are linked properly
    // should all print hello with filename.
    linear_regression::test();
    logistic_regression::test();
    parser::test();
    util::test();
}

int main() {
    test_headers();

    // TODO: Add command line arguments to pick a certain stock/variable

    // Testing out parser
    std::string data_file1 = "data/stocks/sample.csv";
    std::string data_file2 = "data/variables/sample.csv";

    std::pair<std::vector<std::string>, std::vector<float> > result1 = parser::parse_csv(data_file1);
    std::pair<std::vector<std::string>, std::vector<float> > result2 = parser::parse_csv(data_file2);

    std::cout << "RESULT1" << std::endl;
    util::print_vector(result1.first);
    util::print_vector(result1.second);
    std::cout << "RESULT2" << std::endl;
    util::print_vector(result2.first);
    util::print_vector(result2.second);

    return 0;
}
