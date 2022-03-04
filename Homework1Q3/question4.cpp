#include <iostream>
#include <vector>

using namespace std; 

struct adjNode {
	int val;
	adjNode* next = nullptr; 
};

class Graph {
	int numNodes;
	
public:
	vector<adjNode*> heads;  // {5,0,1,1,4,2,3,1,3,3,4,-1};
	Graph(int nodeList[]) {
		numNodes = nodeList[0]; // list[0] is the number of nodes in the graph.
		for (int i=0; i<numNodes; i++){
			heads.push_back(nullptr); //Initialize null ptrs in vector 
		}
		int i = 1;
		int j = 2; 
		while (nodeList[i] >= 0 && nodeList[j] >= 0) { //Add first integer as origin and second as destination 
			adjNode* edge = new adjNode;
			edge->val = nodeList[j];
			if (heads[nodeList[i]] == nullptr) { //heads[nodeList[i]] takes the origin vector from nodeList and is used to reference the same origin point in the edge vector 
				heads[nodeList[i]] = edge; //add adges if origin is null 
			//	cout << nodeList[i] << ", " << heads[nodeList[i]]->val << endl;
				i += 2;
				j += 2; 
				continue;
			}
			edge->next = heads[nodeList[i]];
			heads[nodeList[i]] = edge; //add edges if origin is not null 
			//cout << nodeList[i] << ", " << heads[nodeList[i]]->val << endl;
			i += 2;		 //adding new destinations to the front of the list, not the back  
			j += 2; 
		}
	}
	
	void printList(int n) { //Prints adjacency list for test purposes 
		adjNode* curr = new adjNode; 
		for (int i = 0; i < n; i++) {
			curr = heads[i]; //pointer that iterates through the vector 
			cout << i << ": "; 
			while (curr != nullptr) { //While there is a list available 
				cout << curr->val << " "; //Print out the adjacent nodes and increment curr 
				curr = curr->next; 
			}
			cout << endl; 
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
	Graph graph(graphList); 
	graph.printList(5); 
	return 0; // Hi Justin <3
};