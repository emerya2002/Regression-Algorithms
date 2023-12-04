#include "LinearRegression.h"
#include "LogisticRegression.h"
#include "Parser.h"
#include "Util.h"

int main() {
    // Testing out all header files, should all print hello with filename.
    linear_regression::test();
    logistic_regression::test();
    parser::test();
    util::test();

    return 0;
}
