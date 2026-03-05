#include <vector>
#include <cstdint>

using namespace std;

class Node
{
public:
	int frequency;
	uint8_t key;
	Node *left;
	Node *right;
	bool isLeaf;

	Node();
	Node(int x);
	Node(int x, uint8_t key);
	Node(int x, bool leaf, uint8_t key);
	Node(Node *x);
};

class MinHeap
{
public:
	MinHeap();

	void addNode(int val, uint8_t key);
	void addNode(Node val);
	Node pop();
	Node top();
	void print();
	size_t size();

private:
	vector<Node> storage;
};