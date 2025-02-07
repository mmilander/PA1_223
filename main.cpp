/***************************************************************
* Programmer: Mitchell M. Milander
* Class: CptS 223, Spring 2025
* Programming Assignment: PA1
* Date: February 5, 2025
* Description: This program utilizes templates, classes, and a
			   linked list to implement a terminal game that
			   tests one's knowledge on Linux commands.
****************************************************************/

#include "List.h"

void menu(List<Data>* myList, string* profileNames, int* profilePoints);
void display();
void loadList(List<Data>* myList);
void loadProfile(string* profileNames, int* profilePoints);

int main() {
	string profileNames[5] = { "", "", "", "", "" };
	int profilePoints[5] = { -1, -1, -1, -1, -1 };
	List<Data> myList;
	loadList(&myList);
	loadProfile(profileNames, profilePoints);
	menu(&myList, profileNames, profilePoints);
	
	
	
	//myList.removeNode("g++");
}

void menu(List<Data>* myList, string* profileNames, int* profilePoints) {
	string name = "JohnDoe";
	int flagPro = 0;
	srand(time(NULL));
	int placement = 0;
	int pointValue = 0;
	cout <<
		"Welcome to Linux Trivia. For each question you get right, you recieve "
		"a specified number of points. You will chose the option to recieve a question "
		"and then you will be give 3 options to choose from. "
		"Choose wisely!"
		<< endl;
	int response = 0;
	string responseNum = "";
	while (response != 6) {
		cout << endl;
		display();
		cout << "-> ";
		
		getline(cin, responseNum);
		response = stoi(responseNum);
		switch (response) {
		case 1: {// new game
			if (flagPro == 0) {
				cout << "Name: ";
				getline(cin, name);
				cout << endl;
			}
			string store = "";
			cout << "How many questions do you want? ";
			getline(cin, store);
			cout << endl;
			int storeNum = stoi(store);
			for (int i = 0; i < storeNum; i++) {
				Node<Data> temp = myList->generateRandom();
				cout << "Question " << i + 1 << ": " << temp.getData().command << endl;
				int points = temp.getData().pointValue;
				string answer = temp.getData().definition;
				cout << "Options: " << endl;
				int ranNum = rand() % 3 + 1;
				
				if (ranNum == 1) {
					cout << "\t(1) " << answer << endl;
					temp = myList->generateRandom();
					cout << "\t(2) " << temp.getData().definition << endl;
					temp = myList->generateRandom();
					cout << "\t(3) " << temp.getData().definition << endl;
				}
				else if (ranNum == 2) {
					temp = myList->generateRandom();
					cout << "\t(1) " << temp.getData().definition << endl;
					cout << "\t(2) " << answer << endl;
					temp = myList->generateRandom();
					cout << "\t(3) " << temp.getData().definition << endl;
				}
				else {
					temp = myList->generateRandom();
					cout << "\t(1) " << temp.getData().definition << endl;
					temp = myList->generateRandom();
					cout << "\t(2) " << temp.getData().definition << endl;
					cout << "\t(3) " << answer << endl;
				}
				
				string response = "";
				cout << "Response: ";
				getline(cin, response);
				if (stoi(response) == ranNum ) {
					cout << "Well done!" << endl << endl;
					pointValue += points;
				}
				else {
					cout << "Better luck another day" << endl;
					if (points >= pointValue) {
						pointValue = 0;
					}
					else {
						pointValue = pointValue - points;
					}
				}
			}
			cout << "\n\tYour point value is : " << pointValue << endl;

			break;
		}
		case 2: {
			string nameLoad = "";
			cout << "Name to look up: ";
			getline(cin, nameLoad);
			cout << endl;
			for (int i = 0; i < 5; i++) {
				if (nameLoad == profileNames[i]) {
					cout << "Name found. Your profile is now loaded in the system" << endl;
					flagPro = 1;
					name = profileNames[i];
					pointValue = profilePoints[i];
				}
			}
			if (flagPro == 0) {
				cout << "Profile is not in the system." << endl;
			}
			cout << endl;

			break;
		}
		case 3: {
			Data newPoint;
			cout << "Command: ";
			string inputCommand = "";
			getline(cin, inputCommand);
			cout << endl;

			cout << "Definition: ";
			string inputDef = "";
			getline(cin, inputDef);
			cout << endl;

			cout << "Point Value (1-5): ";
			string point = "";
			getline(cin, point);
			cout << endl;

			newPoint.command = inputCommand;
			newPoint.definition = inputDef;
			newPoint.pointValue = stoi(point);
			myList->insertAtFront(newPoint);
			break;
		}
		case 4: {
			cout << "Name of command to remove: ";
			string cmd = "";
			getline(cin, cmd);
			myList->removeNode(cmd);
			break;
		}
		case 5: {
			myList->print();
			cout << endl;
			break;
		}
		case 6:
			cout << "Exiting program...\n";
			myList->save();
			ofstream writeMe;
			writeMe.open("Profiles.csv");
			int flagOver = 0;
			for(int i = 0; i < 5; i++){
				if (profileNames[i] != "") {
					writeMe << profileNames[i] << ",";
					if (profileNames[i] == name) { //if name is stored, then just update points
						writeMe << pointValue << endl;
						flagOver = 1;
					}
					else {
						writeMe << profilePoints[i] << endl;
					}
				}
				else if (flagOver == 0){ //write the current name/pointvalue
					writeMe << name << ",";
					writeMe << pointValue << endl;
					flagOver = 1;
					break;
				}
				//writeMe << temp->getData().pointValue << "," << endl;
			}
			if (flagOver == 0) { //max profiles
				cout << "There are already 5 profiles saved." << endl;
			}
			writeMe.close();
		};
	}
}
void display(){
	cout << "Please select an option:\n";
	cout << "\t1. Play New Game\n"
		"\t2. Load Previous Game\n"
		"\t3. Add Command\n"
		"\t4. Remove Command\n"
		"\t5. Display All\n"
		"\t6. Save and Exit\n";
}
void loadList(List<Data>* myList) {
	fstream readMe;
	readMe.open("commandsPA1.csv");
	if (readMe.is_open()) {
		string line = "";
		int location = 0;
		string command = "";
		string definition = "";
		int pointValue = 0;
		while (getline(readMe, line)) {
			Data read;
			location = line.find(',');
			command = line.substr(0, location);
			read.command = command;
			//cout << command << " ";
			line = line.substr(location + 1, line.length());

			location = line.find(',');
			definition = line.substr(0, location);
			read.definition = definition;
			//cout << definition << " ";
			line = line.substr(location + 1, line.length());

			location = line.find(',');
			pointValue = stoi(line.substr(0, location));
			read.pointValue = pointValue;
			//cout << pointValue << endl;
			line = line.substr(location + 1, line.length());
			myList->insertAtFront(read);
		}
		readMe.close();
	}
	else {
		cout << "File is unable to open" << endl;
	}
}

void loadProfile(string* profileNames, int* profilePoints) {
	fstream readMe;
	readMe.open("Profiles.csv");
	int tracker = 0; //max is 4 since size of arrays is 5. 
	if (readMe.is_open()) {
		string line = "";
		int location = 0;
		string name = "";
		int pointValue = 0;
		while (getline(readMe, line)) {
			location = line.find(',');
			name = line.substr(0, location);
			line = line.substr(location + 1, line.length());

			location = line.find(',');
			pointValue = stoi(line.substr(0, location));
			//cout << pointValue << endl;
			line = line.substr(location + 1, line.length());
			if (tracker < 5) {
				profileNames[tracker] = name;
				profilePoints[tracker] = pointValue;
			}
			tracker++;
		}
		readMe.close();
	}
	else {
		cout << "File is unable to open" << endl;
	}
}