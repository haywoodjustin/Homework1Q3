#include <iostream>

using namespace std; 

struct adjNode {
	int val;
	adjNode* next; 
};

struct edge {
	int start, end; 
};

class graph{
	adjNode* getAdjListNode(int value, adjNode* head) {
		adjNode* newNode = new adjNode; 
		newNode->val = value;
		newNode->next = head; 

		return newNode; 
	}
public:

};
 
int main() {

	edge edges[3] = { {1,2}, {0,3}, {4,3} }; 

	return 0; // Hi Justin <3
}