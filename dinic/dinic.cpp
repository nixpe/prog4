#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

bool bfs(int s, int t, const vector<vector<int>> &adj, const vector<vector<int>> &capacity, vector<int> &level)
{
    fill(level.begin(), level.end(), -1);
    level[s] = 0;

    queue<int> q;
    q.push(s);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : adj[u])
            if (capacity[u][v] > 0 && level[v] == -1)
            {
                level[v] = level[u] + 1;
                q.push(v);
            }
    }

    return level[t] != -1;
}

int dfs(int u, int t, int flow, vector<vector<int>> &capacity, const vector<vector<int>> &adj, const vector<int> &level)
{
    if (u == t)
        return flow;

    for (int v : adj[u])
    {
        if (capacity[u][v] > 0 && level[v] == level[u] + 1)
        {
            int new_flow = dfs(v, t, min(flow, capacity[u][v]), capacity, adj, level);

            if (new_flow > 0)
            {
                capacity[u][v] -= new_flow;
                capacity[v][u] += new_flow;
                return new_flow;
            }
        }
    }

    return 0;
}

int dinic(int n, int s, int t, vector<vector<int>> &capacity, const vector<vector<int>> &adj)
{
    vector<int> level(n);
    int max_flow = 0;

    while (bfs(s, t, adj, capacity, level))
        while (int new_flow = dfs(s, t, INT_MAX, capacity, adj, level))
            max_flow += new_flow;

    return max_flow;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> capacity(n, vector<int>(n, 0));
    vector<vector<int>> adj(n);

    for (int i = 0; i < m; i++)
    {
        int u, v, cap;
        cin >> u >> v >> cap;

        capacity[u][v] += cap;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << dinic(n, 0, n - 1, capacity, adj);

    return 0;
}