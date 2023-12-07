#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <vector>
#include <iostream>
using namespace std;

namespace linear_regression {

    class LinearRegression {
        public:
            LinearRegression(const vector<float>& x_values, const vector<float>& y_values, const vector<pair<float,float>>& xy_values);
            float showSlope();
            float showIntercept();
            float showX_mean();
            float showX_sum();
            float showY_mean();
            float showY_sum();
            float prediction(float x);

        private:
            float slope = 0.0;
            float intercept = 0.0;
            float x_sum = 0.0;
            float y_sum = 0.0;
            float xy_sum = 0.0;
            float x_squared_sum = 0.0;
            float slope_numerator = 0.0;
            float slope_denominator = 0.0;
            float intercept_numerator = 0.0;
            float intercept_denominator = 0.0;
    };

    void test();

} // namespace regression

#endif