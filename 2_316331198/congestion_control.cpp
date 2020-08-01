#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

static int arrived = 0;     //סהכ
static int dropped = 0;     //נזרקו
static int transmitted = 0; //התקבלו
static int allValue = 0;    //סהכ ערך שיצאו

/**
@input: queue size and file.
@description: 
@admission: during arrival phase, for each incoming packet p if a buffer is not full accept p.
Otherwise (full buffer), if in the queue there is a packet q whose remaining slack s(q)<s(p),
q is removed from the queue and p is accepted. Otherwise, p is dropped.
@processing: from all buffered packets transmit a packet p with the minimal s(p).
**/

void EDF(string queue, string _file)
{
    typedef pair<int, int> pairs;
    priority_queue<pairs, vector<pairs>, greater<pairs>> pqueue;

    //convert file string to char
    char fileC[_file.length() + 1];
    strcpy(fileC, _file.c_str());

    FILE *file = fopen(fileC, "r");

    if (feof(file))
        cout << "file doesn't opening!" << endl;

    char ch;
    while (fscanf(file, "%c", &ch) != EOF)
    {
        string cpacket, cslack, cvalue;

        if (ch == ' ')
        {
            ch = getc(file);
        }

        ch = getc(file);
        while (ch != ',')
        {
            cpacket += ch;
            ch = getc(file);
        }

        ch = getc(file);
        while (ch != ',')
        {
            cslack += ch;
            ch = getc(file);
        }

        ch = getc(file);
        while (ch != ')')
        {
            cvalue += ch;
            ch = getc(file);
        }
        ch = getc(file);

        int packet = stoi(cpacket);
        int slack = stoi(cslack);
        int value = stoi(cvalue);

        for (int i = 0; i < packet; i++)
        {

            if (pqueue.size() < stoi(queue))
            {
                if (slack == 0)
                {
                    dropped++;
                    arrived++;
                }

                else
                {
                    pqueue.push(make_pair(slack, value));
                    arrived++;
                }
            }

            else
            {
                pair<int, int> top = pqueue.top();
                if (top.first < slack)
                {
                    pqueue.pop();
                    pqueue.push(make_pair(slack, value));
                    arrived++;
                    dropped++;
                }
                else
                {
                    dropped++;
                    arrived++;
                }
            }
        }
        /**
        Line drop, Subtract 1 from slack from every package in queue.
        Drop packages with slack 0 and transmit the package with the lowest slack.
        **/

        if (ch == '\n')
        {
            int count = 0;
            vector<pair<int, int>> tmp;
            tmp.clear();
            while (!pqueue.empty())
            {
                pair<int, int> top = pqueue.top();
                top.first--;

                if (top.first <= 0)
                {
                    pqueue.pop();
                    dropped++;
                }
                else
                {
                    pqueue.pop();
                    tmp.push_back(top);
                    count++;
                }
            }
            for (int i = 0; i < count; i++)
            {
                pqueue.push(make_pair(tmp[i].first, tmp[i].second));
            }
            pair<int, int> top = pqueue.top();
            allValue += top.second;
            transmitted++;
            pqueue.pop();
        }
    }
    /**
    After all the packages have been delivered, Subtract 1 from slack from every package in queue.
    Drop packages with slack 0 and transmit the package with the lowest slack.
    **/

    vector<pair<int, int>> tmp;
    tmp.clear();
    while (!pqueue.empty())
    {
        int count = 0;
        tmp.clear();
        while (!pqueue.empty())
        {
            pair<int, int> top = pqueue.top();
            top.first--;
            if (top.first <= 0)
            {
                pqueue.pop();
                dropped++;
            }
            else
            {
                pqueue.pop();
                tmp.push_back(top);
                count++;
            }
        }
        if (tmp.size() != 0)
        {
            for (int i = 0; i < count; i++)
            {
                pqueue.push(make_pair(tmp[i].first, tmp[i].second));
            }
        }
        if (!pqueue.empty())
        {
            pair<int, int> top = pqueue.top();
            allValue += top.second;
            transmitted++;
            pqueue.pop();
        }
    }
    cout << "Total arrived packets: " << arrived << ", total dropped packets: " << dropped
         << ", total transmitted packets: " << transmitted << ", total transmitted value: " << allValue << "." << endl;
}

/**
@input: queue size and file.
@description:
@admission: during arrival phase, for each incoming packet p if a buffer is not full accept p.
Otherwise (full buffer), if in the queue there is a packet q whose value v(q)<v(p),
q is removed from the queue and p is accepted. Otherwise, p is dropped.
@processing: from all buffered packets transmit a packet p with the maximal v(p).
**/
void BoundedDelay(string queue, string _file)
{

    typedef pair<int, int> pairs;
    priority_queue<pairs, vector<pairs>, greater<pairs>> pqueue;

    //convert file string to char
    char fileC[_file.length() + 1];
    strcpy(fileC, _file.c_str());

    FILE *file = fopen(fileC, "r");

    if (feof(file))
        cout << "file doesn't opening!" << endl;

    char ch;
    while (fscanf(file, "%c", &ch) != EOF)
    {
        string cpacket, cslack, cvalue;

        if (ch == ' ')
        {
            ch = getc(file);
        }

        ch = getc(file);
        while (ch != ',')
        {
            cpacket += ch;
            ch = getc(file);
        }

        ch = getc(file);
        while (ch != ',')
        {
            cslack += ch;
            ch = getc(file);
        }

        ch = getc(file);
        while (ch != ')')
        {
            cvalue += ch;
            ch = getc(file);
        }

        ch = getc(file);

        int packet = stoi(cpacket);
        int slack = stoi(cslack);
        int value = stoi(cvalue);

        for (int i = 0; i < packet; i++)
        {

            if (pqueue.size() < stoi(queue))
            {
                if (slack == 0)
                {
                    dropped++;
                    arrived++;
                }

                else
                {
                    pqueue.push(make_pair(value, slack));
                    arrived++;
                }
            }
            else
            {
                pair<int, int> top = pqueue.top();
                if (top.first < value)
                {
                    pqueue.pop();
                    pqueue.push(make_pair(value, slack));
                    arrived++;
                    dropped++;
                }
                else
                {
                    dropped++;
                    arrived++;
                }
            }
        }
        /**
        Line drop, Subtract 1 from slack from every package in queue.
        Drop packages with slack 0 and transmit the package with the highest value.
        **/

        if (ch == '\n')
        {
            int count = 0;
            vector<pair<int, int>> tmp;
            while (!pqueue.empty())
            {

                pair<int, int> top = pqueue.top();
                top.second--;

                if (top.second <= 0)
                {
                    pqueue.pop();
                    dropped++;
                }
                else
                {
                    pqueue.pop();
                    tmp.push_back(top);
                    count++;
                }
            }
            sort(tmp.begin(), tmp.begin() + count);
            int biggest = tmp.at(count - 1).first;
            tmp.erase(tmp.begin() + (count - 1));
            allValue += biggest;
            transmitted++;

            for (int i = 0; i < count - 1; i++)
            {
                pqueue.push(make_pair(tmp[i].first, tmp[i].second));
            }
        }
    }

    /**
    After all the packages have been delivered, Subtract 1 from slack from every package in queue.
    Drop packages with slack 0 and transmit the package with the highest value.
    **/
    vector<pair<int, int>> tmp;
    while (!pqueue.empty())
    {
        int count = 0;
        tmp.clear();
        while (!pqueue.empty())
        {
            pair<int, int> top = pqueue.top();
            top.second--;
            if (top.second <= 0)
            {
                pqueue.pop();
                dropped++;
            }
            else
            {
                pqueue.pop();
                tmp.push_back(top);
                count++;
            }
        }
        sort(tmp.begin(), tmp.begin() + count);
        int biggest = tmp.at(count - 1).first;
        tmp.erase(tmp.begin() + (count - 1));
        allValue += biggest;
        transmitted++;

        for (int i = 0; i < count - 1; i++)
        {
            pqueue.push(make_pair(tmp[i].first, tmp[i].second));
        }
    }
    cout << "Total arrived packets: " << arrived << ", total dropped packets: " << dropped
         << ", total transmitted packets: " << transmitted << ", total transmitted value: " << allValue << "." << endl;
}

/**
@input: algorithm, queue size and file.
@description: A function that maps which algorithm to run on the file information.
@example:edf 10 test.txt
**/
void read(string algo, string queue, string _file)
{
    if (algo == "bd")
        BoundedDelay(queue, _file);
    if (algo == "edf")
        EDF(queue, _file);
}
/**
@description: Reading from the terminal
@example:./a.out (executable file), edf(algorithm), 10 (queue size), test.txt (file).
**/
int main(int argc, char *argv[])
{
    if (argc != 4)
        cout << "Invalid input" << endl;

    string algo = argv[1];
    string num = argv[2];
    string _file = argv[3];

    read(algo, num, _file);
    return 0;
}
