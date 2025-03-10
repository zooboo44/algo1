// Christian Ziobro, ziobro44@csu.fullerton.edu
#include <iostream>
#include <vector>
using namespace std;

bool bfsLoop(int i, int parent, vector<vector<int>>& adj, vector<bool>& visited) {

    //mark current node as visited in the visited array
    visited[i] = true;

    for (int child : adj[i]) {
        //if the current node is not marked as visited, 
        if (!visited[child]) {
            //call bfsLoop recursively on the child node
            if (bfsLoop(child, i, adj, visited)) {
                return true;
            }
        }
        //base case for recursive function, if the current node does != the parent, return true as it is a cycle
        else if (child != parent) {
            return true;
        }
    }

    return false;
}

bool loopDetection(vector<vector<int>>& adj) {
    //number of nodes (size of adjacent list vector)
    int n = adj.size();

    //create vector of visited nodes, initialize all to false
    vector<bool> visited(n, false);

    //iterate through parent nodes, if the parent node hasn't been visited, it calls the bfsLoop function to determine if there is a loop
    for (int i = 0; i < n; i++) {

        if (!visited[i]) {
            if (bfsLoop(i, -1, adj, visited)) { //calls bfsLoop on the 1st (0) node, which is why the parent variable is -1
                return true;
            }
        }
    }

    return false;
}

void fillAdjacencyList(vector<vector<int>>& adj, int n) {
    //iterate through vector of parent nodes
    for (int parent = 0; parent < n; parent++) {
        //prompts user to enter child node of current parent
        cout << "Enter child nodes of parent: " << parent << ": " << endl;
        int child = 0;
        while (true) {
            //takes user input of child nodes, if input == -1, then it moves on to the next parent
            cin >> child;
            if (child == -1) {
                break;
            }
            //fills the adjacency list of the parent to the child, and the child to the parent to make an undirected graph
            adj[parent].push_back(child);
            adj[child].push_back(parent);
        }
    }
}

int main() {
    int n = 0;
    cout << "Enter the number of nodes: ";
    cin >> n;
    if (n <= 0) {
        cout << "Enter a whole number greater than 0" << endl;
        exit(1);
    }
    vector<vector<int>> adj(n);
    //prompts user to fill out adjacency list
    fillAdjacencyList(adj, n);
    
    //n = 3, loop detected
    /*adj[1].push_back(0);
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[2].push_back(0);
    adj[1].push_back(2);
    adj[2].push_back(1);*/

    //n = 3, no loop detected
    /*adj[0].push_back(1);
    adj[1].push_back(0);
    adj[1].push_back(2);
    adj[2].push_back(1);*/

    //calls the isCycle function to determine if the graph is a cycle or not
    if (loopDetection(adj)) {
        cout << "Loop detected" << endl;
    }
    else {
        cout << "No loop detected" << endl;
    }
}
