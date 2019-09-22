#include <memory>
#include <vector>

struct Node {
	const int _value; 
	std::unique_ptr<Node> _left; 
	std::unique_ptr<Node> _right; 
	int _height; 

	Node(int v);
};

class AVL {

	enum class Dir : char {
		Left  = 'L', 
		Right = 'R',
	};

	std::unique_ptr<Node> _root;

	template<Dir dir>
	Dir invert();

	template<Dir dir>
	std::unique_ptr<Node>& accessFirst(std::unique_ptr<Node> &node);

	template<Dir dir>
	std::unique_ptr<Node>& accessSecond(std::unique_ptr<Node> &node){
		Dir inverted = invert<dir>(node);
		return accessFirst<inverted>;
	}

	template<Dir dir>
	void simpleFlip(std::unique_ptr<Node> &side, std::unique_ptr<Node> &new_base);

	template<Dir dir>
	void complexFlip(std::unique_ptr<Node> &side, std::unique_ptr<Node> &new_base);

	template<Dir parent, Dir child>
	void flip(std::unique_ptr<Node> &side, std::unique_ptr<Node> &new_base){
		simpleFlip<parent>(side, new_base);
	};

	template<Dir parentType, Dir childType>
	void flip(std::unique_ptr<Node> &side);

	void updateHeight(std::unique_ptr<Node> &node);
	void balance(std::unique_ptr<Node> &side, 
				 std::unique_ptr<Node> &node, 
				 const std::vector<AVL::Dir> &path,
				 int depth);
	std::vector<int> traverse(	std::unique_ptr<Node> &node = _root, 
								std::vector<int> &numbers = std::vector<int>());




public:

	AVL() = default;
	AVL(int value);
	void insert(const std::vector<int> &array);
	bool insert(int value, 
				std::unique_ptr<Node> &node = _root, 
				std::vector<Dir> &path = std::vector<Dir>(),
				int depth = 0);

	bool find(int value) const;
	std::vector<int> traverse() const;		

};