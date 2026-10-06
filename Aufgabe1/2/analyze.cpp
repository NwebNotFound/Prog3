#include "analyze.h"
#include <string>
int analyze(int input) {
	int temp = input;
	if (input == 0) {
		return 1;
	}
	int numOfDigits = (input < 0) ? 1 : 0;
	while (input != 0) {
		++numOfDigits;
		input /= 10;
	}
	std::cout << "The number " <<temp <<" has "<<numOfDigits<<" digits.\n";
	return numOfDigits;

}

int analyze(std::string input) {
	std::cout << "string \"" << input << "\" is " << input.length() << " long.\n";
	return input.length();

}

