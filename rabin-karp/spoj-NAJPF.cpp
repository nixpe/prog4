#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> rabinKarp(const string &pattern, const string &text)
{
    int p = 31;
    int mod = 1e9 + 7;
    int m = pattern.size();
    int n = text.size();

    if (m > n)
        return {};

    long long patternHash = 0;
    long long windowHash = 0;
    long long power = 1;

    for (int i = 0; i < m - 1; i++)
        power = (power * p) % mod;

    for (int i = 0; i < m; i++)
    {
        patternHash = (patternHash * p + (pattern[i] - 'a' + 1)) % mod;
        windowHash = (windowHash * p + (text[i] - 'a' + 1)) % mod;
    }

    vector<int> matches;

    for (int i = 0; i <= n - m; i++)
    {
        if (patternHash == windowHash)
            if (text.substr(i, m) == pattern)
                matches.push_back(i);

        if (i < n - m)
        {
            windowHash = (windowHash - (long long)(text[i] - 'a' + 1) * power) % mod;
            if (windowHash < 0)
                windowHash += mod;

            windowHash = (windowHash * p + (text[i + m] - 'a' + 1)) % mod;
        }
    }

    return matches;
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        string text, pattern;
        cin >> text >> pattern;

        vector<int> result = rabinKarp(pattern, text);

        if (result.empty())
            cout << "Not Found" << endl
                 << endl;
        else
        {
            cout << result.size() << endl;

            int r = result.size();
            for (int i = 0; i < r; i++)
                cout << result[i] + 1;

            cout << endl
                 << endl;
        }
    }

    return 0;
}
