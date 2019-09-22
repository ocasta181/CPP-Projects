#include "LinkedList.h"

#include <iostream>


Node::Node(const int value)
	: _value(value),
	  _next() {
};

LinkedList::LinkedList(const int value)
	: _root(std::make_unique<Node>(value)){
};

LinkedList::LinkedList()
	: _root(nullptr){
};

void LinkedList::insert(const int value) {
	std::unique_ptr<Node> old_root = std::move(_root);
	_root = std::make_unique<Node>(value);
	_root->_next = std::move(old_root);
	return;
};

bool LinkedList::find(const int value) {
	Node* node =  _root.get(); // will this cause a memory leak?
	while(node){
		if (node->_value == value){
			return true;
		}
		else {
			node = node->_next.get();
		}
	}
	return false;
};

int main(){
	LinkedList ll;
	ll.insert(2);
	ll.insert(1);
	ll.insert(3);
	std::cout << ll.find(4) << "\n";
	std::cout << ll.find(3) << "\n";
	std::cout << std::endl;
	return 0;
};