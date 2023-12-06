#include "LinearRegression.h"
#include <iostream>

namespace linear_regression {

LinearRegression::LinearRegression(const vector<float>& x_values, const vector<float>& y_values) {
	// implement to find line of best firt here (maybe use squares)
	// set the values of slope and intercept base on the resulting line of best fit
    // Calculate the mean of x and y
    float x_mean = 0.0;
	float x_total = 0.0;
    float y_mean = 0.0;
	float y_total = 0.0;

    for (float x : x_values) {
        x_total += x;
    }

    for (float y : y_values) {
        y_total += y;
    }

    x_mean = x_total / x_values.size();
    y_mean = y_total / y_values.size();

    // Calculate the slope and intercept using the least squares method
    float numerator = 0.0;
    float denominator = 0.0;

    for (size_t i = 0; i < x_values.size(); ++i) {
        numerator += (x_values[i] - x_mean) * (y_values[i] - y_mean);
        denominator += pow(x_values[i] - x_mean, 2);
    }

    slope = numerator / denominator;
    intercept = y_mean - slope * x_mean;
}

float LinearRegression::prediction(float x) const{
	return slope*x + intercept;
}

// Define test function
void test() {
	std::cout << "Hello from LinearRegression.cpp" << std::endl;
}

} // namespace linear_regression