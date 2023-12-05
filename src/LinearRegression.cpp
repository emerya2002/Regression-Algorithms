#include "LinearRegression.h"
#include <iostream>

namespace linear_regression {

LinearRegression::LinearRegression(const vector<float>& x_values, const vector<float>& y_values) {
	// implement to find line of best firt here (maybe use squares)
	// set the values of slope and intercept base on the resulting line of best fit
	slope = 0.0;
	intercept = 0.0;
}

float LinearRegression::prediction(float x) const{
	return slope*x + intercept;
}

// Define test function
void test() {
	std::cout << "Hello from LinearRegression.cpp" << std::endl;
}

} // namespace linear_regression