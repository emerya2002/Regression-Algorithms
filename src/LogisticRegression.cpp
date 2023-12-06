#include "LogisticRegression.h"
#include "Util.h"
#include <iostream>
#include <cmath>

namespace logistic_regression {

LogisticRegression::LogisticRegression(const vector<float>& x_values, const vector<float>& y_values, float learning_rate, int epochs) {
	this->weight = 0;
	this->bias = 0;

	// Make empty array for storing encodings of price movements
	this->rates = x_values;
	this->prices = vector<float>(y_values.size(), 0);
	// A stock is encoded to 1 if it is greater than the previous day (profit)
	// A stock is encoded to 0 if it is less than the previous day (loss)
	for (int i = 1; i < y_values.size(); i++) {
		prices[i] = y_values[i] > y_values[i - 1] ? 1 : 0;
	}
	fit(x_values, y_values, learning_rate, epochs);
}

int LogisticRegression::prediction(float x)const {
	float z = this->weight * x + this->bias;
	return sigmoid(z) > 0.5 ? 1 : 0;
}

// Fitting function tailored to stock price vs rate analysis.
// "Trains" the model by going over the dataset `epoch` times and adjusting the params
void LogisticRegression::fit(const vector<float> &x_values, const vector<float> &y_values, float learning_rate, int epochs) {
	// Update parameters for specified number of epochs
	for (int i = 0; i < epochs; i++) { // O(epochs * NUM_DAYS)
		updateModel(learning_rate);
	}
}

// Updates the weight and bias of model using the gradient descent method
void LogisticRegression::updateModel(float learning_rate) { // O(NUM_DAYS)
	float weight_gradient = 0;
	float bias_gradient = 0;
	int n = this->rates.size();

	for (int i = 0; i < n; i++)
	{
		float prediction = this->prediction(this->rates[i]);
		// std::cout << this->rates[i] << "---" << prediction << std::endl;
		float error = this->prices[i] - prediction;
		weight_gradient += this->rates[i] * error;
		bias_gradient += error;
	}

	// Adjust the weight using the learning rate multiplied by the
	// average gradient for weights and biases
	weight += learning_rate * weight_gradient / n;
	bias += learning_rate * bias_gradient / n;
}

float LogisticRegression::sigmoid(float z) const {
	return 1.0f / (1.0f + std::exp(-z));
}


// Define test function
void test() {
	std::cout << "Hello from LogisticRegression.cpp" << std::endl;
}

} // namespace logistic_regression
