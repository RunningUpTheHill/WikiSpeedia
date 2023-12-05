#include "AdjacencyList.h"

#include <chrono>
using namespace std;

int main() {
    AdjacencyList list;
    crow::SimpleApp app;

    CROW_ROUTE(app, "/get_page_names")
            ([&list]() {
                auto pageNames = list.getAllPageNames(); // Call the method to get all page names
                crow::json::wvalue result;
                result["pageNames"] = pageNames;

                crow::response res{result};
                res.add_header("Access-Control-Allow-Origin", "*"); // Allow all origins
                res.add_header("Access-Control-Allow-Methods", "GET, POST, PATCH, PUT, DELETE, OPTIONS");
                res.add_header("Access-Control-Allow-Headers", "Origin, Content-Type, X-Auth-Token");

                return res;
            });

    CROW_ROUTE(app, "/search/<string>/<string>")
            ([&](const std::string& start, const std::string& end) {

                string src = urlDecode(start);
                string dest = urlDecode(end);

                // Measure time for BFS
                auto bfsStart = chrono::steady_clock::now();
                int A = list.countNodesBFS(src, dest);
                auto bfsEnd = chrono::steady_clock::now();
                long long bfsDuration = chrono::duration_cast<chrono::nanoseconds>(bfsEnd - bfsStart).count();

                // Measure time for DFS
                auto dfsStart = chrono::steady_clock::now();
                int B = list.countNodesDFS(src, dest);
                auto dfsEnd = chrono::steady_clock::now();
                long long dfsDuration = chrono::duration_cast<chrono::nanoseconds>(dfsEnd - dfsStart).count();

                //Measure time for A*
                auto astarStart = chrono::steady_clock::now();
                int C = list.aStarSearch(src, dest);
                auto astarEnd = chrono::steady_clock::now();
                long long astarDuration = chrono::duration_cast<chrono::nanoseconds>(astarEnd - astarStart).count();


                crow::json::wvalue result;
                result["User Entered Values"] = src + " " + dest;
                if (A > -1){
                    result["message"] = "Success";
                    result["BFS_node_count"] = A;
                    result["BFS_time_ns"] = bfsDuration;
                    result["DFS_node_count"] = B;
                    result["DFS_time_ns"] = dfsDuration;
                    result["A*_node_count"] = C;
                    result["A*_time_ns"] = astarDuration;
                } else {
                    result["message"] = "Path not found or error";
                }
                crow::response res{result};
                res.add_header("Access-Control-Allow-Origin", "*"); // Allow all origins
                res.add_header("Access-Control-Allow-Methods", "GET, POST, PATCH, PUT, DELETE, OPTIONS");
                res.add_header("Access-Control-Allow-Headers", "Origin, Content-Type, X-Auth-Token");

                return res;
            });

    CROW_ROUTE(app, "/get_graph_data")
            ([&list]() {
                auto graphData = list.getNodesAndEdges();
                crow::response res{graphData};
                res.add_header("Access-Control-Allow-Origin", "*");
                res.add_header("Access-Control-Allow-Methods", "GET, POST, PATCH, PUT, DELETE, OPTIONS");
                res.add_header("Access-Control-Allow-Headers", "Origin, Content-Type, X-Auth-Token");
                return res;
            });

    app.port(18080).multithreaded().run();

    return 0;
}
