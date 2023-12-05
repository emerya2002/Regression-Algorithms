#ifndef LOGISTIC_REGRESSION_H
#define LOGISTIC_REGRESSION_H

#include <vector>
#include <cmath>

using namespace std;

namespace logistic_regression {

    class LogisticRegression {
        public:
            LogisticRegression(const vector<float>& x_values, const vector<float>& y_values);
            float prediction(float x) const;
            // Declare test function

        private:
            float slope;
            float intercept;
    };

    void test();

} // namespace logistic_regression

#endif