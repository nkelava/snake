#pragma once
#include <iostream>

using namespace std;

class Exception {
public:
	virtual void ShowError() = 0;
};

class FileNotFoundException : public Exception {
public:
	void ShowError() { cout << "Couldn't open files. Please check that the coordinates and highscores file names are correct and make sure the files are in the project's directory." << endl << endl; }
};
