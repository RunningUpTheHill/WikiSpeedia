#pragma once
#include <string>
#include <vector>
#include <map>
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
    class Node {
        string pageName;
    };
};