#include<stdio.h>
#include<stdbool.h> // include this to use true and false

#define M 20
#define INF 99999

int getMinNode(bool toExplore[], int g[], int h[], int n) {
    int mini = -1;
    int min_value = INF;
    for (int i = 0; i < n; i++) {
        if (toExplore[i] && (g[i] + h[i] < min_value)) {
            min_value = g[i] + h[i];
            mini = i;
        }
    }
    return mini;
}

void Astar(int adj[M][M], int heu[M], int n, int source, int goal) {
    bool toExplore[M] = {false}; // use bool array
    int g[M]; // stores the shortest known cost
    int parent[M];
    bool explored[M] = {false}; // use bool array

    for (int i = 0; i < n; i++) {
        g[i] = INF;
        parent[i] = -1;
    }
    g[source] = 0; 
    toExplore[source] = true; 

    while (1) {
        int curr = getMinNode(toExplore, g, heu, n);
        if (curr == -1 || curr == goal) { // no more node to explore or we got the node 
            break;
        }

        toExplore[curr] = false; // false is not yet to explored 
        explored[curr] = true; // true is explored

        for (int i = 0; i < n; i++) {
            if (adj[curr][i] > 0 && !explored[i]) {
                int newc = g[curr] + adj[curr][i];
                
                if (!toExplore[i] || newc < g[i]) {
                    g[i] = newc;
                    parent[i] = curr;
                    toExplore[i] = true;
                }
            }
        }
    }

    if (g[goal] == INF) {
        printf("No path found\n");
        return;
    }
    printf("Shortest path: ");
    int path[M], path_len = 0;
    for (int i = goal; i != -1; i = parent[i]) {
        path[path_len++] = i;
    }
    for (int i = path_len - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\nPath cost: %d\n", g[goal]);
}

int main() {
    int n, source, goal;
    int adj[M][M];
    int heu[M];

    printf("Enter the number of nodes: ");
    while (scanf("%d", &n) != 1 || n <= 0 || n > M) {
        printf("Invalid input. Enter a valid number of nodes (1 to %d): ", M);
        while (getchar() != '\n');
    }

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    printf("Enter heuristic values for each node:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &heu[i]);
    }

    printf("Enter the source node: ");
    scanf("%d", &source);
    printf("Enter the goal node: ");
    scanf("%d", &goal);

    Astar(adj, heu, n, source, goal);
    return 0;
}