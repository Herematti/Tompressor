#include <vector>

using namespace std;

class Node
{
public:
	int data;
	Node *left;
	Node *right;

	Node(int x);
	Node(Node* x);
};

class MinHeap
{
public:
	MinHeap();

	void addNode(int val);
	void addNode(Node val);
	Node pop();
	Node top();
	void print();
	size_t size();

private:
	vector<Node> storage;
};