#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include "prefix_table.hpp"

using namespace std;

/**
@input:  The root of the trie, binary prefix, result.
@description: A function that adds nodes to the trie by binary prefix,
the last node will be the result (the last char).
**/

node *BuildTree(node *root, string binary)
{
    for (int i = 0; i < binary.size(); i++)
    {
        if (binary[i] == '1')
        {
            if (root->right == nullptr)
            {
                root->right = setNull();
                root->right->counter_path = 1;
                root->right->father = root;
                root = root->right;
            }
            else
            {
                root->right->counter_path++;
                root->right->father = root;
                root = root->right;
            }
        }
        else
        {
            if (root->left == nullptr)
            {
                root->left = setNull();
                root->left->counter_path = 1;
                root->left->father = root;
                root = root->left;
            }
            else
            {
                root->left->counter_path++;
                root->left->father = root;
                root = root->left;
            }
        }
    }
    return root;
}
/**
@input:  The root of the trie and binary prefix.
@description: A function that decreases by 1 the value of the path.
The value is the number of prefixes passing through this path.
**/
void deletePath(node *root, string binary)
{

    for (int i = 0; i < binary.size() - 1; i++)
    {
        if (binary.at(i) == '1')
        {
            root->right->counter_path--;
            root = root->right;
        }
        else
        {
            root->left->counter_path--;
            root = root->left;
        }
    }
}
/**
@input:  The root of the trie, binary prefix, result.
@description: If two prefixes differ only in the last bit and point to the same
action than both prefixes will be replaced by a single prefix with the same action.
First of all the function does a test for the written condition.
if the condition is valid, the function will delete the unnecessary node (if it has no children)
and change the letter to the father of the node.
 **/
void opt(node *root, string binary, string lastChar)
{
    node *node = root;
    root = BuildTree(root, binary);

    root->result_place = true;
    setResultName(root, lastChar);

    if (root->father->right != nullptr && root->father->left != nullptr) //has children
    {
        if (root->father->right->result_place && root->father->left->result_place)
        {
            if (*(root->father->right->result_name) == *(root->father->left->result_name)) //same result name
            {
                setResultName(root->father, lastChar);
                root->father->result_place = true;
                if (root->father->right->right != nullptr || root->father->right->left != nullptr) //right grandchildren
                {
                    root->father->right->result_name = nullptr;
                    root->father->right->result_place = false;
                }
                else
                {
                    root->father->right = nullptr;
                }
                if (root->father->left->right != nullptr || root->father->left->left != nullptr) //left grandchildren
                {
                    root->father->left->result_name = nullptr;
                    root->father->left->result_place = false;
                }
                else
                {
                    root->father->left = nullptr;
                }
                deletePath(node, binary);
            }
        }
    }
}
/**
@input: action, binary prefix, result, trie root, prefix.
@description:A function that maps the prefix to the correct function: ADD, REMOVE or FIND.
**/
void fun(string function, string binary, string lastChar, node *root, string adress)
{

    if (function == "ADD")
    {
        opt(root, binary, lastChar);
        int dep = depth(root);
        int leaf = nodesCount(root);
        cout << "Added " << adress << " " << lastChar << " at the depth " << dep << " total nodes " << leaf << endl;
    }

    else if (function == "FIND")
    {
        find(root, binary, adress);
    }

    else if (function == "REMOVE")
    {
        if (remove(root, binary, lastChar))
        {
            int dep = depth(root);
            int leaf = nodesCount(root);
            cout << "Removed " << adress << " " << lastChar << " at the depth " << dep << " total nodes " << leaf << endl;
        }
    }
}
/**
@input: text file as a string.
@description: A function that gets the text file as a string,
reads one word at a time and maps the prefix to the correct function: ADD, REMOVE or FIND.
@example:ADD (function) 255.255.255/24 (prefix) A (result).
**/
void read(string _file)
{
    node *root = setNull();

    ifstream file(_file);
    if (!file)
        cout << "file doesn't opening!" << endl;

    string function, adress, bin, lastChar;

    while (!file.eof())
    {
        file >> function;

        file >> adress;

        bin = decimal(adress);
        if (function != "FIND")
        {
            file >> lastChar;
        }
        else
            lastChar = "";
        fun(function, bin, lastChar, root, adress);
    }
}

int main()
{
    read("sample_input.txt");
    return 0;
}