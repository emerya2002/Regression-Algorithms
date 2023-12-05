#include "LinearRegression.h"
#include "LogisticRegression.h"
#include "Parser.h"
#include "Util.h"
#include <iostream>
#include <fstream>

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

int main(int argc, char *argv[]) {
    // test_headers();
    // verify_data();

    // TODO: Add command line arguments to pick a certain stock/variable

    // TODO: Read Data for selected stock and variable

    // TODO: Randomly Split up data into train (95%) and test(5%) vectors for each

    // TODO: Train Linear and Logistic Regression models using 95% of dataset

    // Testing out linear regression
    std::string data_file1 = "data/stocks/sample.csv";
    std::string data_file2 = "data/variables/sample.csv";

    std::pair<std::vector<std::string>, std::vector<float> > result1 = parser::parse_csv(data_file1);
    std::pair<std::vector<std::string>, std::vector<float> > result2 = parser::parse_csv(data_file2);

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

    // TODO: Test model predictions using 5% of dataset

    return 0;
}
