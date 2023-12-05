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
#include "crow_all.h"

using namespace std;

string urlDecode(const std::string& str) {
    std::string decoded;
    char ch;
    int i, j;
    for (i = 0; i < str.length(); i++) {
        if (int(str[i]) == 37) { // '%' in ASCII
            sscanf(str.substr(i + 1, 2).c_str(), "%x", &j);
            ch = static_cast<char>(j);
            decoded += ch;
            i = i + 2;
        } else {
            decoded += str[i];
        }
    }
    return decoded;
}

//class Category {
//public:
//    string CategoryName;
//    unordered_map<string, string> pages;
//
//    explicit Category(string name) {
//        CategoryName = std::move(name);
//    };
//    void append(const string& page) {
//        pages[page] = CategoryName;
//    };
//};

class AdjacencyList {

public:
    unordered_map<string, string> categories;
    unordered_map<string, string> pageNames;
    unordered_map<string, vector<string> > list;
    crow::json::wvalue graph;

    string getCategory(const string& node) {
        return categories[node];
    }

    vector<string> getAllPageNames() {
        vector<string> allNames;
        int i = 0;
        for (const auto& pair : pageNames) {
            if (i > 10000){
                break;
            }
            allNames.push_back(pair.second);
            i++;
        }
        return allNames;
    }

    crow::json::wvalue getNodesAndEdges() {
        crow::json::wvalue result;
        int nodeId = 1;
        unordered_map<string, int> nodeNameToId;

        // Process nodes
        for (const auto& pair : list) {
            nodeNameToId[pair.first] = nodeId;
            result["nodes"][nodeId - 1] = {{"id", nodeId}, {"label", pair.first}, {"shape", "circular"}};
            nodeId++;
        }

        // Process edges
        int edgeId = 0;
        for (const auto& pair : list) {
            for (const auto& adjNode : pair.second) {
                result["edges"][edgeId] = {{"from", nodeNameToId[pair.first]}, {"to", nodeNameToId[adjNode]}};
                edgeId++;
            }
        }

        return result;
    }




    AdjacencyList() {
        ifstream inFile;
        inFile.open("/Users/manasadepu/CLionProjects/WikiSpeedia/wiki_speedia_backend/wiki-topcats-page-names.txt");
        string line;
        while (getline(inFile, line)) {
            stringstream s(line);
            string key, value;
            s >> key;
            auto it = find(line.begin(), line.end(), ' ');
            pageNames[key] = line.substr(it-line.begin()+1, line.size()-*it-1);
        }
        ifstream linkFile;
        linkFile.open("/Users/manasadepu/CLionProjects/WikiSpeedia/wiki_speedia_backend/wiki-topcats.txt");
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
        ifstream i;
        string category;
        i.open("/Users/manasadepu/CLionProjects/WikiSpeedia/wiki_speedia_backend/wiki-topcats-categories.txt");
        while (getline(i, category)) {
            stringstream s(category);
            string placeholder;
            s >> placeholder;
            string CATE = placeholder.substr(9, placeholder.size()-1-9);
            while (s >> placeholder) {
                categories[pageNames[placeholder]] = CATE;
            }
        }

        cout << "Finished initializing List";
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

    int aStarSearch(const string& start, const string& end) {
        // Define the heuristic function
        auto heuristic = [this, &end](const string& node) {
            string nodeCategory = getCategory(node);
            string targetCategory = getCategory(end);

            if (nodeCategory == targetCategory) {
                return 0; // Lower cost if node is in the same category as target
            } else {
                return 1; // Higher cost otherwise
            }
        };

        // Priority queue for the frontier, sorted by f = g + h
        auto cmp = [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        };
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> frontier(cmp);

        unordered_map<string, int> cost_so_far; // Cost from start to a node
        unordered_set<string> visited; // Visited nodes

        frontier.emplace(start, 0);
        cost_so_far[start] = 0;

        while (!frontier.empty()) {
            auto current = frontier.top().first;
            frontier.pop();

            if (current == end) {
                return cost_so_far[current]; // Path found
            }

            for (const auto& next : list[current]) {
                int new_cost = cost_so_far[current] + 1; // Assuming uniform cost for each step
                if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
                    cost_so_far[next] = new_cost;
                    int priority = new_cost + heuristic(next);
                    frontier.emplace(next, priority);
                    visited.insert(next);
                }
            }
        }

        return -1; // If end node is not reachable from start node
    }
};