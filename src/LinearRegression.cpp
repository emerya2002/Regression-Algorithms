#include "LinearRegression.h"

namespace linear_regression {

LinearRegression::LinearRegression(const vector<float>& x_values, const vector<float>& y_values, const vector<pair<float, float>>& xy_values) {
	// implement to find line of best firt here (maybe use squares)
	// set the values of slope and intercept base on the resulting line of best fit
    // Calculate the mean of x and y
    for (float x : x_values) {
        x_sum += x;
    }

    for (float y : y_values) {
        y_sum += y;
    }

    // x_mean = x_sum / x_values.size();
    // y_mean = y_sum / y_values.size();

    // Calculate the slope and intercept using the least squares method
    for (size_t i = 0; i < x_values.size(); ++i) {
		xy_sum += (x_values[i] * y_values[i]);
		x_squared_sum += (x_values[i] * x_values[i]);
    }

	float n = x_values.size();
	slope_numerator = ((n * xy_sum) - (x_sum * y_sum));
	slope_denominator = ((n * x_squared_sum) - (x_sum * x_sum));
	intercept_numerator = ((y_sum * x_squared_sum) - (x_sum * xy_sum));
	intercept_denominator = ((n * x_squared_sum) - (x_sum * x_sum));

    slope = slope_numerator / slope_denominator;
    intercept = intercept_numerator / intercept_denominator;
}

// functions to check values of slope, mean, etc
float LinearRegression::showSlope() {
	return slope;
}
float LinearRegression::showIntercept() {
	return intercept;
}
float LinearRegression::showX_sum() {
	return x_sum;
}
float LinearRegression::showY_sum() {
	return y_sum;
}

// make predictions based on y = mx + b
float LinearRegression::prediction(float x) {
	return (slope*x) + intercept;
}

// Define test function
void test() {
	std::cout << "Hello from LinearRegression.cpp" << std::endl;
}

} // namespace linear_regression