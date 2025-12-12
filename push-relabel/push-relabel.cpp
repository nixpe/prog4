#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void pushFlow(int u, int v,
              vector<vector<int>> &capacity,
              vector<vector<int>> &flow,
              vector<int> &excess,
              queue<int> &active,
              int source, int sink)
{
    int available = capacity[u][v] - flow[u][v];
    int send = min(excess[u], available);

    if (send <= 0)
        return;

    flow[u][v] += send;
    flow[v][u] -= send;

    excess[u] -= send;
    excess[v] += send;

    if (v != source && v != sink && excess[v] == send)
        active.push(v);
}

void relabelNode(int u,
                 const vector<vector<int>> &capacity,
                 const vector<vector<int>> &flow,
                 vector<int> &height, int n)
{
    int minHeight = 1e9;

    for (int v = 0; v < n; v++)
        if (capacity[u][v] - flow[u][v] > 0)
            minHeight = min(minHeight, height[v]);

    if (minHeight < 1e9)
        height[u] = minHeight + 1;
}

void dischargeNode(int u,
                   vector<vector<int>> &capacity,
                   vector<vector<int>> &flow,
                   vector<int> &height,
                   vector<int> &excess,
                   vector<int> &nextEdge,
                   queue<int> &active,
                   int source, int sink, int n)
{
    while (excess[u] > 0)
    {
        if (nextEdge[u] < n)
        {
            int v = nextEdge[u];

            if (capacity[u][v] - flow[u][v] > 0 &&
                height[u] == height[v] + 1)
                pushFlow(u, v, capacity, flow, excess, active, source, sink);

            else
                nextEdge[u]++;
        }

        else
        {
            relabelNode(u, capacity, flow, height, n);
            nextEdge[u] = 0;
        }
    }
}

int pushRelabelMaxFlow(int n, int source, int sink,
                       vector<vector<int>> &capacity)
{
    vector<vector<int>> flow(n, vector<int>(n, 0));
    vector<int> height(n, 0);
    vector<int> excess(n, 0);
    vector<int> nextEdge(n, 0);
    queue<int> active;

    height[source] = n;

    for (int v = 0; v < n; v++)
    {
        if (capacity[source][v] > 0)
        {
            int cap = capacity[source][v];

            flow[source][v] = cap;
            flow[v][source] = -cap;

            excess[v] = cap;
            excess[source] -= cap;

            if (v != source && v != sink)
                active.push(v);
        }
    }

    while (!active.empty())
    {
        int u = active.front();
        active.pop();

        dischargeNode(u, capacity, flow, height, excess, nextEdge, active, source, sink, n);

        if (u != source && u != sink && excess[u] > 0)
            active.push(u);
    }

    return excess[sink];
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> capacity(n, vector<int>(n, 0));

    for (int i = 0; i < m; i++)
    {
        int u, v, cap;
        cin >> u >> v >> cap;
        capacity[u][v] += cap;
    }

    int result = pushRelabelMaxFlow(n, 0, n - 1, capacity);

    cout << result;

    return 0;
}
