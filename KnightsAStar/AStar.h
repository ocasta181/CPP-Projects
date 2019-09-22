#ifndef ASTAR_H
#define ASTAR_H

#include <memory>

struct Point {
    const int _x;
    const int _y;

    Point(int x, int y);

    bool Point::operator==(const Point &left, const Point &right);
};

struct Node {
    Point _point;
    std::unique_ptr<Node> _parent;
    std::unique_ptr<Node> _startNode;
    std::unique_ptr<Node> _endNode;
    int _gCost;
    int _hCost;
    int _fCost;

    Node(   const Point point, 
            const std::unique_ptr<Node> &parent, 
            const std::unique_ptr<Node> &startNode, 
            const std::unique_ptr<Node> &endNode);

    void setCosts(  std::unique_ptr<Node> &startNode, 
                    std::unique_ptr<Node> &endNode);

    void set_gCost(std::unique_ptr<Node> &startNode);

    void set_hCost(std::unique_ptr<Node> &endNode);

    void set_fCost();
};

#endif //ASTAR_H