/*COMSC 210 | Lab 34 | Lawrence Bryant
IDE used: Visual Studio Code | LLM used: ChatGPT*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int SIZE = 11;  // routers 0–10

struct Edge {
    int src, dest, weight;
};

typedef pair<int,int> Pair;   // (neighbor, weight)

class Graph {
public:
    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);

        for (auto &e : edges) {
            adjList[e.src].push_back(make_pair(e.dest, e.weight));
            adjList[e.dest].push_back(make_pair(e.src, e.weight)); // undirected
        }
    }

    // ----------------- PRINT GRAPH ----------------
    void printGraph() {
        cout << "\n=== Network Topology (Adjacency List) ===\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout << "Router " << i << " --> ";
            for (auto &p : adjList[i])
                cout << "(Router " << p.first << ", " << p.second << "ms) ";
            cout << endl;
        }
    }

    // --------------------- DFS ----------------------
    void DFSUtil(int node, vector<bool> &visited) {
        visited[node] = true;
        cout << "Router " << node << " ";

        for (int i = adjList[node].size() - 1; i >= 0; i--) {
            int next = adjList[node][i].first;
            if (!visited[next])
                DFSUtil(next, visited);
        }
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        cout << "\n=== DFS Diagnostic Trace from Router " << start << " ===\n";
        DFSUtil(start, visited);
        cout << "\n";
    }

    // --------------------- BFS ----------------------
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\n=== Broadcast Routing from Router " << start << " ===\n";

        while (!q.empty()) {
            int node = q.front(); q.pop();
            cout << "Router " << node << " ";

            for (auto &p : adjList[node]) {
                int next = p.first;
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
        cout << "\n";
    }

    // ---------------- DIJKSTRA SHORTEST PATH ----------------
    void shortestPath(int start, int end) {
        vector<int> dist(SIZE, INT_MAX);
        vector<int> parent(SIZE, -1);

        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int node = pq.top().second;
            int currentDist = pq.top().first;
            pq.pop();

            if (currentDist > dist[node]) continue;

            for (auto &edge : adjList[node]) {
                int next = edge.first;
                int weight = edge.second;

                if (dist[node] + weight < dist[next]) {
                    dist[next] = dist[node] + weight;
                    parent[next] = node;
                    pq.push({dist[next], next});
                }
            }
        }

        cout << "\n=== Shortest Path (Dijkstra) ===\n";
        cout << "From Router " << start << " to Router " << end << ":\n";

        if (dist[end] == INT_MAX) {
            cout << "No path exists.\n";
            return;
        }

        cout << "Total latency: " << dist[end] << " ms\n";

        vector<int> path;
        for (int v = end; v != -1; v = parent[v])
            path.push_back(v);

        reverse(path.begin(), path.end());

        cout << "Path: ";
        for (int node : path)
            cout << node << " ";
        cout << "\n";
    }

    // ------------------ MINIMUM SPANNING TREE (Prim's) ------------------
    void minimumSpanningTree() {
        vector<int> key(SIZE, INT_MAX);
        vector<int> parent(SIZE, -1);
        vector<bool> inMST(SIZE, false);

        key[0] = 0; // start from node 0
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push({0, 0}); // (key, node)

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            inMST[u] = true;

            for (auto &edge : adjList[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    pq.push({key[v], v});
                    parent[v] = u;
                }
            }
        }

        // Output MST
        cout << "\n=== Minimum Spanning Tree (Prim's Algorithm) ===\n";
        int totalCost = 0;
        for (int i = 1; i < SIZE; i++) {
            if (parent[i] != -1) {
                cout << "Router " << parent[i] << " - Router " << i 
                     << " : " << key[i] << " ms\n";
                totalCost += key[i];
            }
        }
        cout << "Total latency of MST: " << totalCost << " ms\n";
    }
};


// ==========================
//       MAIN APPLICATION
// ==========================

int main() {

    vector<Edge> edges = {
        {0,1,10}, {0,2,7}, {1,3,14}, {2,3,9},
        {2,4,11}, {3,5,6}, {4,6,13}, {5,7,8},
        {6,8,12}, {7,9,5}, {8,10,15},
        {4,7,4}, {2,9,3}, {1,8,16}
    };

    Graph network(edges);

    int choice = 0;
    int routerA, routerB;

    while (choice != 6) {
        cout << "\n==============================\n";
        cout << "   NETWORK ROUTING SIMULATOR\n";
        cout << "==============================\n";
        cout << "1. View Network Topology\n";
        cout << "2. Run DFS Diagnostic Trace\n";
        cout << "3. Simulate Broadcast Routing (BFS)\n";
        cout << "4. Shortest Path (Dijkstra)\n";
        cout << "5. Minimum Spanning Tree (Prim's)\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            network.printGraph();
            break;

        case 2:
            cout << "Enter starting router (0–10): ";
            cin >> routerA;
            if (routerA >= 0 && routerA < SIZE)
                network.DFS(routerA);
            else
                cout << "Invalid router ID.\n";
            break;

        case 3:
            cout << "Enter starting router (0–10): ";
            cin >> routerA;
            if (routerA >= 0 && routerA < SIZE)
                network.BFS(routerA);
            else
                cout << "Invalid router ID.\n";
            break;

        case 4:
            cout << "Enter source router (0–10): ";
            cin >> routerA;
            cout << "Enter destination router (0–10): ";
            cin >> routerB;

            if (routerA >= 0 && routerA < SIZE &&
                routerB >= 0 && routerB < SIZE)
                network.shortestPath(routerA, routerB);
            else
                cout << "Invalid router IDs.\n";
            break;

        case 5:
            network.minimumSpanningTree();
            break;

        case 6:
            cout << "Exiting simulator...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
