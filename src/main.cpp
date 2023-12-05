#include "LinearRegression.h"
#include "LogisticRegression.h"
#include "Parser.h"
#include "Util.h"
// #include <iostream>

#define NUM_DAYS 100 // Number of rows in each csv within data

void test_headers() {
    // Verifies that all header files are linked properly
    // should all print hello with filename.
    linear_regression::test();
    logistic_regression::test();
    parser::test();
    util::test();
}

void verify(std::string folder, std::vector<std::string> filenames) {
    std::cout << "--" <<  folder << "--" << std::endl;
    for (auto f : filenames)
    {
        std::string file_name = "data/" + folder + "/" + f + ".csv";
        std::pair<std::vector<std::string>, std::vector<float> > result = parser::parse_csv(file_name);
        std::cout << f << ": ";
        if (result.first.size() == NUM_DAYS && result.second.size() == NUM_DAYS)
        {
            std::cout << "Data ok - " << NUM_DAYS << " rows" << std::endl;
        }
        else
        {
            std::cerr << "Data bad - rows must equal " << NUM_DAYS << " rows" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

// Verifies all stocks and variables are complete (exactly NUM_DAYS days of data)
void verify_data()
{
    std::vector<std::string> stocks = {"apple", "boeing", "intel", "nike", "walmart"};
    verify("stocks", stocks);
    std::vector<std::string> variables = {"inflation", "interest", "unemployment"};
    verify("variables", variables);
}

int main() {
    // test_headers();
    // verify_data();

    // TODO: Add command line arguments to pick a certain stock/variable

    return 0;
}
