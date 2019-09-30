#include <memory>
#include <vector>

struct Node {
    const int _value; 
    std::unique_ptr<Node> _left; 
    std::unique_ptr<Node> _right; 
    int _height; 

    Node(int v);
};

struct AVL {
    enum class Dir : char {
        Left  = 'L', 
        Right = 'R',
    };

    AVL() = default;
    AVL(int value);
    std::vector<int> traverse();
    void insert(const std::vector<int> &array);
    bool insert(int value);
    

    bool find(int value) const;
    std::vector<int> traverse() const;

private:

    std::unique_ptr<Node> _root;

    template<Dir dir>
    Dir invert();

    template<Dir dir>
    std::unique_ptr<Node>& accessFirst(std::unique_ptr<Node> &node);

    template<Dir dir>
    std::unique_ptr<Node>& accessSecond(std::unique_ptr<Node> &node);

    template<Dir dir>
    void simpleFlip(std::unique_ptr<Node> &side, std::unique_ptr<Node> &new_base);

    template<Dir dir>
    void complexFlip(std::unique_ptr<Node> &side, std::unique_ptr<Node> &new_base);

    template<Dir parentType, Dir childType>
    void flip(std::unique_ptr<Node> &side, std::unique_ptr<Node> &new_base);

    void updateHeight(std::unique_ptr<Node> &node);
    void balance(std::unique_ptr<Node> &side, 
                 std::unique_ptr<Node> &node, 
                 const std::vector<AVL::Dir> &path,
                 int depth);

    std::vector<int> traverse(	std::unique_ptr<Node> &node, 
                                std::vector<int> &numbers);
    bool insert(int value, 
                std::unique_ptr<Node> &node, 
                std::vector<Dir> &path,
                int depth);		

};