#include "LogisticRegression.h"
#include <iostream>

namespace logistic_regression {

LogisticRegression::LogisticRegression(const vector<float>& x_values, const vector<float>& y_values) {
	// implement logistic regression
	// set the values of slope and intercept based on the fitting result
}

float LogisticRegression::prediction(float x)const {
	float exponent = exp(-(slope * x + intercept));
	return 1 / (1 + exponent);
}

// Define test function
void test() {
	std::cout << "Hello from LogisticRegression.cpp" << std::endl;
}

} // namespace logistic_regression