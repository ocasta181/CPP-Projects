#ifndef ASTAR_H
#define ASTAR_H

#include <memory>

struct Point {
    const int _x;
    const int _y;

    Point(int x, int y);

    bool operator==(const Point &right);
};

struct Node {
    std::shared_ptr<Point> _point;
    std::shared_ptr<Node> _parent;
    std::shared_ptr<Node> _startNode;
    std::shared_ptr<Node> _endNode;
    int _gCost;
    int _hCost;
    int _fCost;

    Node(const std::shared_ptr<Point> &point);

    Node(const std::shared_ptr<Point> &point, 
         std::shared_ptr<Node> &parent, 
         std::shared_ptr<Node> &startNode, 
         std::shared_ptr<Node> &endNode);

    void setCosts(  std::shared_ptr<Node> &startNode, 
                    std::shared_ptr<Node> &endNode);

    void set_gCost( std::shared_ptr<Node> &startNode);

    void set_hCost( std::shared_ptr<Node> &endNode);

    void set_fCost();
};

std::vector<std::vector<std::shared_ptr<Node>>> findChildren( std::shared_ptr<Node> &parent,
                                std::shared_ptr<Node> &startNode,
                                std::shared_ptr<Node> &endNode,
                                std::vector<Node> Closed,
                                std::vector<Node> Open);

void AStar( std::unique_ptr<Point> &start, std::unique_ptr<Point> &end);

#endif //ASTAR_H