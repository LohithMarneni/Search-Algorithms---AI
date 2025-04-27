#include <iostream>
using namespace std;

const int MAX = 100;
const int INF = 1000000; // large value as infinity

// To print the path
void printPath(int parent[], int goal) {
    int path[MAX];
    int index = 0;
    int current = goal;
    
    while (current != -1) {
        path[index++] = current;
        current = parent[current];
    }
    
    cout << "Path: ";
    for (int i = index - 1; i >= 0; i--) {
        cout << path[i] << " ";
    }
    cout << endl;
}

// Uniform Cost Search without Priority Queue
void ucs(int graph[MAX][MAX], int start, int goal, int n) {
    int parent[MAX];
    int pathCost[MAX];
    bool visited[MAX];
    
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
        pathCost[i] = INF;
        visited[i] = false;
    }
    
    pathCost[start] = 0;
    
    for (int count = 0; count < n; count++) {
        // Find the unvisited node with the smallest path cost
        int minCost = INF;
        int current = -1;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i] && pathCost[i] < minCost) {
                minCost = pathCost[i];
                current = i;
            }
        }
        
        if (current == -1) {
            break; // No reachable unvisited node
        }
        
        visited[current] = true;
        
        if (current == goal) {
            cout << "Goal reached with a path cost of " << pathCost[current] << endl;
            printPath(parent, goal);
            return;
        }
        
        for (int i = 0; i < n; i++) {
            if (graph[current][i] > 0 && !visited[i]) {
                int newCost = pathCost[current] + graph[current][i];
                if (newCost < pathCost[i]) {
                    pathCost[i] = newCost;
                    parent[i] = current;
                }
            }
        }
    }
    
    cout << "Goal can't be reached!" << endl;
}

int main() {
    int n, start, goal;
    int graph[MAX][MAX];
    
    cout << "Enter number of nodes: ";
    cin >> n;
    
    cout << "Enter adjacency matrix: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Enter cost for node " << i << " to node " << j << ": ";
            cin >> graph[i][j];
        }
    }
    
    cout << "Enter start node: ";
    cin >> start;
    
    cout << "Enter goal node: ";
    cin >> goal;
    
    ucs(graph, start, goal, n);
    
    return 0;
}