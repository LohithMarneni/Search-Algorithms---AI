#include <iostream>
#include <cmath>
using namespace std;

const int MAX_NODES = 50;
const int INF = 1e9; // A very large value

void bestFirstSearch(int n, int adj[MAX_NODES][MAX_NODES], int heuristic[MAX_NODES], int start, int goal) {
    int visited[MAX_NODES];    // 0 = unvisited, 1 = visited
    int parent[MAX_NODES];     // To reconstruct the path
    int cost[MAX_NODES];       // Cost array to track cumulative cost
    int processList[MAX_NODES]; // List to manage nodes to process
    int front = 0, rear = 0;

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        parent[i] = -1;
        cost[i] = INF;
    }

    processList[rear++] = start;
    visited[start] = 1;
    cost[start] = 0;

    while (front < rear) {
        // Find the node with the minimum heuristic value
        int minHeuristic = INF, minIndex = -1;
        for (int i = front; i < rear; i++) {
            int node = processList[i];
            if (heuristic[node] < minHeuristic) {
                minHeuristic = heuristic[node];
                minIndex = i;
            }
        }

        if (minIndex == -1) break;

        // Remove the node with the minimum heuristic value from the process list
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
                int newCost = cost[currentNode] + adj[currentNode][neighbor];
                if (newCost < cost[neighbor]) {
                    cost[neighbor] = newCost;
                    parent[neighbor] = currentNode;
                }
                processList[rear++] = neighbor; // Add the neighbor to the process list
            }
        }
    }

    if (visited[goal] == 0) {
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

    // Output the total cost
    cout << "Total Cost: " << cost[goal] << endl;
}

int main() {
    int n=9;
    int start=0, goal=8;
    int adj[MAX_NODES][MAX_NODES]=
    {
        {0,5,2,3,0,0,0,0,0},
        {5,0,0,0,0,0,0,0,0},
        {2,0,0,0,4,9,0,0,0},
        {3,0,0,0,0,0,0,0,0},
        {0,0,4,0,0,0,0,0,0},
        {0,0,9,0,0,0,9,8,0},
        {0,0,0,0,0,9,0,0,0},
        {0,0,0,0,0,8,0,0,6},
        {0,0,0,0,0,0,0,6,0}
    };
    int heuristic[MAX_NODES]={10,9,7,8,8,6,6,3,0};  // Heuristic values for each node

    bestFirstSearch(n, adj, heuristic, start, goal);

    return 0;
}