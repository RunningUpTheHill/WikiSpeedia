#include "AdjacencyList.h"

int main() {
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

    return 0;
}
