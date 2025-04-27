#include <bits/stdc++.h>
using namespace std;
const int MAX_NODES = 50;
const int INF = INT_MAX; 
void uniformCostSearch(int n, int adj[MAX_NODES][MAX_NODES], int start, int goal) {
    int cost[MAX_NODES];          // Total cost to reach each node
    int visited[MAX_NODES]={0};       // 0 = unvisited, 1 = visited
    int parent[MAX_NODES];        // To reconstruct the path
    int priority_queue[MAX_NODES];   // Like a queue, but manual priority
    int front = 0, rear = 0;
    // Initialize arrays
    for (int i = 0; i < n; i++) {
        cost[i] = INF;
        parent[i] = -1;
    }

    cost[start] = 0;
    priority_queue[rear++] = start;

    while (front < rear) {
        // Find the node with the minimum cost
        int minCost = INF, minIndex = -1;
        for (int i = front; i < rear; i++) {
            int node = priority_queue[i];
            if (!visited[node] && cost[node] < minCost) {
                minCost = cost[node];
                minIndex = i;
            }
        }

        if (minIndex == -1) break;

        // Remove the node with the minimum cost from the process list
        int currentNode = priority_queue[minIndex];
        for (int i = minIndex; i < rear - 1; i++) {
            priority_queue[i] = priority_queue[i + 1];
        }
        rear--;
        
        visited[currentNode] = 1;

        // If goal is reached, break the loop
        if (currentNode == goal) {
            break;
        }

        // Explore neighbors of the current node
        for (int neighbor = 0; neighbor < n; neighbor++) {
            if (adj[currentNode][neighbor] > 0 && !visited[neighbor]) {
                int newCost = cost[currentNode] + adj[currentNode][neighbor];
                if (newCost < cost[neighbor]) {
                    cost[neighbor] = newCost;
                    parent[neighbor] = currentNode;
                    priority_queue[rear++] = neighbor; // Add the neighbor to the process list
                }
            }
        }
    }

    if (cost[goal] == INF) {
        cout << "No path found." << endl;
        return;
    }

    // Reconstruct the path
    int path[MAX_NODES], pathLength = 0;
    for (int node = goal; node != -1; node = parent[node]) {
        path[pathLength++] = node;
    }

    // Output the path
    cout << "Path: ";
    for (int i = pathLength - 1; i >= 0; i--) {
        cout << path[i] << " ";
    }
    cout << endl;
    cout << "Total Cost: " << cost[goal] << endl;
}

int main() {
    
    int n = 5; // Example number of nodes
    int src = 0, goal = 4; // Example source and goal nodes
    int adj[MAX_NODES][MAX_NODES] = { // Example adjacency matrix
        {0, 5, 0, 0, 0},
        {5, 0, 7, 10, 0},
        {0, 7, 0, 3, 0},
        {0, 10, 3, 0, 6},
        {0, 0, 0, 6, 0}
    };
    uniformCostSearch(n, adj, src, goal);
    return 0;
}
