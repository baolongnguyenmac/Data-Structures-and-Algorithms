#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

#include "fstream"
#include "vector"
#include "string"

#define MAX 100

class CGraph {
    public:
        CGraph() {
            _v = 0;
            for (int i = 0; i < MAX; i++) {
                for (int j = 0; j < MAX; j++) {
                    _adjacency[i][j] = 0;
                }
            }
        }

        void addEdge(int v1, int v2) {
            _adjacency[v1][v2] = 1;
        }

        void generateIsVisitedVector() {
            if (_isVisited.empty()) {
                for (int i = 0; i < _v; i++) {
                    _isVisited.push_back(false);
                }
            }
            else {
                for (int i = 0; i < _v; i++) {
                    _isVisited[i] = false;
                }
            }
        }

        void readAdjMatrix(string fileName) {
            fstream file(fileName, ios::in);
            int temp;

            file >> _v;

            for (int i = 0; i < _v; i++) {
                for (int j = 0; j < _v; j++) {
                    file >> temp;
                    if (temp == 1) {
                        addEdge(i, j);
                    }
                }
            }
        }

        void BFS(int start) {
            generateIsVisitedVector();
            vector<int> queue;

            queue.push_back(start);
            _isVisited[start] = true;

            while (!queue.empty()) {
                int temp = queue[0];
                cout << temp << " ";
                queue.erase(queue.begin());

                for (int i = 0; i < _v; i++) {
                    if (_adjacency[temp][i] == 1 && !_isVisited[i]) {
                        _isVisited[i] = true;
                        queue.push_back(i);
                    }
                }
            }
        }

        void DFS(int start) {
            generateIsVisitedVector();
            DFS(start, _isVisited);
        }

        // implement base on BFS
        bool isConnectedBFS(int start) {
            vector<int> queue;
            generateIsVisitedVector();

            queue.push_back(start);
            _isVisited[start] = true;

            int temp;
            while (!queue.empty()) {
                temp = queue[0];
                queue.erase(queue.begin());
                for (int i = 0; i < _v; i++) {
                    if (_adjacency[temp][i] == 1 && !_isVisited[i]) {
                        queue.push_back(i);
                        _isVisited[i] = true;
                    }
                }
            }

            for (int i = 0; i < _isVisited.size(); i++) {
                if (!_isVisited[i]) {
                    return false;
                }
            }
            return true;
        }

        // implement base on DFS
        bool isConnectedDFS(int start) {
            generateIsVisitedVector();
            isConnectedDFS(start, _isVisited);
            for (int i = 0; i < _isVisited.size(); i++) {
                if (!_isVisited[i]) {
                    return false;
                }
            }
            return true;
        }

    private:
        int _v;
        int _adjacency[MAX][MAX];
        vector<bool> _isVisited;

        void DFS(int start, vector<bool> &isVisited) {
            cout << start << " ";
            isVisited[start] = true;

            for (int i = 0; i < _v; i++) {
                if (_adjacency[start][i] == 1 && !isVisited[i]) {
                    DFS(i, isVisited);
                }
            }
        }

        void isConnectedDFS(int start, vector<bool> &isVisited) {
            isVisited[start] = true;

            for (int i = 0; i < _v; i++) {
                if (_adjacency[start][i] == 1 && !isVisited[i]) {
                    DFS(i, isVisited);
                }
            }
        }
};

int main(int argc, char const *argv[]) {
    CGraph *g = new CGraph;
    g->readAdjMatrix("adjacencyMatrix.txt");

    g->DFS(0);
    cout << endl;
    g->DFS(0);
    cout << endl;

    return 0;
}
