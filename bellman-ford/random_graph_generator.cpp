#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void generate_random_graph(vector<vector<int>> &edges, int n, int e, int min_wt = -20, int max_wt = 20)
{
    for (int i = 0; i < e; i++)
    {
        int u = rand() % n;
        int v = rand() % n;

        int w = min_wt + rand() % (max_wt - min_wt + 1);

        edges.push_back({u, v, w});
    }
}

ostream &operator<<(ostream &os, const vector<vector<int>> &edges)
{
    for (const auto &edge : edges)
        os << edge[0] << " " << edge[1] << " " << edge[2] << endl;

    return os;
}

int main()
{
    srand(time(0));

    int n, e;
    cin >> n >> e;

    vector<vector<int>> edges;
    generate_random_graph(edges, n, e);

    cout << n << " " << e << endl;
    cout << edges;

    return 0;
}