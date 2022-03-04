#include <iostream>
#include <vector>

using namespace std;

struct adjNode {
	int val = NULL;
	adjNode* next = nullptr;
};

class Graph {
	int numNodes;

public:
	vector<adjNode*> heads;  // {5,0,1,1,4,2,3,1,3,3,4,-1};
	Graph(int nodeList[]) {
		numNodes = nodeList[0]; // list[0] is the number of nodes in the graph.
		for (int i = 0; i < numNodes; i++) {
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
			curr = heads[i]; //pointer that iterates through the linked list 
			cout << i << ": ";
			while (curr != nullptr) { //While there is a list available 
				cout << curr->val << " "; //Print out the adjacent nodes and increment curr 
				curr = curr->next;
			}
			cout << endl;
		}
	}

	int getNumNodes() {
		return numNodes;
	}

	void edgeAddition(int from, int to) {
		if (from > numNodes || to > numNodes) {
			cout << "Invalid vertex given." << endl; // Can't add an edge to a vertex that doesn't exist.
		}
		adjNode* edge = new adjNode;
		edge->val = to;
		if (heads[from] == NULL) { //If head is null, add with no other work needed 
			heads[from] = edge;
		}
		else {
			adjNode* endNode = heads[from];
			while (endNode->next != NULL) { //If head is not null, iterate through edges, add to back 
				endNode = endNode->next;
			}
			endNode->next = edge;
		}
		cout << "Edge added succesfully." << endl;
	}

	void edgeDeletion(int from, int to) {
		if (from > numNodes || to > numNodes) {
			cout << "Invalid vertex given." << endl; // Can't delete an edge to a vertex that doesn't exist.
			return; 
		}
		if (heads[from] == NULL) {
			// There are no edges associated with the given from vertex.
			cout << "Given destination vertex does not have any associated edges." << endl; 
			return; 
		}
		adjNode* currNode = heads[from];
		if (heads[from]->val == to) { //If the first node is the given node 
			currNode = heads[from];
			heads[from] = currNode->next; 
			delete currNode; 
			cout << "Edge deleted succesfully" << endl; 
			return; 
		}
		adjNode* prev = new adjNode; 
		while (currNode->next != NULL) { //If we need to search the list for the given node 
			if (currNode->next -> val == to) {
				prev = currNode;    //Assign previous pointer to node behind deletion node
				currNode = currNode->next;  
			}
			prev->next = currNode->next; //Link previous node to node ahead of deletion node 
			delete currNode;  //Delete given node 
			cout << "Edge deleted succesfully" << endl;
			return; 
		}
		cout << "Edge was not found" << endl; 
	}

	~Graph() { 
		adjNode* curr = new adjNode; 
		for (int i = 0; i < 5; i++) {
			while (heads[i] != nullptr) {
				curr = heads[i];
				heads[i] = curr->next;
				delete curr;  //Delete all nodes in the list 
				curr = heads[i];
			}
			delete heads[i]; //Delete the pointers in the spaces of heads[i]
		}
		delete &heads; //Delete the entire vector heads 
	}
};

vector<int> DFS(Graph G, int v, vector<int> mark = {}) {
	vector<int> dfs;
	if (mark.empty()) {
		for (int i = 0; i < G.getNumNodes(); i++) {
			mark.push_back(0);
		}
	}
	dfs = { v };
	if (G.heads[v] == NULL) {
		return {v};
	}
	adjNode* currNode = G.heads[v];
	while (currNode != NULL) {
		if (mark[currNode->val] == 0) {
			vector<int> temp = DFS(G, currNode->val, mark);
			for (unsigned int i = 0; i < temp.size(); i++) {
				dfs.push_back(temp[i]);
			}
		}
		currNode = currNode->next;
		for (int i = 0; i < dfs.size(); i++) {
			mark[dfs[i]] = 1;
		}
	}
	return dfs;
};

int main() {

	int graphList[12] = { 5,0,1,1,4,2,3,1,3,3,4,-1 };
	Graph graph(graphList);
	graph.printList(5);
	vector<int> output = DFS(graph, 1);
	cout << endl;
	for (int i = 0; i < output.size(); i++) {
		cout << output[i] << " ";
	}
	graph.edgeDeletion(4, 3); 
	cout << endl;
	graph.printList(5);
	cout << endl; 
	return 0;
}