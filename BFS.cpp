#include <bits/stdc++.h>
using namespace std;

const int max_nodes = 50;
const int INF = INT_MAX;

void bfs(int n, int adj[max_nodes][max_nodes], int src, int goal) {
    bool vis[max_nodes] = {false};
    int prev[max_nodes], cost[max_nodes];
    int queue[max_nodes];//hi
    int front = 0, rear = 0;

    // Initialize arrays
    for (int i = 0; i < max_nodes; i++) {
        prev[i] = -1;
        cost[i] = INF;
    }

    // Start BFS
    queue[rear++] = src;
    vis[src] = true;
    cost[src] = 0;

    while (front < rear) {  
        int node = queue[front++];
        if (node == goal) break;

        for (int ne = 0; ne < n; ne++) {
            if (adj[node][ne] > 0 && !vis[ne]) {
                cost[ne] = cost[node] + adj[node][ne];
                queue[rear++] = ne;
                vis[ne] = true;
                prev[ne] = node;
            }
        }
    }

    if (cost[goal] == INF) {
        cout << "No Path" << endl;
        return;
    }
    int path[max_nodes], pl = 0;
    for (int at = goal; at != -1; at = prev[at]) {
        path[pl++] = at;
    }
    cout << "Path from " << src << " to " << goal << " is: ";
    for (int i = pl - 1; i >= 0; i--) {
        cout << path[i] << (i > 0 ? " -> " : "");
    }
    cout << endl;
    cout << "Cost: " << cost[goal] << endl;
}

int main() {
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;

    int src, goal;
    cout << "Enter the source and goal nodes: ";
    cin >> src >> goal;

    if (src < 0 || src >= n || goal < 0 || goal >= n) {
        cout << "Invalid source or goal node!" << endl;
        return 0;
    }

    int adj[max_nodes][max_nodes];
    cout << "Enter the adjacency matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }

    bfs(n, adj, src, goal);

    return 0;
}