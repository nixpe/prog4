#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> gen_adj_list(const vector<pair<int, int>> &edges)
{
    int max_node = 0;
    for (const auto &edge : edges)
        max_node = max({max_node, edge.first, edge.second});

    vector<vector<int>> adj_list(max_node + 1);

    for (const auto &edge : edges)
    {
        adj_list[edge.first].push_back(edge.second);
        adj_list[edge.second].push_back(edge.first);
    }

    return adj_list;
}

ostream &operator<<(ostream &os, const vector<vector<int>> &adj_list)
{
    int i = 0;
    for (const auto &neighbors : adj_list)
    {
        os << i++ << " : ";
        for (const auto &node : neighbors)
            os << node << " ";
        os << endl;
    }

    return os;
}

int main()
{
    vector<pair<int, int>> edges = {{2, 3}, {5, 6}, {4, 3}, {0, 6}, {7, 3}, {5, 2}};
    vector<vector<int>> adj_list = gen_adj_list(edges);

    cout << adj_list;

    return 0;
}