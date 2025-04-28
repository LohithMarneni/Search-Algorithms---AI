#include <iostream>
#include <cmath>
using namespace std;
const int MAX_NODES = 50;
const int INF = 1e9; // A very large value
void aStarSearch(int n, int adj[MAX_NODES][MAX_NODES], int heuristic[MAX_NODES], int start, int goal) {
    int g[MAX_NODES];          // Cost to reach each node (g(n))
    int f[MAX_NODES];          // Estimated total cost (f(n) = g(n) + h(n))
    int visited[MAX_NODES];    // 0 = unvisited, 1 = visited
    int parent[MAX_NODES];     // To reconstruct the path
    int processList[MAX_NODES]; // List to manage nodes to process
    int front = 0, rear = 0;
    // Initialize arrays
    for (int i = 0; i < n; i++) {
        g[i] = INF;
        f[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    g[start] = 0;
    f[start] = heuristic[start]; // Initial f value for start node
    processList[rear++] = start;
    while (front < rear) {
        // Find the node with the minimum f value
        int minF = INF, minIndex = -1;
        for (int i = front; i < rear; i++) {
            int node = processList[i];
            if (!visited[node] && f[node] < minF) {
                minF = f[node];
                minIndex = i;
            }
        }
        if (minIndex == -1) break;
        // Remove the node with the minimum f value from the process list
        int currentNode = processList[minIndex];
        for (int i = minIndex; i < rear - 1; i++) {
            processList[i] = processList[i + 1];
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
                int newG = g[currentNode] + adj[currentNode][neighbor];
                if (newG < g[neighbor]) {
                    g[neighbor] = newG;
                    f[neighbor] = g[neighbor] + heuristic[neighbor];
                    parent[neighbor] = currentNode;
                    processList[rear++] = neighbor; // Add the neighbor to the process list
                }
            }
        }
    }
    if (f[goal] == INF) {
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
    cout << "Total Cost: " << g[goal] << endl;
}

int main() {
    int n=6;
    int adj[MAX_NODES][MAX_NODES]={
        {0,2,0,3,0,0},
        {2,0,1,0,0,9},
        {0,1,0,0,0,0},
        {3,0,0,0,6,0},
        {0,0,0,6,0,1},
        {0,9,0,0,1,0}
    };
    int heuristic[MAX_NODES]={11,6,99,7,1,0};  // Heuristic values for each node
    int start=0, goal=5;
    aStarSearch(n, adj, heuristic, start, goal);
    return 0;
}
