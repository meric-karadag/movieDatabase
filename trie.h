#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;
#define nullptr NULL
template <class T>
class Trie
{
private:
    // Define TrieNode for the first phase (Trie)
    /* DO NOT CHANGE */
    struct TrieNode
    {
        static const int ALPHABET_SIZE = 128;
        TrieNode *children[ALPHABET_SIZE];
        char keyChar;
        bool isEndOfKey;
        T *data;

        TrieNode(char c) : keyChar(c), isEndOfKey(false), data(NULL)
        {

            for (int i = 0; i < ALPHABET_SIZE; i++)
            {
                children[i] = NULL;
            }
        }
    };

    TrieNode *root;

public: // Do not change.
    Trie();
    ~Trie();

    Trie &insert(const string &username);
    void remove(std::string username);
    T *search(std::string username);
    void findStartingWith(std::string prefix, std::vector<T *> &results);
    void wildcardSearch(const std::string &wildcardKey, std::vector<T *> &results);
    void print();

private:                                                           // you may add your own utility member functions here.
    void print(const std::string &primaryKey);                     // Do not change this line.
    void printTrie(TrieNode *node, const std::string &currentKey); // Do not change this line.
    void deleteTrieNode(TrieNode *&node);
    void findStartingWithHelper(TrieNode *node, vector<T *> &results);
    void wildcardSearchHelper(TrieNode *node, const std::string &wildcardKey, std::vector<T *> &results);
};
/* DO NOT CHANGE */
template <class T>
Trie<T>::Trie() : root(new TrieNode('\0')) {}

template <class T>
void Trie<T>::deleteTrieNode(TrieNode *&node)
{
    if (node == NULL)
        return;
    for (int i = 0; i < 128; i++)
    {
        deleteTrieNode(node->children[i]);
    }
    delete node->data;
    delete node;
    node = NULL;
}
template <class T>
Trie<T>::~Trie()
{
    /* IMPLEMENT THIS */
    deleteTrieNode(root);
}

template <class T>
Trie<T> &Trie<T>::insert(const string &username)
{
    /* IMPLEMENT THIS */
    TrieNode *node = root;
    int pos = 0;
    int len = username.length();
    while (pos < len && node != NULL)
    {
        int index = static_cast<int>(username[pos]);
        if (node->children[index] == NULL)
        {
            node->children[index] = new TrieNode(username[pos]);
        }
        node = node->children[index];
        pos++;
    }
    node->isEndOfKey = true;
    node->data = new T(username);
    return *this;
}

template <class T>
T *Trie<T>::search(std::string username)
{
    /* IMPLEMENT THIS */
    TrieNode *node = root;
    int pos = 0;
    int len = username.length();

    while (pos < len)
    {
        int index = static_cast<int>(username[pos]);
        if (node->children[index])
        {
            node = node->children[index];
            pos++;
        }
        else
        {
            return NULL;
        }
    }
    if (node->isEndOfKey)
        return node->data;
    else
        return NULL;
}

template <class T>
void Trie<T>::remove(std::string username)
{
    /* IMPLEMENT THIS */
    TrieNode *node = root;
    int pos = 0;
    int len = username.length();

    while (pos < len)
    {
        int index = static_cast<int>(username[pos]);
        if (node->children[index])
        {
            node = node->children[index];
            pos++;
        }
        else
        {
            return;
        }
    }
    if (node)
    {
        node->isEndOfKey = false;
        // if (node->data)
        // delete node->data;
        // node->data = NULL;
    }
    else
    {
        return;
    }
}

template <class T>
void Trie<T>::findStartingWithHelper(TrieNode *node, vector<T *> &results)
{
    if (node == NULL)
        return;
    if (node->isEndOfKey)
    {
        results.push_back(node->data);
    }
    for (int i = 0; i < 128; i++)
    {
        if (node->children[i])
            findStartingWithHelper(node->children[i], results);
    }
}
template <class T>
void Trie<T>::findStartingWith(string prefix, vector<T *> &results)
{
    /* IMPLEMENT THIS */
    TrieNode *node = root;
    int pos = 0;
    int len = prefix.length();
    while (pos < len && node != nullptr)
    {
        int index = static_cast<int>(prefix[pos]);
        if (node->children[index] == nullptr)
        {
            return;
        }
        node = node->children[index];
        pos++;
    }
    findStartingWithHelper(node, results);
}

template <class T>
void Trie<T>::wildcardSearch(const std::string &wildcardKey, std::vector<T *> &results)
{
    template <class T>
    void Trie<T>::wildcardSearch(const std::string &wildcardKey, std::vector<T *> &results)
    {
        wildcardSearchHelper(root, wildcardKey, "", results);
    }

    template <class T>
    void Trie<T>::wildcardSearchHelper(TrieNode * node, const std::string &wildcardKey, const std::string &currentKey, std::vector<T *> &results)
    {
        if (wildcardKey.empty())
        {
            if (node->isEndOfKey)
            {
                results.push_back(node->data);
            }
            return;
        }

        char wildcardChar = wildcardKey[0];
        std::string remainingWildcard = wildcardKey.substr(1);

        if (wildcardChar == '?')
        {
            for (int i = 0; i < 128; i++)
            {
                if (node->children[i])
                {
                    std::string newKey = currentKey + static_cast<char>(i);
                    wildcardSearchHelper(node->children[i], remainingWildcard, newKey, results);
                }
            }
        }
        else if (wildcardChar == '*')
        {
            wildcardSearchHelper(node, remainingWildcard, currentKey, results);

            for (int i = 0; i < 128; i++)
            {
                if (node->children[i])
                {
                    std::string newKey = currentKey + static_cast<char>(i);
                    wildcardSearchHelper(node->children[i], wildcardKey, newKey, results);
                }
            }
        }
        else
        {
            int index = static_cast<int>(wildcardChar);
            if (node->children[index])
            {
                std::string newKey = currentKey + wildcardChar;
                wildcardSearchHelper(node->children[index], remainingWildcard, newKey, results);
            }
        }
    }
}

/* DO NOT CHANGE */
template <class T>
void Trie<T>::print()
{
    print("");
}
/* DO NOT CHANGE */
template <class T>
void Trie<T>::print(const std::string &primaryKey)
{
    if (primaryKey.empty())
    {
        // Print the entire tree.
        printTrie(root, "");
    }
    else
    {
        // Print specific keys.
        TrieNode *primaryNode = root;
        for (int i = 0; i < primaryKey.length(); i++)
        {

            int index = primaryKey[i];
            if (!primaryNode->children[index])
            {
                std::cout << "{}" << std::endl; // Primary key not found, nothing to print.
                return;
            }
            primaryNode = primaryNode->children[index];
        }
    }
}
/* DO NOT CHANGE */
template <class T>
void Trie<T>::printTrie(TrieNode *node, const std::string &currentKey)
{
    if (!node)
    {
        return;
    }
    if (node->isEndOfKey)
    {
        std::cout << currentKey << std::endl;
        std::cout << "Watched Movies:" << std::endl;
        if (node->data)
        {
            node->data->printMovies();
        }
    }
    for (int i = 0; i < 128; ++i)
    {
        if (node->children[i])
        {
            printTrie(node->children[i], currentKey + static_cast<char>(i));
        }
    }
}
