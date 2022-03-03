#include <iostream>
#include <vector>

using namespace std; 

struct adjNode {
	int val;
	adjNode* next = NULL; 
};

class Graph {
	int numNodes;
public:
	//adjNode** heads;
	vector<adjNode*> heads; 
	Graph(int nodeList[]) {
		numNodes = nodeList[0]; // list[0] is the number of nodes in the graph.
		for (int i=0; i<numNodes; i++){
			heads.push_back(nullptr);
		}
		int i = 1;
		int j = 2;
		while (nodeList[i] >= 0 && nodeList[j] >= 0) {
			adjNode* edge = new adjNode;
			edge->val = nodeList[j];
			if (heads[i] == nullptr) {
				heads[i] = edge;
				i, j += 2; 
				continue;
			}
			edge->next = heads[i];
			heads[i] = edge;
			i, j += 2; 
		}
	}
	/*int getNumNodes() {
		return numNodes;
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
			adjNode* endNode = heads[from];
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
		if (heads[from]->val == to){
			heads[from] = NULL;
			return "Edge deleted succesfully";
		}
		adjNode* currNode = heads[from];
		while (currNode->next != NULL) {
			if (currNode->next->val == to){
				currNode->next = currNode->next->next;
				return "Edge deleted succesfully";
			}
			currNode = currNode->next;
		}
		return "Edge was not found";
	}
	~Graph(){
		delete numNodes;
		delete heads;
	} */ 
};
 
/*int* DFS(Graph G, int v) {
	const int length = G.getNumNodes();
	int dfs[length];
	int mark[length];
	mark[v] = 1;
	if (G.heads[v] = NULL){
		return;
	}
	adjNode* currNode = G.heads[v];
	while (currNode->next != NULL){
		if (mark[currNode->val] == 0){
			dfs = v + DFS(G, currNode->val);
		}
		currNode = currNode->next;
	}
	return &dfs;
};*/

int main() {

	int graphList[12] = {5,0,1,1,4,2,3,1,3,3,4,-1};
	/*edge edgeList[5], temp;
	int j = 0; 
	for (int i = 1; i != -1; i += 2) {
		temp.start = graphList[i]; 
		temp.end = graphList[i + 1]; 
		edgeList[j] = temp; 
		j++; 
	} */
	Graph graph(graphList);

	return 0; // Hi Justin <3
};