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
    for(auto val: array){
        this->insert(val);
    }
}


bool AVL::insert(const int value){
    std::unique_ptr<Node> &node = this->_root;
    std::vector<AVL::Dir> path = std::vector<AVL::Dir>();
    const int depth = 0;

    return AVL::insert(value, node, path, depth);
}


bool AVL::insert(   const int value, 
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
                // need to point the parent *node* to this new *side*
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
        this->_root = std::make_unique<Node>(value);

        return true;
    }
}


std::vector<int> AVL::traverse( std::unique_ptr<Node> &node, 
                                std::vector<int> &numbers) {
    if (node){
        this->traverse(node->_left, numbers);
        numbers.emplace_back(node->_value);
        this->traverse(node->_right, numbers);
    }

    return numbers;
}

std::vector<int> AVL::traverse() {
    std::unique_ptr<Node> &node = this->_root;
    std::vector<int> numbers = std::vector<int>();

    return this->traverse(node, numbers);
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
                this->flip<AVL::Dir::Left, AVL::Dir::Left>(side, node);
            } else {
                this->flip<AVL::Dir::Left, AVL::Dir::Right>(side, node);
            } 
        } else {
            if (childType == AVL::Dir::Left) {
                this->flip<AVL::Dir::Right, AVL::Dir::Left>(side, node);
            } else {
                this->flip<AVL::Dir::Right, AVL::Dir::Right>(side, node);
            }
        }
    }
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
std::unique_ptr<Node>& AVL::accessSecond<AVL::Dir::Left>(std::unique_ptr<Node> &node){
    return node->_right;
}


template<>
std::unique_ptr<Node>& AVL::accessSecond<AVL::Dir::Right>(std::unique_ptr<Node> &node){
    return node->_left;
}


template<>
AVL::Dir AVL::invert<AVL::Dir::Left>(){
    return AVL::Dir::Right;
}


template<>
AVL::Dir AVL::invert<AVL::Dir::Right>(){
    return AVL::Dir::Left;
}


template<AVL::Dir parentType>
void AVL::simpleFlip(std::unique_ptr<Node> &side, std::unique_ptr<Node> &new_base) {
    this->accessFirst<parentType>(side) = this->accessSecond<parentType>(new_base);
    this->accessSecond<parentType>(new_base) = side;
}


template<AVL::Dir parentType>
void AVL::complexFlip(std::unique_ptr<Node> &side, std::unique_ptr<Node> &new_base) {

    AVL::accessSecond<parentType>(AVL::accessFirst<parentType>(side))   = AVL::accessFirst<parentType>(new_base);
    AVL::accessFirst<parentType>(new_base) 							= AVL::accessFirst<parentType>(side);
    AVL::accessFirst<parentType>(side) 								= AVL::accessSecond<parentType>(new_base);
    AVL::accessSecond<parentType>(new_base) 							= side;
}


template<AVL::Dir parentType, AVL::Dir childType>
void AVL::flip(std::unique_ptr<Node> &side, std::unique_ptr<Node> &node) {
    const auto rebase = [&node, &side, this](std::unique_ptr<Node> &new_base) {
        if (node and node->_left == side) {
            node->_left = move(new_base);
        } else if (node and node->_right == side) {
            node->_right = move(new_base);
        } else {
            this->_root = move(new_base);
        }
    };

    std::unique_ptr<Node> new_base = move(this->accessFirst<childType>(side));

    rebase(new_base);
    this->flip<parentType, childType>(side, new_base);
}


int main() { 
    AVL avl = AVL();
    
    std::vector<int> test_arr{1,2,3,4,5,6,7,8,9,10};
    avl.insert(test_arr);

    const auto numbers = avl.traverse(); 

    const auto printNum = [](int x){
        std::cout << x << " ";
    };

    std::for_each(numbers.begin(), numbers.end(), printNum);
    std::cout << std::endl;
    return 0;
}