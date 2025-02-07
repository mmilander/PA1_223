
#pragma once
//template< class NODETYPE > class List; // forward declaration

template<class T>
class Node
{
public:
	Node(T newData) { // copy constructor
		data = newData;
		nextPtr = nullptr;
	}
	T getData() { //; // return data in the node
		return data;
	}
	void setNext(Node<T>* nextP) {
		nextPtr = nextP;
	}
	Node <T>* getNext() {
		return nextPtr;
	}

private:
	T data; // data
	Node<T>* nextPtr; // next node in the list
};
