#include "maze.h"
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>

using namespace std;

DisjointSets Maze::getSets() const {
    return maze;
}

void Maze::printMaze() const
{
    cout << setw(3) << " ";
    for (int j=0; j<ncols; j++) {
        cout << setw(6) << "______";
    }
    for (int i=0; i<nrows; i++) {
        cout << endl;
        cout << setw(3) << "|";
        for (int j=0; j<ncols-1; j++) {
            int val = i*nrows+j;
            cout << setw(3) << val<<setw(3);
            if (noWalls.empty() ||
                (find(noWalls.begin(),noWalls.end(),pair<int,int>(val,val+1)) == noWalls.end() &&
                 find(noWalls.begin(),noWalls.end(),pair<int,int>(val+1,val)) == noWalls.end())
                    )
                cout << "|";
            else
                cout <<" ";
        }
        int val = i*nrows+ncols-1;
        cout << setw(3) << val<<setw(3) << "|";
        cout <<endl;
        cout << setw(3) << " ";
        for (int j=0; j<ncols; j++) {
            int val = i*nrows+j;
            if (i<nrows-1) {
                if ( noWalls.empty() ||
                     (find(noWalls.begin(), noWalls.end(), pair<int, int>(val, val + ncols)) == noWalls.end()
                      && find(noWalls.begin(), noWalls.end(), pair<int, int>(val+ncols, val)) == noWalls.end())
                        )
                    cout << setw(6) << "______";
                else
                    cout << setw(6) << " ";
            } else
                cout << setw(6) << "______";
        }

    }
    cout <<endl << endl;
}



// a implementar

Maze::Maze(int rows, int cols):nrows(rows),ncols(cols),maze(rows*cols) {
}

vector<int> Maze::getNeighbours(int x) const {
    vector<int> res;
    return res;
}

void Maze::buildRandomMaze() {
    const size_t sz = nrows*ncols;
    while(maze.getNumberOfSets() > 1){
        int x = rand()%sz, y = rand()%sz;
        int x1 = x/ncols, x2 = x%ncols, y1 = y/ncols, y2 = y%ncols;
        int v1 = maze.find(x), v2 = maze.find(y);
        if(v1 != v2 && abs(x1-y1)+abs(x2-y2) == 1){
            maze.unionSets(v1,v2);
            noWalls.push_back(make_pair(x,y));
            printMaze();
        }
    }
}

