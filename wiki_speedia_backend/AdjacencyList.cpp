#include "AdjacencyList.h"
#include <utility>

Category::Category(string name) {
    CategoryName = std::move(name);
}

void Category::append(const string& page) {
    pages.push_back(page);
}
