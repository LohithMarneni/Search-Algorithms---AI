#include <iostream>
#include <climits>
using namespace std;

const int max_nodes = 50;

void dfsWithCost(int n, int adj[max_nodes][max_nodes], int src, int goal, int depth_limit) {
    bool vis[max_nodes] = {false};  // Visited array
    int cost[max_nodes];            // Array to store the cost to reach each node
    int prev[max_nodes];            // Array to track the previous node for path reconstruction
    int stack[max_nodes];           // Array to simulate the stack
    int top = -1;                   // Stack pointer (top of the stack)
    int depth[max_nodes];           // Array to store the depth of each node

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        cost[i] = INT_MAX;   // Initialize all costs to infinity
        prev[i] = -1;        // No previous node initially
        depth[i] = -1;       // No depth initially
    }
    
    stack[++top] = src;         // Push the source node onto the stack
    cost[src] = 0;              // Cost to reach the source is 0
    depth[src] = 0;             // The depth of the source node is 0

    // DFS loop using an explicit stack (array-based)
    while (top >= 0) {
        int node = stack[top];  // Peek the top node without popping it

        // If we reached the goal node, we can stop
        if (node == goal) {
            break;
        }

        bool isAnyUnvisitedNeighbor = false; // Flag to check if we have any unvisited neighbors

        // Explore all the neighbors of the current node
        for (int ne = 0; ne < n; ne++) {
            if (adj[node][ne] > 0 && !vis[ne] && depth[node] < depth_limit) {  // If there's an edge, the neighbor isn't visited, and we're within the depth limit
                isAnyUnvisitedNeighbor = true;  // We found an unvisited neighbor
                cost[ne] = cost[node] + adj[node][ne];  // Update the cost to reach the neighbor
                prev[ne] = node;           // Set the current node as the previous node for the neighbor
                depth[ne] = depth[node] + 1;  // Increment the depth for the neighbor
                stack[++top] = ne;         // Push the neighbor onto the stack
            }
        }

        // After exploring neighbors, mark the node as visited (only once all neighbors are processed)
        vis[node] = true;

        if (!isAnyUnvisitedNeighbor) {
            // If no unvisited neighbors, pop the current node from the stack
            top--;
        }
    }

    // If the goal node is unreachable
    if (cost[goal] == INT_MAX) {
        cout << "No Path" << endl;
        return;
    }

    // Reconstruct and print the path from source to goal
    int path[max_nodes];
    int pathLen = 0;
    for (int at = goal; at != -1; at = prev[at]) {
        path[pathLen++] = at;
    }

    cout << "Path from " << src << " to " << goal << " is: ";
    for (int i = pathLen - 1; i >= 0; i--) {
        cout << path[i] << (i > 0 ? " -> " : "");
    }
    cout << endl;
    cout << "Cost: " << cost[goal] << endl;
}

int main() {
    int n = 5; // Example number of nodes
    int src = 0, goal = 4; // Example source and goal nodes
    int depth_limit = 3; // Example depth limit
    int adj[max_nodes][max_nodes] = { // Example adjacency matrix
        {0,5,0,0,0},
        {5,0,7,10,0},
        {0,7,0,3,0},
        {0,10,3,0,6},
        {0,0,0,6,0}
    };
    dfsWithCost(n, adj, src, goal, depth_limit);
    return 0;
}
