#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class TrieNode
{
public:
    bool isLeaf;
    vector<pair<string, TrieNode *>> edges;

    TrieNode() : isLeaf(false) {}
};

class PatriciaTrie
{
private:
    TrieNode *root;

    int longestCommonPrefix(const string &a, const string &b) const
    {
        int L = min(a.size(), b.size());
        int i = 0;
        while (i < L && a[i] == b[i])
            i++;
        return i;
    }

    void clear(TrieNode *node)
    {
        if (!node)
            return;

        for (auto &e : node->edges)
            clear(e.second);

        delete node;
    }

public:
    PatriciaTrie() : root(new TrieNode()) {}

    ~PatriciaTrie()
    {
        clear(root);
    }

    void insert(string word)
    {
        for (char &c : word)
            c = tolower(c);

        TrieNode *current = root;
        string remaining = word;

        while (true)
        {
            bool foundEdge = false;

            for (auto &edge : current->edges)
            {
                string &label = edge.first;
                TrieNode *child = edge.second;

                int k = longestCommonPrefix(label, remaining);

                if (k == 0)
                    continue;

                if (k == label.size())
                {
                    remaining = remaining.substr(k);
                    current = child;
                    foundEdge = true;
                    break;
                }

                string commonPart = label.substr(0, k);
                string oldRemainder = label.substr(k);
                string newRemainder = remaining.substr(k);

                TrieNode *mid = new TrieNode();

                mid->edges.push_back({oldRemainder, child});

                edge.first = commonPart;
                edge.second = mid;

                if (newRemainder.empty())
                    mid->isLeaf = true;

                else
                {
                    TrieNode *newNode = new TrieNode();
                    newNode->isLeaf = true;
                    mid->edges.push_back({newRemainder, newNode});
                }

                return;
            }

            if (!foundEdge)
            {
                TrieNode *newNode = new TrieNode();
                newNode->isLeaf = true;
                current->edges.push_back({remaining, newNode});
                return;
            }

            if (remaining.empty())
            {
                current->isLeaf = true;
                return;
            }
        }
    }

    bool search(string word) const
    {
        for (char &c : word)
            c = tolower(c);

        TrieNode *current = root;
        string remaining = word;

        while (!remaining.empty())
        {
            bool moved = false;

            for (auto &edge : current->edges)
            {
                const string &label = edge.first;
                TrieNode *child = edge.second;

                int k = longestCommonPrefix(label, remaining);

                if (k == 0)
                    continue;

                if (k != label.size())
                    return false;

                remaining = remaining.substr(k);
                current = child;
                moved = true;
                break;
            }

            if (!moved)
                return false;
        }

        return current->isLeaf;
    }
};

int main()
{
    PatriciaTrie trie;

    ifstream file("word_list_en.txt");

    string word;
    while (getline(file, word))
        trie.insert(word);

    cout << trie.search("nick") << endl;
    cout << trie.search("hello") << endl;
    cout << trie.search("world") << endl;
    cout << trie.search("test") << endl;

    return 0;
}
