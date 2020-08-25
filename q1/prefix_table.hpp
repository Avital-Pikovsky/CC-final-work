#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/socket.h>
#include <sstream>
#include <string.h>

using namespace std;

typedef struct node
{
    char *result_name;
    bool result_place;
    int counter_path;
    node *left, *right, *father;
} node;

/**
@input: node and his result name.
@description: puts result name into node.
**/
void setResultName(node *node, string result_name)
{
    node->result_name = new char[result_name.length() + 1];
    strcpy(node->result_name, result_name.c_str());
}

/**
@description: Initialization of node (every new node).
**/
node *setNull()
{
    node *vertex = nullptr;
    vertex = (node *)malloc(sizeof(node));

    if (vertex != nullptr)
    {
        vertex->result_name = nullptr;
        vertex->result_place = false;
        vertex->counter_path = 0;
        vertex->father = nullptr;
        vertex->left = nullptr;
        vertex->right = nullptr;
    }
    return vertex;
}
/**
@input: The root of the trie.
@description: A function that calculates the depth of the tree - including the root.
**/
int depth(node *root)
{
    if (root == NULL)
        return 0;
    else
    {
        int leftDepth = depth(root->left);
        int rightDepth = depth(root->right);

        if (leftDepth > rightDepth)
            return (leftDepth + 1);
        else
            return (rightDepth + 1);
    }
}

/**
@input: root and binary prefix.
@description: A function that finds for a prefix in a trie.
@example:FIND (function), 255.255.255.0 (prefix).
**/
void find(node *root, string binary, string adress)
{
    int depth = 0;
    int temporary_depth = 0;
    string result = "";
    string result_end = "";

    for (int i = 0; i < binary.size(); i++)
    {
        if (root->result_place)
        {
            result = root->result_name;
            temporary_depth = depth;
        }
        if (root->right == nullptr && root->left == nullptr)
        {
            result_end = root->result_name;
            break;
        }
        if (binary.at(i) == '1' && root->right != nullptr)
        {
            depth++;
            root = root->right;
        }
        else if (binary.at(i) == '0' && root->left != nullptr)
        {
            depth++;
            root = root->left;
        }
        else
        {
            break;
        }
    }
    if (!result.empty() || !result_end.empty())
    {

        if (result != result_end) //Not the end of the trie
        {
            temporary_depth++;
            cout << "Found " << adress << result << " at the depth " << temporary_depth << "." << endl;
        }

        else //The end of the trie
        {
            depth++;
            cout << "Found " << adress << result << " at the depth " << depth << "." << endl;
        }
    }
    else

        cout << "Not found " << adress << endl;
}

/**
@input: root, binary prefix and result.
@description: A function that search if the prefix exist.
this function use by "remove" function.
@example:REMOVE (function), 255.255.255/24 (prefix), A(result).
**/
bool search(node *root, string binary, string lastChar)
{
    string name = "";
    int i;
    for (i = 0; i < binary.size(); i++)
    {
        if (root->right == nullptr && root->left == nullptr)
            break;

        else if (binary.at(i) == '1')
        {
            if (root->right != nullptr)
                root = root->right;
            else
                break;
        }
        else // binary.at(i) == '0'
        {
            if (root->left != nullptr)
                root = root->left;
            else
                break;
        }
    }
    if (root->result_place)
    {
        name = root->result_name;

        if (i == binary.size() && name == lastChar)
        {
            return true;
        }
    }

    return false;
}

/**
@input: root, binary prefix and result.
@description: A function that finds for a prefix in a trie.
first check if the prefix exist.
@example:REMOVE (function), 255.255.255/24 (prefix), A(result).
**/
bool remove(node *root, string binary, string lastChar)
{
    if (!search(root, binary, lastChar))
    {
        printf("This prefix doesn't exist, can't remove it\n");
        return false;
    }
    int i;
    for (i = 0; i < binary.size(); i++)
    {

        if (binary.at(i) == '1')
        {
            if (root->right->counter_path != 1)
            {
                root->right->counter_path--;
                root = root->right;
            }
            else // ==1
            {
                root->right = nullptr;
                break;
            }
        }
        else
        {
            if (root->left->counter_path != 1)
            {
                root->left->counter_path--;
                root = root->left;
            }
            else // ==1
            {
                root->left = nullptr;
                break;
            }
        }
    }
    if (i == binary.size())
    {
        root->result_name = nullptr;
        root->result_place = false;
    }
    return true;
}
/**
@input: string of decimal number.
@description: A function that converts part of the prefix from a decimal number to a binary.
@example:255 -> 11111111
**/
string toBinary(string deci)
{
    string s = "";
    int dec = stoi(deci);
    int a[10], i;

    for (i = 0; dec > 0; i++)
    {
        a[i] = dec % 2;
        dec = dec / 2;
    }
    for (i = i - 1; i >= 0; i--)
    {
        s += to_string(a[i]);
    }
    while (s.size() < 8)
        s = "0" + s;
    return s;
}
/**
@input: decimal prefix.
@description: A function that converts the prefix to a binary number and uses the toBinary function.
@example:255.255.255.255 -> 11111111 11111111 11111111 11111111
**/
string decimal(string dec)
{
    int intmask;
    string s = "";
    while (!dec.empty())
    {
        size_t dot = dec.find(".");
        string str = dec.substr(0, dot);
        string bin = toBinary(str);

        s += bin;
        if (dot < dec.size())
        {
            dec.erase(0, dot);
            dec.erase(dec.begin());
        }
        else
        {
            str = dec.substr(0);
            bin = toBinary(str);
            s += bin;
            dec.erase(0);
        }

        if ((dec.find("/") != std::string::npos) && (dec.find(".") == std::string::npos))
        {
            size_t slash = dec.find("/");
            str = dec.substr(0, slash);

            bin = toBinary(str);
            s += bin;

            dec.erase(0, slash);
            dec.erase(dec.begin());

            string mask = dec.substr(0);
            intmask = stoi(mask);
            dec.erase(0);
        }
    }
    string ans = s.substr(0, intmask);
    return ans;
}
/**
@input: Trie root.
@description:A function that counts how many nodes there are in a trie.
**/
int nodesCount(node *root)
{
    if (root == NULL)
        return 0;

    else
    {
        return 1 + nodesCount(root->left) + nodesCount(root->right);
    }
}
