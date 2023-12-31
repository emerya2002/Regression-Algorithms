#include "LinearRegression.h"
#include "LogisticRegression.h"
#include "Parser.h"
#include "Util.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <chrono>

#define NUM_DAYS 100 // Number of rows in each csv within data
#define TEST_AMOUNT 5 // Number of rows that would be used for testing (5%)
#define LEARNING_RATE 0.005 // How large each update to the logistic model should be
#define NUM_EPOCHS 20 // Number of times to train the logistic model over training data

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
    // test_headers();

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
    // Store a binary encoding of the testing data to be used to evaluate the
    // logistical model in future. This will let us know if that datapoint
    // was a profit or a loss.
    std::vector<int> stock_encodings_test = util::splitData(stock_data, stock_data_test, TEST_AMOUNT);
    util::splitData(variable_data, variable_data_test, TEST_AMOUNT);

    // get linear runtime
    auto linear_start = std::chrono::high_resolution_clock::now();

    // Train Linear and Logistic Regression models using 95% of dataset
    vector<pair<float, float>> xy_values;
    for (size_t i = 0; i < variable_data.second.size(); ++i) {
        xy_values.push_back(make_pair(variable_data.second[i], stock_data.second[i]));
    }

    cout << "** Testing Linear ** " << endl;
    linear_regression::LinearRegression linearModel(variable_data.second, stock_data.second, xy_values);

    // opening linear output file
    ofstream linear_outputFile("LinearPredictions.txt");
    cout << "Linear Predictions outputted to output file **" << endl;

    // Log error rate between prediction and actual price, with total error
    linear_outputFile << "The best fitting line is y = " << linearModel.showSlope() << "x + " << linearModel.showIntercept() << endl;

    // linear_outputFile << "The mean of xy is " << linearModel.showXY_mean() << ", the sum of xy is " << linearModel.showXY_sum() << endl;
    linear_outputFile << endl << "Predictions: " << endl;
    float error = 0;
    float total = 0;
    for (int i = 0; i < variable_data_test.second.size(); i++)
    {
        float x = variable_data_test.second[i];
        float prediction = linearModel.prediction(x);
        linear_outputFile << "Prediction for x = " << x << ": " << prediction << " -- Actual = " << stock_data_test.second[i] << std::endl;
        error += std::abs(stock_data_test.second[i] - prediction);
        total += stock_data_test.second[i];
    }

    linear_outputFile << "=================\nAverage Percent Error: " << (error / total) * 100 << "%" << std::endl;

    auto linear_end = chrono::high_resolution_clock::now();  // Stop measuring time

    // Calculate and print the running time in seconds
    auto linear_duration = chrono::duration_cast<chrono::microseconds>(linear_end - linear_start);
    linear_outputFile << endl << "Running Time: " << linear_duration.count() << " ms" << endl;


    linear_outputFile.close();

    // Testing out logistic regression
    // get linear runtime
    auto logistic_start = std::chrono::high_resolution_clock::now();
    std::cout << "** Testing Logistic **" << std::endl;
    logistic_regression::LogisticRegression logisticModel(variable_data.second, stock_data.second, LEARNING_RATE, NUM_EPOCHS);

    // opening logistic output file
    std::ofstream logistic_outputFile("LogisticPredictions.txt");
    std::cout << "Logistic Predictions outputted to output file **" << std::endl;

    // Log error rate between prediction and actual movement, with total error
    logistic_outputFile << "Predictions: " << std::endl;
    int correct_predictions = 0;
    for (int i = 0; i < variable_data_test.second.size(); i++)
    {
        float x = variable_data_test.second[i];
        int prediction = logisticModel.prediction(x);
        // Use binary encoding to determine if prediction was right or wrong
        logistic_outputFile << "Prediction for x = " << x << ": " << prediction << " -- Actual = " << stock_encodings_test[i] << std::endl;
        if (prediction == stock_encodings_test[i]) {
            correct_predictions++;
        }
    }
    logistic_outputFile << "=================" << std::endl;
    float logistic_accuracy = static_cast<float>(correct_predictions) / static_cast<float>(variable_data_test.second.size()) * 100;
    logistic_outputFile << "Accuracy: " << logistic_accuracy << "%" << std::endl;

    auto logistic_end = chrono::high_resolution_clock::now();  // Stop measuring time

    // Calculate and print the running time in seconds
    auto logistic_duration = chrono::duration_cast<chrono::microseconds>(logistic_end - logistic_start);
    logistic_outputFile << endl << "Running Time: " << logistic_duration.count() << " ms" << endl;

    logistic_outputFile.close();

    return 0;
}
