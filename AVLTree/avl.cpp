#include "AVL.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

Node::Node(const int value)
	: _value(value),
	  _left(),
	  _right(),
	  _height(0) {
}

AVL::AVL(const int value)
	: _root(std::make_unique<Node>(value)) {
}

void AVL::insert(const std::vector<int> &array){
	std::for_each(array.begin(), array.end(), AVL::insert);
	// AVL::insert is an "unresolved overloaded function type"
}

bool AVL::insert(	const int value, 
					std::unique_ptr<Node> &node, 
					std::vector<AVL::Dir> &path,
					const int depth) { 
	if (node) {
		const auto insertSide = [value, &node, &path, &depth, this](std::unique_ptr<Node> &side) {
			if (side) {
				const bool inserted = insert(value, side, path, depth + 1);

				if (inserted) {
					AVL::updateHeight(node);
					AVL::balance(side, node, path, depth);
				}

				return inserted;
			} else {
				side = std::make_unique<Node>(value);
				AVL::updateHeight(node);
				
				return true;
			}
		};

		if (node->_value > value) {
			path.emplace_back(AVL::Dir::Left);

			return insertSide(node->_left);
		} else if (node->_value < value) {
			path.emplace_back(AVL::Dir::Right);

			return insertSide(node->_right);
		} else {
			return false;
		}
	} else {
		node = std::make_unique<Node>(value);

		return true;
	}
}

void AVL::updateHeight(std::unique_ptr<Node> &node){
	assert(node);

	const int right_height = node->_right ? node->_right->_height : 0;
	const int left_height  = node->_left  ? node->_left->_height  : 0;

	node->_height = std::max(left_height, right_height);
}

void AVL::balance(	std::unique_ptr<Node> &side, 
					std::unique_ptr<Node> &node, 
					const std::vector<AVL::Dir> &path,
					const int depth) {
	const int right_height = node->_right ? node->_right->_height : 0;
	const int left_height  = node->_left  ? node->_left->_height  : 0;
	const int not_balanced = std::abs(left_height - right_height) > 1;

	if(not_balanced){
		const AVL::Dir parentType = path[depth];
		const AVL::Dir childType  = path[depth + 1];

		if (parentType == AVL::Dir::Left){
			if (childType == AVL::Dir::Left) {
				flip<AVL::Dir::Left, AVL::Dir::Left>(side, node);
			} else {
				flip<AVL::Dir::Left, AVL::Dir::Right>(side, node);
			} 
		} else {
			if (childType == AVL::Dir::Left) {
				flip<AVL::Dir::Right, AVL::Dir::Left>(side, node);
			} else {
				flip<AVL::Dir::Right, AVL::Dir::Right>(side, node);
			}
		}
	}
}

std::vector<int> AVL::traverse( std::unique_ptr<Node> &node = _root, 
								std::vector<int> &numbers = std::vector<int>()) {
	if (node){
		traverse(node->_left, numbers);
		numbers.emplace_back(node->_value);
		traverse(node->_right, numbers);
	}

	return numbers;
}


template<>
std::unique_ptr<Node>& AVL::accessFirst<AVL::Dir::Left>(std::unique_ptr<Node> &node){
	return node->_left;
}

template<>
std::unique_ptr<Node>& AVL::accessFirst<AVL::Dir::Right>(std::unique_ptr<Node> &node){
	return node->_right;
}

template<>
AVL::Dir AVL::invert<AVL::Dir::Left>(){
	return AVL::Dir::Right;
}

template<>
AVL::Dir AVL::invert<AVL::Dir::Right>(){
	return AVL::Dir::Left;
}


template<AVL::Dir, AVL::Dir>
void simpleFlip(std::unique_ptr<Node> &side, std::unique_ptr<Node> &new_base) {
	AVL::accessFirst<AVL::Dir>(side) = AVL::accessSecond<AVL::Dir>(new_base);
	AVL::accessSecond<AVL::Dir>(new_base) = side;
}

template<AVL::Dir, AVL::Dir>
void complexFlip(std::unique_ptr<Node> &side, std::unique_ptr<Node> &new_base) {

	AVL::accessSecond<AVL::Dir>(AVL::accessFirst<AVL::Dir>(side))   = AVL::accessFirst<AVL::Dir >(new_base);
	AVL::accessFirst<AVL::Dir >(new_base) 							= AVL::accessFirst<AVL::Dir >(side);
	AVL::accessFirst<AVL::Dir >(side) 								= AVL::accessSecond<AVL::Dir>(new_base);
	AVL::accessSecond<AVL::Dir>(new_base) 							= side;
}

template<>
void flip<AVL::Dir::Left, AVL::Dir::Right>(std::unique_ptr<Node> &side, std::unique_ptr<Node> &new_base){
	complexFlip<parent>(side, new_base);
}

template<>
void flip<AVL::Dir::Right, AVL::Dir::Left>(std::unique_ptr<Node> &side, std::unique_ptr<Node> &new_base){
	complexFlip<parent>(side, new_base);
}

template<AVL::Dir parentType, AVL::Dir childType>
void AVL::flip(std::unique_ptr<Node> &side, std::unique_ptr<Node> &node) {
	const auto reBase = [&node, &side, this](std::unique_ptr<Node> &new_base) {
		if (node and node->_left == side) {
			node->_left = new_base;
		} else if (node and node->_right == side) {
			node->_right = new_base;
		} else {
			_root = new_base;
		}
	};

	std::unique_ptr<Node> new_base = accessFirst<childType>(side);

	rebase(new_base);
	flip<parentType, childType>(side, new_base);
}


// Driver Code 
int main() 
{ 
	AVL avl;
	
	/* Constructing tree given in 
	the above figure */
	avl.insert([1,2,3,4,5,6,7,8,9,10]);

	const auto numbers = avl.traverse(); 

	const auto printNum = [](int x){
		std::cout << x << " ";
	};

	std::for_each(numbers.begin(), numbers.end(), printNum);
	std::cout << std::endl;
	return 0;
} 

// This code is contributed by 
// rathbhupendra 
