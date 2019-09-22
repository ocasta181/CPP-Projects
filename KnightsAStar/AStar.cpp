#include "AStar.h"

#include <cmath>
#include <algorithm>

Point::Point(const int x, const int y)
    : _x(x),
      _y(y) {
}

bool Point::operator== (const Point &left, const Point &right) {
    return (left._x == right._x && left._y == right._y);
}

Node::Node( const Point &point, 
            const std::unique_ptr<Node> &parent = nullptr, 
            const std::unique_ptr<Node> &startNode = NULL, 
            const std::unique_ptr<Node> &endNode = NULL)
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

void Node::setCosts(std::unique_ptr<Node> &startNode, 
                    std::unique_ptr<Node> &endNode) {
    Node::set_gCost(startNode);
    Node::set_hCost(endNode);
    Node::set_fCost();
}

void Node::set_gCost(std::unique_ptr<Node> &startNode) {
    int x_dist = std::abs(_point._x - startNode->_point._x);
    int y_dist = std::abs(_point._y - startNode->_point._y);
    int mindist = std::min(x_dist, y_dist);
    int maxdist = std::max(x_dist, y_dist);
    _gCost = mindist * 14 + (maxdist - mindist) * 10;
}

void Node::set_hCost(std::unique_ptr<Node> &endNode) {
    int x_dist = std::abs(_point._x - endNode->_point._x);
    int y_dist = std::abs(_point._y - endNode->_point._y);
    int mindist = std::min(x_dist, y_dist);
    int maxdist = std::max(x_dist, y_dist);
    _hCost = mindist * 14 + (maxdist - mindist) * 10;
}

void Node::set_fCost() {
    _fCost = _gCost + _hCost;
}

std::vector<Node> findChildren( std::unique_ptr<Node> &parent,
                                std::unique_ptr<Node> &startNode,
                                std::unique_ptr<Node> &endNode,
                                std::vector<Node> Closed,
                                std::vector<Node> Open) {
    int x = parent->_point._x;
    int y = parent->_point._y;

    std::vector<Point> links {  Point::Point(x-2, y-1), 
                                Point::Point(x-2, y+1), 
                                Point::Point(x-1, y-2),
                                Point::Point(x-1, y+2),
                                Point::Point(x+1, y-2),
                                Point::Point(x+1, y+2),
                                Point::Point(x+2, y-1),
                                Point::Point(x+2, y+1) };

    for (int i = 0; i < links.size(); ++i) {
        bool removeFlag = false;
        for (auto c : Closed){
            if (links[i] == c._point){
                links.erase(links.begin() + i);
                --i;
                removeFlag = true;
                break;
            }
        }
        if (removeFlag) {
            continue;
        }
        Node tempNode = Node::Node(links[i], parent, startNode, endNode);
        
        for (auto o : Open) {
            if (tempNode._point == o._point) {
                if (tempNode._hCost >= o._hCost) {
                    links.erase(links.begin() + i);
                    --i;
                    break;
                }
                else {
                    // Open.remove(o)
                }
            }
        }
    }
    std::vector<Node> children;
    children.insert(children.end(), std::begin(Open), std::end(Open));
    for (auto link : links) {
        children.push_back(Node::Node(link, parent, startNode, endNode));
    }
    children.insert(children.end(), std::begin(Closed), std::end(Closed));

    return children;
}

