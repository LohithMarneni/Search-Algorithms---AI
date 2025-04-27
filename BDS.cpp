#include <bits/stdc++.h>
using namespace std;

const int max_nodes = 50;
const int INF = INT_MAX;

void bidirectionalSearch(int n, int adj[max_nodes][max_nodes], int src, int goal) {
    if (src == goal) {
        cout << "Source and Goal are the same!" << endl;
        return;
    }

    bool vis1[max_nodes] = {false}, vis2[max_nodes] = {false};
    int prev1[max_nodes], prev2[max_nodes];
    int cost1[max_nodes], cost2[max_nodes]; // Cost arrays to track distances
    int queue1[max_nodes], queue2[max_nodes];
    int front1 = 0, rear1 = 0, front2 = 0, rear2 = 0;

    // Initialize arrays
    for (int i = 0; i < max_nodes; i++) {
        prev1[i] = -1;
        prev2[i] = -1;
        cost1[i] = INF;
        cost2[i] = INF;
    }

    // Start BFS from src (forward) and goal (backward)
    queue1[rear1++] = src;
    vis1[src] = true;
    cost1[src] = 0;

    queue2[rear2++] = goal;
    vis2[goal] = true;
    cost2[goal] = 0;

    bool found = false;
    int meetNode = -1;

    while (front1 < rear1 && front2 < rear2) {
        // BFS from src to goal (forward search)
        int node1 = queue1[front1++];
        for (int ne = 0; ne < n; ne++) {
            if (adj[node1][ne] > 0 && !vis1[ne]) {
                vis1[ne] = true;
                prev1[ne] = node1;
                queue1[rear1++] = ne;
                cost1[ne] = cost1[node1] + adj[node1][ne]; // Update cost

                if (vis2[ne]) {
                    found = true;
                    meetNode = ne;
                    break;
                }
            }
        }

        // BFS from goal to src (backward search)
        if (!found) {
            int node2 = queue2[front2++];
            for (int ne = 0; ne < n; ne++) {
                if (adj[node2][ne] > 0 && !vis2[ne]) {
                    vis2[ne] = true;
                    prev2[ne] = node2;
                    queue2[rear2++] = ne;
                    cost2[ne] = cost2[node2] + adj[node2][ne]; // Update cost

                    if (vis1[ne]) {
                        found = true;
                        meetNode = ne;
                        break;
                    }
                }
            }
        }
    }

    if (!found) {
        cout << "No Path" << endl;
        return;
    }

    // Reconstruct the path
    int path[max_nodes], pl = 0;
    int tempNode = meetNode;

    // Trace path from meetNode to src (forward path)
    while (tempNode != -1) {
        path[pl++] = tempNode;
        tempNode = prev1[tempNode];
    }

    // Reverse the path from src to meetNode
    for (int i = 0; i < pl / 2; i++) {
        swap(path[i], path[pl - 1 - i]);
    }

    // Trace path from meetNode to goal (backward path)
    tempNode = prev2[meetNode];
    while (tempNode != -1) {
        path[pl++] = tempNode;
        tempNode = prev2[tempNode];
    }

    // Output the path and total cost
    cout << "Path from " << src << " to " << goal << " is: ";
    for (int i = 0; i < pl; i++) {
        cout << path[i] << (i < pl - 1 ? " -> " : "");
    }
    cout << endl;
    cout << "Total Cost: " << cost1[meetNode] + cost2[meetNode] << endl; // Total cost from src to goal
}

int main() {
    int n = 5; // Example number of nodes
    int src = 0, goal = 4; // Example source and goal nodes
    int adj[max_nodes][max_nodes] = { // Example adjacency matrix
        {0, 5, 0, 0, 0},
        {5, 0, 7, 10, 0},
        {0, 7, 0, 3, 0},
        {0, 10, 3, 0, 6},
        {0, 0, 0, 6, 0}
    };
    bidirectionalSearch(n, adj, src, goal);

    return 0;
}