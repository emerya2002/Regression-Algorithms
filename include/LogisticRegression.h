#ifndef LOGISTIC_REGRESSION_H
#define LOGISTIC_REGRESSION_H

#include <vector>

using namespace std;

namespace logistic_regression {
    // Implements a simple binary logistic regression model for
    // analyzing stock price movements in relation to an independent variable.
    class LogisticRegression {
        public:
            // x - independent variable, y - dependent variable
            LogisticRegression(const vector<float>& x_values, const vector<float>& y_values, float learning_rate, int epochs);
            int prediction(float x) const;

        private:
            float weight; // "slope"
            float bias; // "intercept"

            vector<float> rates;
            vector<float>prices;

            // "Trains" the model by going over the dataset `epoch` times and adjusting the params
            void fit(const vector<float> &x_values, const vector<float> &y_values, float learning_rate, int epochs);
            void updateModel(float learning_rate);
            float sigmoid(float z) const;
    };

    // Declare test function
    void test();

} // namespace logistic_regression

#endif
