#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

int find_max_node(const vector<vector<int>> &edges)
{
    int max_node = 0;
    for (const auto &edge : edges)
        max_node = max({max_node, edge[0], edge[1]});

    return max_node;
}

void gen_adj_list(vector<vector<vector<int>>> &adj_list, const vector<vector<int>> &edges)
{
    for (const auto &edge : edges)
    {
        int u = edge[0], v = edge[1], weight = edge[2];
        adj_list[u].push_back({v, weight});
        adj_list[v].push_back({u, weight});
    }
}

vector<int> dijkstra(const vector<vector<int>> &edges, int src = 0)
{
    int n = find_max_node(edges);
    vector<vector<vector<int>>> adj_list(n + 1);

    gen_adj_list(adj_list, edges);

    vector<int> dist(n + 1, INT_MAX);
    dist[src] = 0;

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    pq.push({0, src});

    while (!pq.empty())
    {
        int curr_dist = pq.top()[0];
        int curr_node = pq.top()[1];
        pq.pop();

        if (curr_dist > dist[curr_node])
            continue;

        for (const auto &edge : adj_list[curr_node])
        {
            int adj_node = edge[0];
            int edge_weight = edge[1];

            if (curr_dist + edge_weight < dist[adj_node])
            {
                dist[adj_node] = curr_dist + edge_weight;
                pq.push({dist[adj_node], adj_node});
            }
        }
    }

    return dist;
}

ostream &operator<<(ostream &os, const vector<int> &dist)
{
    for (const auto &d : dist)
        os << d << " ";
    os << endl;

    return os;
}

int main()
{
    vector<vector<int>> edges = {{0, 1, 4}, {0, 2, 8}, {1, 4, 6}, {2, 3, 2}, {3, 4, 10}, {5, 6, 6}, {4, 3, 3}, {0, 6, 1}, {7, 3, 4}, {5, 2, 6}};
    vector<int> dist = dijkstra(edges);

    cout << dist;

    return 0;
}