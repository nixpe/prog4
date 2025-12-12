#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

class TrieNode
{
public:
    bool isLeaf;
    vector<TrieNode *> children;

    TrieNode() : isLeaf(false), children(26, nullptr) {}
};

class Trie
{
private:
    TrieNode *root;

    void clear(TrieNode *node)
    {
        if (!node)
            return;

        for (TrieNode *child : node->children)
            clear(child);

        delete node;
    }

public:
    Trie() : root(new TrieNode()) {}

    ~Trie()
    {
        clear(root);
    }

    void insert(const string &word)
    {
        TrieNode *curr = root;

        for (char c : word)
        {
            c = tolower(c);

            if (c < 'a' || c > 'z')
                return;

            int idx = c - 'a';

            if (!curr->children[idx])
                curr->children[idx] = new TrieNode();

            curr = curr->children[idx];
        }

        curr->isLeaf = true;
    }

    bool search(const string &word) const
    {
        TrieNode *curr = root;

        for (char c : word)
        {
            c = tolower(c);

            if (c < 'a' || c > 'z')
                return false;

            int idx = c - 'a';

            if (!curr->children[idx])
                return false;

            curr = curr->children[idx];
        }

        return curr->isLeaf;
    }
};

int main()
{
    Trie trie;

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
