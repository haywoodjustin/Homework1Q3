#include <iostream>
#include <vector>
#include <string>

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
			edgeAddition(nodeList[i], nodeList[j]);
			i += 2;		 //adding new destinations to the front of the list, not the back  
			j += 2;
		}
	}

	void printList() { //Prints adjacency list for test purposes 
		adjNode* curr = new adjNode;
		for (int i = 0; i < numNodes; i++) {
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

	string edgeAddition(int first, int second) {
		if (first > numNodes || second > numNodes) {
			return "Invalid vertex given."; // Can't add an edge to a vertex that doesn't exist.
		}
		adjNode* edge = new adjNode;
		edge->val = second;
		if (heads[first] == NULL) { //If head is null, add with no other work needed 
			heads[first] = edge;
		}
		else {
			// We will search to see if the edge already exists first. We only need to do this once since the
			// graph is bidirectional. Also, this wouldn't apply to the above condition because if heads[first]
			// is empty then the edge cannot already exist.
			adjNode* currNode = heads[first];
			while (currNode != nullptr) {
				if (currNode->val == second) {
					return "The edge already exists.";
				}
				currNode = currNode->next;
			}

			edge->next = heads[first]->next;
			heads[first]->next = edge; // If head is not null, add the edge to the front of the list.
		}
		edge = new adjNode;
		edge->val = first;
		if (heads[second] == NULL) { //If head is null, add with no other work needed 
			heads[second] = edge;
		}
		else {
			edge->next = heads[second]->next;
			heads[second]->next = edge; // If head is not null, add the edge to the front of the list.
		}
		return "Edge added succesfully.";
	}

	string edgeDeletion(int first, int second) {
		if (first > numNodes || second > numNodes) {
			return "Invalid vertex given."; // Can't delete an edge to a vertex that doesn't exist.
		}
		if (heads[first] == NULL) {
			// There are no edges associated with the given from vertex.
			return "Given source vertex does not have any associated edges.";
		}
		adjNode* currNode = heads[first];
		if (heads[first]->val == second) { //If the first node is the given node 
			currNode = heads[first];
			heads[first] = currNode->next;
			delete currNode;
			return "Edge deleted succesfully";
		}
		adjNode* prev = new adjNode;
		while (currNode->next != NULL) { //If we need to search the list for the given node 
			if (currNode->next->val == second) {
				prev = currNode;    //Assign previous pointer to node behind deletion node
				currNode = currNode->next;
			}
			prev->next = currNode->next; //Link previous node to node ahead of deletion node 
			delete currNode;  //Delete given node 
			return "Edge deleted succesfully";
		}
		return "Edge was not found";
	}

	~Graph() {
		//delete& heads;
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
	mark[v] = 1;
	if (G.heads[v] == NULL) {
		return { v };
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

string Components(Graph G) {
	vector<int> mark;
	vector<int> parent;
	string result = "";
	for (unsigned int i = 0; i < G.getNumNodes(); i++) {
		parent.push_back(-1);
		mark.push_back(0);
	}
	// Get the parent array in order before we format the result string
	for (unsigned int i = 0; i < G.getNumNodes(); i++) {
		if (mark[i] == 0) {
			vector<int> temp = DFS(G, i);
			for (unsigned int j = 0; j < temp.size(); j++) {
				mark[temp[j]] = 1;
				if (temp[j] != i) {
					parent[temp[j]] = i;
				}
			}
		}
	}
	// Now we can format the result string using the completed parent list.
	for (unsigned int i = 0; i < parent.size(); i++) {
		if (parent[i] == -1) {
			// Theoretically, there should only be one vertex with a value of -1 for the parent
			// per connected component. Therefore, doing a DFS on that vertex will yield it's
			// respective component.
			result += "{";
			vector<int> temp = DFS(G, i);
			for (unsigned int j = 0; j < temp.size(); j++) {
				if (j == temp.size() - 1) {
					result += to_string(temp[j]) + "}";
				}
				else {
					result += to_string(temp[j]) + ", ";
				}
			}
		}
	}
	return result;
}

int main() {

	int graphList[12] = { 5,0,1,1,4,2,3,1,3,3,4,-1 };
	Graph graph(graphList);
	graph.printList();
	vector<int> output = DFS(graph, 1);
	cout << endl;
	for (int i = 0; i < output.size(); i++) {
		cout << output[i] << " ";
	}
	cout << endl;
	cout << graph.edgeAddition(4, 3) << endl;
	cout << endl;
	graph.printList();
	cout << endl;
	cout << graph.edgeDeletion(4, 3) << endl;
	cout << endl;
	graph.printList();
	cout << endl;
	cout << Components(graph) << endl;
	cout << endl;
	return 0;
}