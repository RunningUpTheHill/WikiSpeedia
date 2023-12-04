#include "AdjacencyList.h"
#include "crow_all.h"
using namespace std;

int main() {

    crow::SimpleApp app;
    AdjacencyList list;

    ifstream inFile;
    string category;
    inFile.open("wiki-topcats-categories.txt");
    vector<Category> categories;
    while (getline(inFile, category)) {
        stringstream s(category);
        string placeholder;
        s >> placeholder;
        Category Cate(placeholder.substr(9, placeholder.size() - 1 - 9));
        while (s >> placeholder) {
            Cate.append(placeholder);
        }
        categories.push_back(Cate);
    }

    CROW_ROUTE(app, "/search/<string>/<string>")
            ([&](const std::string& start, const std::string& end) {

                int A = list.countNodesBFS(start, end);
                int B = list.countNodesDFS(start, end);

                crow::json::wvalue result;
                result["User Entered Values"] = start + " " + end;
                if (A > -1){
                    result["message"] = "Success";
                    result["node_count"] = A;
                } else {
                    result["message"] = "Path not found or error";
                }
                return result;
            });

    app.port(18080).multithreaded().run();





    return 0;
}
