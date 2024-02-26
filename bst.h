#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;
#define nullptr NULL

// do not add any other library.
// modify parts as directed by assignment text and comments here.

template <class T>
class BST
{
private:
    // Define TreeNode for the second phase (Binary Search Tree)
    /* DO NOT CHANGE */
    struct TreeNode
    {
        std::string key;
        T data;
        TreeNode *left;
        TreeNode *right;
        TreeNode(const std::string &k, const T &value) : key(k), data(value), left(NULL), right(NULL) {}
    };

    TreeNode *root;

public: // Do not change.
    BST();
    ~BST();
    TreeNode *getRoot() { return root; }
    bool isEmpty() { return root == NULL; }

    BST &insert(const std::string key, const T &value);
    bool search(std::string value) const;
    void remove(std::string value);
    BST<T> *merge(BST<T> *bst);
    BST<T> *intersection(BST<T> *bst);
    std::vector<TreeNode> tree2vector(TreeNode *root);
    void print();

private:                                                                         // you may add your own utility member functions here.
    void print(TreeNode *node, std::string indent, bool last, bool isLeftChild); // Do not change.
    void deleteNode(TreeNode *&node);
    void insertNode(TreeNode *&node, std::string key, const T &value);
    bool searchNode(TreeNode *node, std::string value) const;
    void removeNode(TreeNode *&node, std::string key);
    void tree2vectorNode(TreeNode *node, std::vector<TreeNode> &result);
};

// Constructor
template <class T>
BST<T>::BST() : root(NULL) {}

// Destructor
template <class T>
void BST<T>::deleteNode(TreeNode *&node)
{
    if (node == NULL)
        return;
    deleteNode(node->left);
    deleteNode(node->right);
    delete node;
    node = NULL;
}

template <class T>
BST<T>::~BST()
{
    /* IMPLEMENT THIS */
    deleteNode(root);
}

// Insert function for BST.
template <class T>
void BST<T>::insertNode(TreeNode *&node, std::string key, const T &value)
{
    if (node == NULL)
    {
        node = new TreeNode(key, value);
    }
    else if (key < node->key)
        insertNode(node->left, key, value);
    else if (key > node->key)
        insertNode(node->right, key, value);
    // Else a duplicate do nothing
}
template <class T>
BST<T> &BST<T>::insert(const string key, const T &value)
{
    /* IMPLEMENT THIS */
    insertNode(root, key, value);
    return *this;
}

// Search function for BST.
template <class T>
bool BST<T>::searchNode(TreeNode *node, std::string value) const
{
    if (node == NULL)
        return false;
    if (node->key == value)
        return true;
    if (node->key > value)
        return searchNode(node->left, value);
    else
        return searchNode(node->right, value);
}
template <class T>
bool BST<T>::search(std::string value) const
{
    /* IMPLEMENT THIS */
    return searchNode(root, value);
}

// Remove a node from BST for given key. If key not found, do not change anything.
template <class T>
void BST<T>::removeNode(TreeNode *&node, std::string key)
{
    if (node == NULL)
        return;
    if (key > node->key)
    {
        removeNode(node->right, key);
    }
    else if (key < node->key)
    {
        removeNode(node->left, key);
    }
    else
    {
        if (node->left != NULL && node->right != NULL)
        {
            // Case 3: Both Children; replace w/ min from Right
            std::string replaceKey;
            T replaceValue;
            TreeNode *temp = node->right;
            while (temp && temp->left)
            {
                temp = temp->left;
            }
            replaceKey = temp->key;
            replaceValue = temp->data;
            // Copy value here
            node->key = replaceKey;
            node->data = replaceValue;

            removeNode(node->right, node->key);
        }
        else
        {
            // Case 2 only child or case 1: leaf node
            TreeNode *oldNode = node;
            node = (node->left != NULL) ? node->left : node->right;
            delete oldNode;
            oldNode = NULL;
        }
    }
}

template <class T>
void BST<T>::remove(std::string value)
{
    /* IMPLEMENT THIS */
    removeNode(root, value);
}

// A helper function for converting a BST into vector.
template <class T>
std::vector<typename BST<T>::TreeNode> BST<T>::tree2vector(TreeNode *root)
{
    std::vector<TreeNode> result;
    tree2vectorNode(root, result);

    return result;
}

template <class T>
void BST<T>::tree2vectorNode(TreeNode *node, std::vector<TreeNode> &result)
{
    // Traverses In-Order
    if (node == nullptr)
        return;
    tree2vectorNode(node->left, result);
    result.push_back(*node);
    tree2vectorNode(node->right, result);
}

// Merge two BST's and return merged BST.
template <class T>
BST<T> *BST<T>::merge(BST<T> *bst)
{
    /* IMPLEMENT THIS */
    typename ::vector<typename BST<T>::TreeNode> vector1 = this->tree2vector(this->getRoot());
    typename ::vector<typename BST<T>::TreeNode> vector2 = bst->tree2vector(bst->getRoot());

    int vector1_size = vector1.size();
    int vector2_size = vector2.size();
    int it1 = 0, it2 = 0;
    // typename ::vector<typename BST<T>::TreeNode>::iterator it1;
    // typename ::vector<typename BST<T>::TreeNode>::iterator it2;

    BST<T> *newBST = new BST<T>;
    while (it1 != vector1_size && it2 != vector2_size)
    {
        if (vector1[it1].key < vector2[it2].key)
        {
            newBST->insert(vector1[it1].key, vector1[it1].data);
            it1++;
        }
        else if (vector1[it1].key > vector2[it2].key)
        {
            newBST->insert(vector2[it2].key, vector2[it2].data);
            it2++;
        }
        else
        {
            // Common element
            newBST->insert(vector1[it1].key, vector1[it1].data);
            it1++;
            it2++;
        }
    }
    while (it1 != vector1_size)
    {
        newBST->insert(vector1[it1].key, vector1[it1].data);
        it1++;
    }
    while (it2 != vector2_size)
    {
        newBST->insert(vector2[it2].key, vector2[it2].data);
        it2++;
    }
    return newBST;
}

// Intersect two BST's and return new BST.
template <class T>
BST<T> *BST<T>::intersection(BST<T> *bst)
{
    /* IMPLEMENT THIS */
    typename ::vector<typename BST<T>::TreeNode> vector1 = this->tree2vector(this->getRoot());
    typename ::vector<typename BST<T>::TreeNode> vector2 = bst->tree2vector(bst->getRoot());

    int vector1_size = vector1.size();
    int vector2_size = vector2.size();
    int it1 = 0, it2 = 0;

    BST<T> *newBST = new BST<T>;
    while (it1 != vector1_size && it2 != vector2_size)
    {
        if (vector1[it1].key < vector2[it2].key)
        {
            it1++;
        }
        else if (vector1[it1].key > vector2[it2].key)
        {
            it2++;
        }
        else
        {
            // Common element
            newBST->insert(vector1[it1].key, vector1[it1].data);
            it1++;
            it2++;
        }
    }
    return newBST;
}

/* DO NOT CHANGE */
template <class T>
void BST<T>::print()
{
    print(root, "", true, false);
}

/* DO NOT CHANGE */
template <class T>
void BST<T>::print(TreeNode *node, string indent, bool last, bool isLeftChild)
{
    if (node != NULL)
    {
        cout << node->key << endl;
        print(node->left, indent, false, true);
        print(node->right, indent, true, false);
    }
}
