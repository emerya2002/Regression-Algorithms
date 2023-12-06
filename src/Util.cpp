#include "Util.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

namespace util {

// Define test function
void test() {
	std::cout << "Hello from Util.cpp" << std::endl;
}

void splitData(
	std::pair<std::vector<std::string>, std::vector<float> > &train_data,
	std::pair<std::vector<std::string>, std::vector<float> > &test_data,
	int test_amount = 5) {
	if (train_data.first.size() <= test_amount || train_data.second.size() <= test_amount) {
		std::cerr << "Error: train_data needs to be greater than test_amount" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Seed random generator with current time
	std::srand(std::time(nullptr));

	for (int i = 0; i < test_amount; ++i)
	{
		// Generate a random index
		int index = std::rand() % train_data.first.size();

		// Move the values at index from train_data to test_data
		test_data.first.push_back(train_data.first[index]);
		test_data.second.push_back(train_data.second[index]);

		// Erase the moved elements from train_data
		train_data.first.erase(train_data.first.begin() + index);
		train_data.second.erase(train_data.second.begin() + index);
	}
}

} // namespace util
