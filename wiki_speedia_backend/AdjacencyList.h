#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <set>
#include <queue>

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

    int countNodesDFS(const string& start, const string& end){
        set<string> visited;
        return dfs(start, end, visited, 0) - 1;
    }

    int dfs(const string& node, const string& end, set<string>& visited, int count) {
        visited.insert(node);
        if (node == end) return count;

        for (const auto& adjNode : this->list[node]) {
            if (visited.find(adjNode) == visited.end()) {
                int result = dfs(adjNode, end, visited, count + 1);
                if (result != -1) return result;
            }
        }
        return -1; // Path not found
    }

    int countNodesBFS(const string& start, const string& end) {
        if (start == end) return 0;

        queue<pair<string, int>> q; // Pair of node and depth
        set<string> visited;

        // Initialize
        q.push({start, 0});
        visited.insert(start);

        while (!q.empty()) {
            auto [node, depth] = q.front();
            q.pop();

            for (const auto& adjNode : this->list[node]) {
                if (visited.find(adjNode) == visited.end()) {
                    visited.insert(adjNode);
                    q.push({adjNode, depth + 1});

                    if (adjNode == end) return depth;
                }
            }
        }
        return -1; // If end node is not reachable from start node
    }



};