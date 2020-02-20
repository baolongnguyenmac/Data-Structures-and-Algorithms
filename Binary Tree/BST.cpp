#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

class CNode {
    public:
        CNode() {
            _data = -1;
            _pLeft = _pRight = NULL;
        }
        CNode(int data) {
            _data = data;
            _pLeft = _pRight = NULL;
        }

        int getData() {
            return _data;
        }
        CNode* getPLeft() {
            return _pLeft;
        }
        CNode* getPRight() {
            return _pRight;
        }

        void setData(int data) {
            _data = data;
        }
        void setPLeft(CNode *p) {
            _pLeft = p;
        }
        void setPRight(CNode *p) {
            _pRight = p;
        }

    private:
        int _data;
        CNode *_pLeft;
        CNode *_pRight;
        friend class CTree;
};

class CTree {
    public:
        CTree() {
            _pRoot = NULL;
        }
        CTree(int data) {
            CNode *p = new CNode(data);
            _pRoot = p;
        }

        void remove(int x) {
            remove(_pRoot, x);
        }

        void insert(int data) {
            insert(_pRoot, data);
        }

        int height() {
            return height(_pRoot);
        }

        int countNode() {
            return countNode(_pRoot);
        }

        void LNR() {
            LNR(_pRoot);
        }

        void NLR() {
            NLR(_pRoot);
        }

        void LRN() {
            LRN(_pRoot);
        }

        CNode* search(int x) {
            return search(_pRoot, x);
        }

    private:
        void remove(CNode *&pRoot, int x) {
            if (pRoot == NULL) {
                return;
            }
            else if (pRoot->_data > x) {
                remove(pRoot->_pLeft, x);
            }
            else if (pRoot->_data < x) {
                remove(pRoot->_pRight, x);
            }
            else if (pRoot->_data == x) {
                CNode *del = pRoot;

                // node co 1 con or k co con
                if (pRoot->_pLeft == NULL) {
                    pRoot = pRoot->_pRight;
                    delete del;
                }
                else if (pRoot->_pRight == NULL) {
                    pRoot = pRoot->_pLeft;
                    delete del;
                }
                else {  // node 2 con
                    CNode *leftMost = pRoot->_pRight;
                    while (leftMost->_pLeft != NULL) {
                        leftMost = leftMost->_pLeft;
                    }
                    int temp = leftMost->_data;
                    remove(pRoot, temp);
                    pRoot->_data = temp;
                }
            }
        }

        void insert(CNode *&pRoot, int data) {
            if (pRoot == NULL) {
                CNode *p = new CNode(data);
                pRoot = p;
            }
            else if (data < pRoot->_data) {
                insert(pRoot->_pLeft, data);
            }
            else if (data > pRoot->_data) {
                insert(pRoot->_pRight, data);
            }
        }

        int height(CNode *pRoot) {
            if (pRoot == NULL) {
                return 0;
            }
            int left = height(pRoot->_pLeft);
            int right = height(pRoot->_pRight);
            if (left > right) {
                return left + 1;
            }
            return right + 1;
        }

        int countNode(CNode *pRoot) {
            if (pRoot == NULL) {
                return 0;
            }
            return countNode(pRoot->_pLeft) + countNode(pRoot->_pRight) + 1;
        }

        void LNR(CNode *pRoot) {
            if (pRoot != NULL) {
                LNR(pRoot->_pLeft);
                cout << pRoot->_data << " ";
                LNR(pRoot->_pRight);
            }
        }

        void NLR(CNode *pRoot) {
            if (pRoot != NULL) {
                cout << pRoot->_data << " ";
                NLR(pRoot->_pLeft);
                NLR(pRoot->_pRight);
            }
        }

        void LRN(CNode *pRoot) {
            if (pRoot != NULL) {
                LRN(pRoot->_pLeft);
                LRN(pRoot->_pRight);
                cout << pRoot->_data << " ";
            }
        }

        CNode* search(CNode *pRoot, int x) {
            if (pRoot != NULL) {
                if (pRoot->_data == x) {
                    return pRoot;
                }
                else if (pRoot->_data > x) {
                    return search(pRoot->_pLeft, x);
                }
                else {
                    return search(pRoot->_pRight, x);
                }
            }
            return NULL;
        }

        CNode *_pRoot;
};

int main(int argc, char const *argv[]) {
    CTree *tree = new CTree;

    tree->insert(3);
    tree->insert(4);
    tree->insert(2);
    tree->insert(1);
    tree->insert(5);

    tree->LNR();
    cout << endl;

    tree->remove(1);

    tree->LNR();

    return 0;
}
