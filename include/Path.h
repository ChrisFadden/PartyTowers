#ifndef PATH_H
#define PATH_H

#include "GameObject.h"
#include <vector>

using namespace std;

class Path {
    public:
        Path();
        pair<int,int> getDest(int);
        void addDest(pair<int,int>);
        void addDest(int, int);
        int length();

    private:
        vector<pair<int,int>> path;
};

#endif
