#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <unordered_set>
#include <queue>

using namespace std;

class Category {
    string CategoryName;
    vector<string> pages;
public:
    explicit Category(string name) {
        CategoryName = std::move(name);
    };
    void append(const string& page) {
        pages.push_back(page);
    };
};

class AdjacencyList {
public:
    unordered_map<string, string> pageNames;
    unordered_map<string, vector<string> > list;
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

    int countNodesDFS(const string& start, const string& end) {
        if (start == end) return 0;

        stack<pair<string, int>> s; // Pair of node and depth
        unordered_set<string> visited;

        // Initialize
        s.emplace(start, 0);
        visited.insert(start);

        while (!s.empty()) {
            auto node = s.top();
            s.pop();

            for (const auto& adjNode : this->list[node.first]) {
                if (visited.find(adjNode) == visited.end()) {
                    visited.insert(adjNode);
                    s.emplace(adjNode, node.second+1);
                }
                if (adjNode == end) return node.second + 1;
            }
        }
        return -1; // If end node is not reachable from start node
    }

    int countNodesBFS(const string& start, const string& end) {
        if (start == end) return 0;

        queue<pair<string, int>> q; // Pair of node and depth
        unordered_set<string> visited;

        // Initialize
        q.emplace(start, 0);
        visited.insert(start);

        while (!q.empty()) {
            auto node = q.front();
            q.pop();

            for (const auto& adjNode : this->list[node.first]) {
                if (visited.find(adjNode) == visited.end()) {
                    visited.insert(adjNode);
                    q.emplace(adjNode, node.second+1);
                }
                if (adjNode == end) return node.second + 1;
            }
        }
        return -1; // If end node is not reachable from start node
    }
};