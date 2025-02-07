#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Data
{

public:
	string command;
	string definition;
	int pointValue;

	Data() {
		command = "";
		definition = "";
		pointValue = 0;
	}

};