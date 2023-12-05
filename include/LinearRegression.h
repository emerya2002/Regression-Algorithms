#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <vector>

using namespace std;

namespace linear_regression {

    class LinearRegression {
        public:
            LinearRegression(const vector<float>& x_values, const vector<float>& y_values);
            float prediction(float x) const;

        private:
            float slope;
            float intercept;
    };

    void test();

} // namespace regression

#endif