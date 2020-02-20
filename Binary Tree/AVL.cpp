#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

class CNodeAVL {
    public:
        CNodeAVL() {
            _data = -1;
            _pLeft = _pRight = NULL;
        }
        CNodeAVL(int data) {
            _data = data;
            _pLeft = _pRight = NULL;
        }

        int getData() {
            return _data;
        }
        CNodeAVL* getPLeft() {
            return _pLeft;
        }
        CNodeAVL* getPRight() {
            return _pRight;
        }

        void setData(int data) {
            _data = data;
        }
        void setPLeft(CNodeAVL *p) {
            _pLeft = p;
        }
        void setPRight(CNodeAVL *p) {
            _pRight = p;
        }

    private:
        int _data;
        CNodeAVL *_pLeft;
        CNodeAVL *_pRight;
        friend class CTree;
};

class CTree {
    public:
        CTree() {
            _pRoot = NULL;
        }
        CTree(int data) {
            CNodeAVL *p = new CNodeAVL(data);
            _pRoot = p;
        }

        bool isBST() {
            return isBST(_pRoot); 
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

        CNodeAVL* search(int x) {
            return search(_pRoot, x);
        }

        bool isAVL() {
            return isAVL(_pRoot);
        }

    private:
        void remove(CNodeAVL *&pRoot, int x) {
            if (pRoot == NULL) {
                return;
            }
            else if (pRoot->_data > x) {
                remove(pRoot->_pLeft, x);
                balance(pRoot);
            }
            else if (pRoot->_data < x) {
                remove(pRoot->_pRight, x);
                balance(pRoot);
            }
            else if (pRoot->_data == x) {
                CNodeAVL *del = pRoot;

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
                    CNodeAVL *leftMost = pRoot->_pRight;
                    while (leftMost->_pLeft != NULL) {
                        leftMost = leftMost->_pLeft;
                    }
                    int temp = leftMost->_data;
                    remove(pRoot, temp);
                    pRoot->_data = temp;
                }
            }
        }

        void insert(CNodeAVL *&pRoot, int data) {
            if (pRoot == NULL) {
                CNodeAVL *p = new CNodeAVL(data);
                pRoot = p;
            }
            else if (data < pRoot->_data) {
                insert(pRoot->_pLeft, data);
            }
            else if (data > pRoot->_data) {
                insert(pRoot->_pRight, data);
            }
            balance(pRoot);
        }

        void leftRotate(CNodeAVL *&p) {
            CNodeAVL *q = p->_pRight;
            p->_pRight = q->_pLeft;
            q->_pLeft = p;
            p = q;
        }

        void rightRotate(CNodeAVL *&p) {
            CNodeAVL *q = p->_pLeft;
            p->_pLeft = q->_pRight;
            q->_pRight = p;
            p = q;
        }

        int diff(CNodeAVL *p) {
            return height(p->_pLeft) - height(p->_pRight);
        }

        void balance(CNodeAVL *&p) {
            int delta = diff(p);

            // mất cân bằng trái
            if (delta > 1) {    
                if (diff(p->_pLeft) >= 0) { // mất cân bằng trái trái
                    rightRotate(p);
                }
                else {  // mất cân bằng trái phải
                    leftRotate(p->_pLeft);
                    rightRotate(p);
                }
            }

            // mất cân bằng phải
            else if (delta < -1) {
                if (diff(p->_pRight) <= 0) {    // mất cân bằng phải phải 
                    leftRotate(p);
                }
                else {  // mất cân bằng phải trái 
                    rightRotate(p->_pRight);
                    leftRotate(p);
                }
            }
        }

        int height(CNodeAVL *pRoot) {
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

        int countNode(CNodeAVL *pRoot) {
            if (pRoot == NULL) {
                return 0;
            }
            return countNode(pRoot->_pLeft) + countNode(pRoot->_pRight) + 1;
        }

        void LNR(CNodeAVL *pRoot) {
            if (pRoot != NULL) {
                LNR(pRoot->_pLeft);
                cout << pRoot->_data << " ";
                LNR(pRoot->_pRight);
            }
        }

        void NLR(CNodeAVL *pRoot) {
            if (pRoot != NULL) {
                cout << pRoot->_data << " ";
                NLR(pRoot->_pLeft);
                NLR(pRoot->_pRight);
            }
        }

        void LRN(CNodeAVL *pRoot) {
            if (pRoot != NULL) {
                LRN(pRoot->_pLeft);
                LRN(pRoot->_pRight);
                cout << pRoot->_data << " ";
            }
        }

        bool isBST(CNodeAVL *pRoot) {
            if (pRoot == NULL) {
                return true;
            }
            if (pRoot->_pLeft != NULL && pRoot->_pLeft->_data > pRoot->_data) {
                return false;
            }
            if (pRoot->_pRight != NULL && pRoot->_pRight->_data < pRoot->_data) {
                return false;
            }
            if (!isBST(pRoot->_pLeft) || !isBST(pRoot->_pRight)) {
                return false;
            }
            return true;
        }

        CNodeAVL* search(CNodeAVL *pRoot, int x) {
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

        bool isAVL(CNodeAVL *pRoot) {
            // if (isBST(pRoot)) {
            //     int delta = diff(pRoot);
            //     if (delta <= 1 && delta >= -1) {
            //         if (isAVL(pRoot->_pLeft) && isAVL(pRoot->_pRight)) {
            //             return true;
            //         }
            //     }
            // }
            // return false;
        }

        CNodeAVL *_pRoot;
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
    tree->remove(3);
    tree->remove(4);
    tree->remove(5);

    if (tree->isAVL()) {
        cout << "fuck\n";
    }

    // tree->LNR();

    return 0;
}
