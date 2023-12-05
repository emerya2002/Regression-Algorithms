#include "LinearRegression.h"
#include "LogisticRegression.h"
#include "Parser.h"
#include "Util.h"
#include <iostream>
#include <fstream>

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

    // Testing out linear regression
    std::cout << "** Testing Linear ** " << std::endl;
    linear_regression::LinearRegression linearModel(result1.second, result2.second);

    // opening linear output file
    std::ofstream linear_outputFile("LinearPredictions.txt");
    std::cout << "Linear Predictions outputted to output file **" << std::endl;

    linear_outputFile << "Predictions: " << std::endl;
    for(float x : result1.second) {
        linear_outputFile << "Prediction for x = " << x << ": " << linearModel.prediction(x) << std::endl;
    }

    linear_outputFile.close();
    
    // Testing out logistic regression
    std::cout << "** Testing Logistic **" << std::endl;
    logistic_regression::LogisticRegression logisticModel(result1.second, result2.second);

    // opening linear output file
    std::ofstream logistic_outputFile("LogisticPredictions.txt");
    std::cout << "Logistic Predictions outputted to output file **" << std::endl;

    logistic_outputFile << "Predictions: " << std::endl;
    for(float x : result1.second) {
        logistic_outputFile << "Prediction for x = " << x << ": " << logisticModel.prediction(x) << std::endl;
    }

    logistic_outputFile.close();

    /*
    std::cout << "RESULT1" << std::endl;
    util::print_vector(result1.first);
    util::print_vector(result1.second);
    std::cout << "RESULT2" << std::endl;
    util::print_vector(result2.first);
    util::print_vector(result2.second);
    */


    return 0;
}
