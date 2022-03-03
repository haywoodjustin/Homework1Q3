#include <iostream>

using namespace std; 

struct adjNode {
	int val;
	adjNode* next = NULL; 
};

struct edge {
	int start, end; 
};

class Graph {
	int numNodes;
public:
	adjNode* heads[numNodes];
	Graph(int nodeList) {
		numNodes = nodeList[0]; // list[0] is the number of nodes in the graph.
		int i = 1;
		int j = 2;
		while (nodeList[i] >= 0 && nodeList[j] >= 0) {
			adjNode* edge = new adjNode;
			edge->val = nodeList[j];
			if (heads[i] == NULL) {
				heads[i] = edge;
				continue;
			}
			adjNode* endNode = heads[i];
			while (endNode->next != NULL) {
				endNode = endNode->next;
			}
			endNode->next = edge;
			j = j + 2;
			i = i + 2;
		}
	}
	string edgeAddition(int from, int to) {
		if (from > numNodes || to > numNodes) {
			return "Invalid vertex given."; // Can't add an edge to a vertex that doesn't exist.
		}
		adjNode* edge = new adjNode;
		edge->val = to;
		if (heads[from] == NULL) {
			heads[from] = edge;
		}
		else {
			adjNode* endNode = heads[i];
			while (endNode->next != NULL) {
				endNode = endNode->next;
			}
			endNode->next = edge;
		}
		return "Edge added succesfully.";
	}
	string edgeDeletion(int from, int to){
		if (from > numNodes || to > numNodes) {
			return "Invalid vertex given."; // Can't delete an edge to a vertex that doesn't exist.
		}
		if (heads[from] == NULL) {
			// There are no edges associated with the given from vertex.
			return "Given from vertex does not have any associated edges."; 
		}
		adjNode* currNode = heads[i];
		while (currNode->next != NULL) {
			if (currNode)
			currNode = currNode->next;
		}
		return "Edge deleted succesfully";
	}
};
 
int main() {

	int graphList = { 5,0,1,1,4,2,3,1,3,3,4,-1 };
	Graph graph = new Graph(graphList);

	return 0; // Hi Justin <3
};