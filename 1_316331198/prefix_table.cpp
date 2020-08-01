#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/socket.h>
#include <sstream>
#include <string.h>
#include "prefix_table.hpp"

using namespace std;

/**
@input:  The root of the trie, binary prefix, result.
@description: A function that adds nodes to the trie by binary prefix,
the last node will be the result (the last char).
**/
void add(node *root, string binary, string lastChar)
{
    setResultName(root, lastChar);

    for (int i = 0; i < binary.size(); i++)
    {
        if (binary[i] == '1')
        {
            if (root->right == nullptr)
            {
                root->right = setNull();
                root->right->counter_path = 1;
                root = root->right;
            }
            else
            {
                root->right->counter_path++;
                root = root->right;
            }
        }
        else
        {
            if (root->left == nullptr)
            {
                root->left = setNull();
                root->left->counter_path = 1;
                root = root->left;
            }
            else
            {
                root->left->counter_path++;
                root = root->left;
            }
        }
    }
    root->result_place = true;
    setResultName(root, lastChar);
}
/**
@input: action, binary prefix, result, trie root, prefix.
@description:A function that maps the prefix to the correct function: ADD, REMOVE or FIND.
**/
void fun(string function, string binary, string lastChar, node *root, string adress)
{

    if (function == "ADD")
    {
        add(root, binary, lastChar);
        int dep = depth(root);
        int leaf = nodesCount(root);
        cout << "Added " << adress << " " << lastChar << " at the depth " << dep << " total nodes " << leaf << endl;
    }

    else if (function == "FIND")
    {
        find(root, binary);
        int dep = depth(root);
        cout << "Found " << adress << " at the depth " << dep << endl;
    }

    else if (function == "REMOVE")
    {
        remove(root, binary, lastChar);
        int dep = depth(root);
        int leaf = nodesCount(root);
        cout << "Removed " << adress << " " << lastChar << " at the depth " << dep << " total nodes " << leaf << endl;
    }
}
/**
@input: text file as a string.
@description: A function that gets the text file as a string,
reads one word at a time and order them by action, prefix, result.
@example:ADD (function), 255.255.255/24 (prefix), A (result).
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
        //"file>>" reads one world
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
