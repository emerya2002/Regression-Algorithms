#include "LinearRegression.h"
#include "LogisticRegression.h"
#include "Parser.h"
#include "Util.h"
#include <iostream>
#include <fstream>
#include <utility>

#define NUM_DAYS 100 // Number of rows in each csv within data
#define TEST_AMOUNT 5 // Number of rows that would be used for testing

// Verifies that all header files are linked properly
// should all print hello from filename.
void test_headers() {
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
    // Pick a certain stock/variable based on command line arguments
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <stock_name> <variable_name>" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Read in Data for selected stock and variable
    std::string stock_name = argv[1];
    std::string variable_name = argv[2];

    std::string stock_file = "data/stocks/" + stock_name + ".csv";
    std::string variable_file = "data/variables/" + variable_name + ".csv";

    std::pair<std::vector<std::string>, std::vector<float> > stock_data = parser::parse_csv(stock_file);
    std::pair<std::vector<std::string>, std::vector<float> > variable_data = parser::parse_csv(variable_file);
    // Verify data is complete and of equal length
    if (stock_data.first.size() != NUM_DAYS || variable_data.first.size() != NUM_DAYS)
    {
        std::cerr << "Error: Data size mismatch" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Randomly Split up data into train (95%) and test(5%) vectors for each
    auto stock_data_test = std::make_pair(std::vector<std::string>(), std::vector<float>());
    auto variable_data_test = std::make_pair(std::vector<std::string>(), std::vector<float>());
    util::splitData(stock_data, stock_data_test, TEST_AMOUNT);
    util::splitData(variable_data, variable_data_test, TEST_AMOUNT);

    // TODO: Train Linear and Logistic Regression models using 95% of dataset

    std::cout << "** Testing Linear ** " << std::endl;
    linear_regression::LinearRegression linearModel(variable_data.second, stock_data.second);

    // opening linear output file
    std::ofstream linear_outputFile("LinearPredictions.txt");
    std::cout << "Linear Predictions outputted to output file **" << std::endl;

    // TODO: log error rate between prediction and actual price, with total error
    linear_outputFile << "Predictions: " << std::endl;
    for (float x : variable_data_test.second)
    {
        linear_outputFile << "Prediction for x = " << x << ": " << linearModel.prediction(x) << std::endl;
    }

    linear_outputFile.close();

    // Testing out logistic regression
    std::cout << "** Testing Logistic **" << std::endl;
    logistic_regression::LogisticRegression logisticModel(variable_data.second, stock_data.second);

    // opening linear output file
    std::ofstream logistic_outputFile("LogisticPredictions.txt");
    std::cout << "Logistic Predictions outputted to output file **" << std::endl;

    // TODO: log error rate between prediction and actual price, with total error
    logistic_outputFile << "Predictions: " << std::endl;
    for (float x : variable_data_test.second)
    {
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
