#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int letterIndex(const string &letter)
{
    static const vector<string> letters = {
        "а", "б", "в", "г", "д", "ѓ", "е", "ж", "з", "ѕ",
        "и", "ј", "к", "л", "љ", "м", "н", "њ", "о", "п",
        "р", "с", "т", "ќ", "у", "ф", "х", "ц", "ч", "џ", "ш"};

    for (int i = 0; i < 31; i++)
        if (letter == letters[i])
            return i;

    return -1;
}

class TrieNode
{
public:
    bool isLeaf;
    vector<TrieNode *> children;

    TrieNode() : isLeaf(false), children(31, nullptr) {}
};

class Trie
{
private:
    TrieNode *root;

    void clear(TrieNode *node)
    {
        if (!node)
            return;

        for (TrieNode *c : node->children)
            clear(c);

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

        for (int i = 0; i < word.size(); i += 2)
        {
            string letter = word.substr(i, 2);
            int idx = letterIndex(letter);

            if (idx < 0)
                return;

            if (!curr->children[idx])
                curr->children[idx] = new TrieNode();

            curr = curr->children[idx];
        }

        curr->isLeaf = true;
    }

    bool search(const string &word) const
    {
        TrieNode *curr = root;

        for (int i = 0; i < word.size(); i += 2)
        {
            string letter = word.substr(i, 2);
            int idx = letterIndex(letter);

            if (idx < 0)
                return false;

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

    ifstream file("word_list_mk.txt");

    string word;
    while (getline(file, word))
        trie.insert(word);

    cout << trie.search("никола") << endl;
    cout << trie.search("пешевски") << endl;
    cout << trie.search("збор") << endl;
    cout << trie.search("тест") << endl;

    return 0;
}
