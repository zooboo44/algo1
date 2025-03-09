// Christian Ziobro
#include <iostream>
#include <vector>
using namespace std;

bool bfsCycle(int n, vector<vector<int>>& adj, 
    vector<bool>& visited, int parent) {
                      
    visited[n] = true;

    for(int i = 0; i < adj[n].size(); i++){
        
        if (!visited[i]) {
            if (bfsCycle(i, adj, visited, n)){
                return true;
            }
        }
        //base case for recursive function, if the current node does != the parent, return true as it is a cycle
        else if (i != parent){
            return true;
        }
    }
    
    return false;
}

bool isCycle(vector<vector<int>>& adj) {
    //number of nodes(size of adjacent list vector)
    int n = adj.size();
    
    //create vector of visited nodes, initialize all to false
    vector<bool> visited(n, false);

    //iterate through adjacent list vector
    for (int i = 0; i < n; i++) {
        //if not visited (it wont be as this is the first call of the function)
        if (!visited[i]){
            //if the call to the bfsCycle function returns true, this function returns true as it is a cycle
            if (bfsCycle(i, adj, visited, -1)){
                return true;
            }
        }
    }
    
    //returns false as the graph is not a cycle
    return false;
}

int main() {
    int n = 0;
    cout << "Enter the number of nodes: ";
    cin >> n;
    vector<vector<int>> adj(n);

    for(int parent = 0; parent < n; parent++){
        cout << "Enter child nodes of parent: " << parent << ": " << endl;
        int child = 0;
        while(child != -1){
            cin >> child;
            adj[parent].push_back(child);
            adj[child].push_back(parent);
        }
    }

    adj[0].push_back(1);
    adj[1].push_back(0);
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(2);
    adj[3].push_back(4);
    adj[4].push_back(3);
    adj[4].push_back(5);
    adj[5].push_back(4);
    
    //calls the isCycle function to determine if the graph is a cycle or not
    if (isCycle(adj)) {
        cout << "Loop detected" << endl;
    } else {
        cout << "No loop detected" << endl;
    }
}
