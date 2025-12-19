#include <iostream>
#include <string>
#include <vector>

using namespace std;

void buildBasePowers(
    vector<long long> &basePower,
    int length,
    int base,
    int mod)
{
    basePower[0] = 1;
    for (int i = 1; i <= length; i++)
        basePower[i] = (basePower[i - 1] * base) % mod;
}

void buildHash(
    const string &text,
    vector<long long> &hash,
    int length,
    int base,
    int mod,
    bool reversed)
{
    hash[0] = 0;

    for (int i = 0; i < length; i++)
    {
        int index = reversed ? (length - 1 - i) : i;
        int value = text[index] - 'a' + 1;
        hash[i + 1] = (hash[i] * base + value) % mod;
    }
}

long long getHash(
    int left,
    int right,
    int length,
    const vector<long long> &hash,
    const vector<long long> &basePower,
    int mod,
    bool reversed)
{
    int l = left;
    int r = right;

    if (reversed)
    {
        l = length - 1 - right;
        r = length - 1 - left;
    }

    long long value =
        hash[r + 1] - (hash[l] * basePower[r - l + 1]) % mod;

    if (value < 0)
        value += mod;

    return value;
}

bool isPalindrome(
    int left,
    int right,
    int length,
    const vector<long long> &forwardHash,
    const vector<long long> &reverseHash,
    const vector<long long> &basePower,
    int mod)
{
    return getHash(
               left, right, length,
               forwardHash, basePower, mod, false) ==
           getHash(
               left, right, length,
               reverseHash, basePower, mod, true);
}

vector<long long> computePalindromicCharacteristics(const string &text)
{
    int length = text.size();
    int base = 31;
    int mod = 1e9 + 7;

    vector<long long> basePower(length + 1);
    vector<long long> forwardHash(length + 1);
    vector<long long> reverseHash(length + 1);

    buildBasePowers(basePower, length, base, mod);
    buildHash(text, forwardHash, length, base, mod, false);
    buildHash(text, reverseHash, length, base, mod, true);

    vector<vector<int>> palLevel(length, vector<int>(length, 0));
    vector<long long> result(length + 2, 0);

    for (int substringLength = 1; substringLength <= length; substringLength++)
    {
        for (int start = 0; start + substringLength - 1 < length; start++)
        {
            int end = start + substringLength - 1;

            if (!isPalindrome(
                    start, end, length,
                    forwardHash, reverseHash,
                    basePower, mod))
                continue;

            palLevel[start][end] = 1;

            if (substringLength > 1)
            {
                int halfLength = substringLength / 2;
                palLevel[start][end] =
                    palLevel[start][start + halfLength - 1] + 1;
            }

            result[palLevel[start][end]]++;
        }
    }

    for (int k = length - 1; k >= 1; k--)
        result[k] += result[k + 1];

    return result;
}

int main()
{
    string text;
    cin >> text;

    vector<long long> answer =
        computePalindromicCharacteristics(text);

    for (int k = 1; k <= text.size(); k++)
        cout << answer[k] << " ";

    return 0;
}
