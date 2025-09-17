#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<int> bellman_ford(const vector<vector<vector<int>>> &adj, int n, int src = 0)
{
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        bool changed = false;

        for (int u = 0; u < n; u++)
        {
            if (dist[u] == INT_MAX)
                continue;

            for (const auto &edge : adj[u])
            {
                int v = edge[0];
                int wt = edge[1];

                if (dist[u] + wt < dist[v])
                {
                    dist[v] = dist[u] + wt;
                    changed = true;
                }
            }
        }

        if (!changed)
            break;
    }

    vector<bool> neg_cycle(n, false);
    queue<int> q;

    for (int u = 0; u < n; u++)
    {
        if (dist[u] == INT_MAX)
            continue;

        for (const auto &edge : adj[u])
        {
            int v = edge[0];
            int wt = edge[1];

            if (dist[u] + wt < dist[v])
            {
                if (!neg_cycle[v])
                {
                    neg_cycle[v] = true;
                    q.push(v);
                }
            }
        }
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (const auto &edge : adj[u])
        {
            int v = edge[0];

            if (!neg_cycle[v])
            {
                neg_cycle[v] = true;
                q.push(v);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (neg_cycle[i])
            dist[i] = INT_MIN;
    }

    return dist;
}

istream &operator>>(istream &is, vector<vector<vector<int>>> &adj)
{
    int e;
    is >> e;

    for (int i = 0; i < e; i++)
    {
        int u, v, wt;
        is >> u >> v >> wt;

        adj[u].push_back({v, wt});
    }

    return is;
}

ostream &operator<<(ostream &os, const vector<int> &dist)
{
    for (const auto &d : dist)
    {
        if (d == INT_MAX)
            os << "INF" << " ";

        else if (d == INT_MIN)
            os << "NEG_CYCLE" << " ";

        else
            os << d << " ";
    }

    return os;
}

int main()
{
    int n;
    cin >> n;

    vector<vector<vector<int>>> adj(n);
    cin >> adj;

    vector<int> dist = bellman_ford(adj, n);
    cout << dist;

    return 0;
}