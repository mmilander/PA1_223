#include "Node.h"
#include "Data.h"
#include <stdlib.h>
#include <time.h>

template<class T>
class List
{
public:
	int size = 0;
	List() { // constructor
		head = nullptr;
		tail = nullptr;
	}
	~List() { // destructor
		Node<T>* temp = head;
		while (temp != nullptr) {
			Node<T>* temp1 = temp;
			temp = temp->getNext();
			delete(temp1);
		}
	}
	void insertAtFront(T newData) {
		Node<T>* newNode = new Node<T>(newData); //allocate space
		if (head == nullptr) {
			head = newNode;
			size++;
			//tail = newNode;
		}
		else {
			newNode->setNext(head);
			head = newNode;
			size++;
		}
	}

	void removeNode(string target) { //target is the linux command e.g. g++ 
		Node<T>* temp = head;
		Node<T>* current = head;
		Node<T>* previous = head;
		if (head == nullptr) {
			cout << "List is empty" << endl;
		} else if(head->getData().command == target) { //if head needs to be deleted
			head = head->getNext();
			delete(temp);
			size--;
		}
		else {
			while (temp != nullptr) {
				Node<T>* temp2 = temp;
				if (temp->getData().command == target) {
					previous->setNext(temp->getNext());
					temp = temp->getNext();
					delete(temp2);
					break; //node removed
					size--;
				}
				else {
					previous = temp;
					temp = temp->getNext();
					current = temp;
				}
			}
		}
	}

	bool isEmpty() {
		return (head == nullptr);
	}
	void print() {
		Node<T>* temp = head;
		while (temp != nullptr) {
			T tempData = temp->getData();
			cout << tempData.command << " " << tempData.definition << " " << tempData.pointValue << endl;
			temp = temp->getNext();
		}
	}
	Node<T> generateRandom() {
		Node<T>* temp = head;
		//srand(time(NULL));
		int randomNum = 0;
		if (size != 0) {
			//cout << "SIZE: " << size << endl;
			randomNum = rand() % size;
		}
		int flag = 0;
		while (flag != randomNum) {
			temp = temp->getNext();
			flag++;
		}
		return *temp;
	}
	void save() {
		ofstream writeMe;
		writeMe.open("commandsPA1.csv");
		Node<T>* temp = head;
		while (temp != nullptr) {
			writeMe << temp->getData().command << ",";
			writeMe << temp->getData().definition << ",";
			writeMe << temp->getData().pointValue << "," << endl;
			temp = temp->getNext();
		}
		writeMe.close();
	}

private:
	Node<T>* head;
	Node<T>* tail;
};
