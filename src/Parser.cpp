#include "Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace parser {

// Define test function
void test() {
	std::cout << "Hello from Parser.cpp" << std::endl;
}

// Reads in data from a two column CSV file and returns a std::pair with the
// first column as a vector of strings and the second as a vector of floats
std::pair<std::vector<std::string>, std::vector<float> > parse_csv(const std::string& filename) {
	// Read in data from csv file
	std::ifstream file(filename);
	std::string line;

	if (!file.is_open()) {
		std::cerr << "Parser: Invalid filename '" << filename << "'" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::vector<std::string> dates = std::vector<std::string>();
	std::vector<float> values = std::vector<float>();

	// Skip first line (columns)
	getline(file, line);

	while (getline(file, line)) {

		std::stringstream ss(line);
		std::string date;
		std::string value;
		// Get data from line -> "DATE,VALUE"
		if (getline(ss, date, ',') && getline(ss, value)) {
			dates.push_back(date);
			values.push_back(std::stof(value));
		}
	}
	file.close();
	std::pair<std::vector<std::string>, std::vector<float> > result = std::make_pair(dates, values);
	return result;
}

} // namespace parser
