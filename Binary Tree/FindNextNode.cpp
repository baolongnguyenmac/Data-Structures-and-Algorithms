/*  cài đặt này như sau
        mỗi node sẽ có 1 con trỏ để trỏ đến parent của nó
*/

#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

#include "vector"

class CNode {
    public:
        CNode(int data) {
            _data = data;
        }

        int getData() {
            return _data;
        }

        // bool operator==(CNode *p) {
        //     if (p->_data == _data && p->_pParent == _pParent && p->_pLeft == _pLeft && p->_pRight == _pRight) {
        //         return true;
        //     }
        //     return false;
        // }

    private: 
        int _data;
        CNode *_pParent = NULL;
        CNode *_pLeft = NULL;
        CNode *_pRight = NULL;
        friend class CTree;
};

class CTree {
    public: 
        CTree(int data) {
            _pRoot = new CNode(data);
        }

        void insert(int data) {
            return insert(_pRoot, data);
        }

        // tìm node tiếp theo của node *p trong TH duyệt node theo kiểu NLR
        // CNode* findNodeNLR(int x) {
            /*
                (TH1) -> 2 
                        / \
                (TH2)->1   3 <-(TH3)
            */
            // CNode *p = findNode(_pRoot, x);
            // if (p == NULL) {
            //     return NULL;
            // }
            // if (p->_pLeft != NULL) {
            //     return p->_pLeft;
            // }
            // else if () {

            // }
        // }

        // tìm node tiếp theo của node *p trong TH duyệt node theo kiểu LNR
        CNode* findNextLNR(int x) {
            /*
                (TH1) -> 2 
                        / \
                (TH2)->1   3 <-(TH3)
            */
            CNode *p = findNode(_pRoot, x);
            if (p == NULL) {
                return NULL;
            }
            else if (p->_pRight != NULL) {  // TH1
                CNode *temp = p->_pRight;
                while (temp->_pLeft != NULL) {
                    temp = temp->_pLeft;
                }
                return temp;
            }
            else if (p->_pParent->_data > p->_data) {   // TH2
                return p->_pParent;
            }
            else if (p->_pParent->_data < p->_data) {
                CNode *temp = p;
                while (temp->_pParent->_data < temp->_data) {   // TH3
                    temp = temp->_pParent;
                }
                return temp->_pParent;
            }
        }

        void BFS() {
            return BFS(_pRoot);
        }

    private:
        CNode* findNode(CNode *pRoot, int x) {
            if (pRoot == NULL) {
                return NULL;
            }
            if (x > pRoot->_data) {
                return findNode(pRoot->_pRight, x);
            }
            else if (x < pRoot->_data) {
                return findNode(pRoot->_pLeft, x);
            }
            else {
                return pRoot;
            }
        }

        void insert(CNode *&pRoot, int data) {
            if (pRoot->_pLeft == NULL && data < pRoot->_data) {
                pRoot->_pLeft = new CNode(data);
                pRoot->_pLeft->_pParent = pRoot;
            }
            else if (pRoot->_pRight == NULL && data > pRoot->_data) {
                pRoot->_pRight = new CNode(data);
                pRoot->_pRight->_pParent = pRoot;
            }
            if (data > pRoot->_data) {
                insert(pRoot->_pRight, data);
            }
            else if (data < pRoot->_data) {
                insert(pRoot->_pLeft, data);
            }
        }

        void BFS(CNode *pRoot) {
            vector<CNode*> queue;
            CNode *temp = pRoot;
            queue.push_back(temp);

            while (!queue.empty()) {
                temp = queue[0];
                queue.erase(queue.begin());
                if (temp->_pLeft != NULL) {
                    queue.push_back(temp->_pLeft);
                }
                if (temp->_pRight != NULL) {
                    queue.push_back(temp->_pRight);
                }
                cout << temp->_data << " ";
            }
        }

        CNode *_pRoot = NULL;
};

int main(int argc, char const *argv[]) {
    CTree *tree = new CTree(7);

    tree->insert(2);
    tree->insert(1);
    tree->insert(5);
    tree->insert(4);
    tree->insert(3);
    tree->insert(6);

    cout << tree->findNextLNR(6)->getData() << endl;

    return 0;
}

