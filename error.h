#pragma once

#include <string>
#include <iostream>
#include <sys/stat.h>

using namespace std;

// Error struct
//  errorCode legend to be added here
class error {
	string errorMessage;
	int errorCode{ 0 };

public:
	error(string msg = "Unspecified Exception", int errorCode = -1) :
		errorMessage{ msg }, errorCode{ errorCode }{};

	void displayError() {
		cout << "Exception occured with message: " << errorMessage << '\n';
		cout << "Exception code: " << errorCode << '\n';
	}
};

inline bool fileExists(std::string& name) { // Mostly non-directly related function that checks file for existence
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}
