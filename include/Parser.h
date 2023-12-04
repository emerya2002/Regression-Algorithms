// File for parsing in stocks and variables from csv files in regression/data/
#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

namespace parser {

// Declare test function
void test();

// Parses a csv file with columns [date (YYYY-MM-DD), price/value (float)]
// Assumes the CSV file is without any missing data
std::pair<std::vector<std::string>, std::vector<float> > parse_csv(const std::string& filename);

} // namespace parser

#endif