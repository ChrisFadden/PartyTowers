#include "Path.h"

Path::Path() {
    
}

int Path::length() {
    return path.size();
}

pair<int, int> Path::getDest(int num) {
    return path.at(num);
}

void Path::addDest(int a, int b) {
    addDest(pair<int,int>(a,b));
}

void Path::addDest(pair<int, int> p) {
    path.push_back(p);
}
