#include <iostream>
#include <vector>
#include <climits>
#include <string>

using namespace std;

vector<int> bellman_ford(const vector<vector<int>> &edges, int n, int src = 0)
{
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        bool changed = false;

        for (const auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            if (dist[u] != INT_MAX && dist[u] + wt < dist[v])
            {
                dist[v] = dist[u] + wt;
                changed = true;
            }
        }

        if (!changed)
            break;
    }

    for (const auto &edge : edges)
    {
        int u = edge[0];
        int v = edge[1];
        int wt = edge[2];

        if (dist[u] != INT_MAX && dist[u] + wt < dist[v])
            return {-1};
    }

    return dist;
}

istream &operator>>(istream &is, vector<vector<int>> &edges)
{
    for (auto &edge : edges)
    {
        int u, v, w;
        is >> u >> v >> w;
        edge = {u, v, w};
    }

    return is;
}

ostream &operator<<(ostream &os, const vector<int> &dist)
{
    for (const auto &d : dist)
        os << (d == INT_MAX ? "INF" : to_string(d)) << " ";

    return os;
}

int main()
{
    int n, e;
    cin >> n >> e;

    vector<vector<int>> edges(e);
    cin >> edges;

    vector<int> dist = bellman_ford(edges, n);
    cout << dist;

    return 0;
}