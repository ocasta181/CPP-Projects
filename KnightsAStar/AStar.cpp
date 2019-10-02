#include "AStar.h"

#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

Point::Point(const int x, const int y)
    : _x(x),
      _y(y) {
}

bool Point::operator== (const Point &right) {
    return (this->_x == right._x && this->_y == right._y);
}

Node::Node(const std::shared_ptr<Point> &point)
    :   _point(point),
        _parent(nullptr),
        _startNode(nullptr),
        _endNode(nullptr),
        _gCost(),
        _hCost(),
        _fCost() {}

Node::Node( const std::shared_ptr<Point> &point, 
            std::shared_ptr<Node> &parent, 
            std::shared_ptr<Node> &startNode, 
            std::shared_ptr<Node> &endNode)
    : _point(point),
      _parent(parent),
      _startNode(startNode),
      _endNode(endNode),
      _gCost(),
      _hCost(),
      _fCost() {
    if (_startNode && _endNode){
        Node::setCosts(_startNode, _endNode);
    }
}

void Node::setCosts(std::shared_ptr<Node> &startNode, 
                    std::shared_ptr<Node> &endNode) {
    Node::set_gCost(startNode);
    Node::set_hCost(endNode);
    Node::set_fCost();
}

void Node::set_gCost(std::shared_ptr<Node> &startNode) {
    int x_dist = std::abs(_point->_x - startNode->_point->_x);
    int y_dist = std::abs(_point->_y - startNode->_point->_y);
    int mindist = std::min(x_dist, y_dist);
    int maxdist = std::max(x_dist, y_dist);
    _gCost = mindist * 14 + (maxdist - mindist) * 10;
}

void Node::set_hCost(std::shared_ptr<Node> &endNode) {
    int x_dist = std::abs(_point->_x - endNode->_point->_x);
    int y_dist = std::abs(_point->_y - endNode->_point->_y);
    int mindist = std::min(x_dist, y_dist);
    int maxdist = std::max(x_dist, y_dist);
    _hCost = mindist * 14 + (maxdist - mindist) * 10;
}

void Node::set_fCost() {
    _fCost = _gCost + _hCost;
}

std::vector<std::vector<std::shared_ptr<Node>>> findChildren( 
                                std::shared_ptr<Node> &parent,
                                std::shared_ptr<Node> &startNode,
                                std::shared_ptr<Node> &endNode,
                                std::vector<std::shared_ptr<Node>> Closed,
                                std::vector<std::shared_ptr<Node>> Open) {
    int x = parent->_point->_x;
    int y = parent->_point->_y;

    std::vector<std::shared_ptr<Point>> links {  std::make_shared<Point>(Point(x-2, y-1)), 
                                                 std::make_shared<Point>(Point(x-2, y+1)), 
                                                 std::make_shared<Point>(Point(x-1, y-2)),
                                                 std::make_shared<Point>(Point(x-1, y+2)),
                                                 std::make_shared<Point>(Point(x+1, y-2)),
                                                 std::make_shared<Point>(Point(x+1, y+2)),
                                                 std::make_shared<Point>(Point(x+2, y-1)),
                                                 std::make_shared<Point>(Point(x+2, y+1)) };

    for (int i = 0; i < links.size(); ++i) {
        bool removeFlag = false;
        for (auto & c : Closed){
            if (*links[i] == *c->_point){
                links.erase(links.begin() + i);
                --i;
                removeFlag = true;
                break;
            }
        }
        if (removeFlag) {
            continue;
        }
        Node tempNode = Node(links[i], parent, startNode, endNode);
        
        for (int j = 0; j <= Open.size(); j++) { //auto o : Open) {
            std::shared_ptr<Node> o = Open[j];
            if (tempNode._point == o->_point) {
                if (tempNode._hCost >= o->_hCost) {
                    links.erase(links.begin() + i);
                    --i;
                    break;
                }
                else {
                    Open.erase(Open.begin() + j); //remove(o)
                }
            }
        }
    }
    std::vector<std::vector<std::shared_ptr<Node>>> children;
    children.push_back(Open);
    // std::vector<std::shared_ptr<Node>> tmp;
    for (auto & link : links) {
        children[0].push_back(std::make_shared<Node>(Node(link, parent, startNode, endNode)));
    }
    // children[0].push_back(tmp);
    children.push_back(Closed); //children.end(), std::begin(Closed), std::end(Closed));

    return children;
}

void AStar(std::shared_ptr<Point> &start, std::shared_ptr<Point> &end) {
    std::shared_ptr<Node> startNode = std::make_shared<Node>(Node(start));
    std::shared_ptr<Node> endNode = std::make_shared<Node>(Node(end));
    startNode->setCosts(startNode, endNode);
    endNode->setCosts(startNode, endNode);
    std::vector<std::shared_ptr<Node>> Closed;
    std::vector<std::shared_ptr<Node>> Open;
    Open.push_back(startNode);

    while(Open.size() > 0){
        std::shared_ptr<Node> current = * std::min_element( std::begin(Open), 
                                                          std::end(Open), 
                                                          [](std::shared_ptr<Node> i, std::shared_ptr<Node> j){
                                                              return i->_fCost < j->_fCost;
                                                          }
                                                        );
        if (current->_point == endNode->_point){
            std::vector<std::shared_ptr<Point>> path;
            int nMoves = 0;
            while(current->_parent){
                path.push_back(current->_point);
                current = current->_parent;
                ++nMoves;
            }
            path.push_back(current->_point);
            std::cout << "path: (" << path.back()->_x << "," << path.back()->_y << ")\nnMoves: " << nMoves << std::endl;
            return;
        }
        Open.erase(std::remove(Open.begin(), Open.end(), current), Open.end());
        Closed.push_back(current);
        std::vector<std::vector<std::shared_ptr<Node>>> children = findChildren(current, startNode, endNode, Closed, Open);
        std::vector<std::shared_ptr<Node>> Open = children[0];
        std::vector<std::shared_ptr<Node>> Closed = children[1];
    }

}

int main(){
    std::shared_ptr<Point> start = std::make_shared<Point>(Point(0, 0));
    std::shared_ptr<Point> end = std::make_shared<Point>(Point(8, 3));

    AStar(start, end);

}