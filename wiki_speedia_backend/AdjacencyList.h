#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Category {
public:
    string CategoryName;
    vector<string> pages;
    explicit Category(string name);
    void append(const string& page);
};

class AdjacencyList {
    unordered_map<string, string> pageNames;
    unordered_map<string, vector<string>> list;
public:
    AdjacencyList() {
        ifstream inFile;
        inFile.open("wiki-topcats-page-names.txt");
        string line;
        while (getline(inFile, line)) {
            stringstream s(line);
            string key, value;
            s >> key;
            auto it = find(line.begin(), line.end(), ' ');
            pageNames[key] = line.substr(it-line.begin()+1, line.size()-*it-1);
        }
        ifstream linkFile;
        linkFile.open("wiki-topcats.txt");
        string props;
        while (getline(linkFile, props)) {
            stringstream ss(props);
            string from, to;
            ss >> from >> to;
            list[pageNames[from]].push_back(pageNames[to]);
            if (list.find(pageNames[to]) == list.end()) {
                list[pageNames[to]] = {};
            }
        }
    }
};