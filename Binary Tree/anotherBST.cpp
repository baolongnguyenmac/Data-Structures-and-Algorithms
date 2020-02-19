#include <iostream>
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

    private:
        int _data;
        CNode* _pLeft;
        CNode* _pRight;
        friend class CTree;
};

class CTree {
    public:
        CTree() {
            _pRoot = NULL;
        }

        void insert(int data) {
            insert(_pRoot, data);
        }

        void LNR() {
            LNR(_pRoot);
        }

        void remove(int x) {
            remove(_pRoot, x);
        }

    private:
        CNode* _pRoot;

        void remove(CNode *&root, int x) {
            if (root == NULL) {
                return;
            }
            else if (x > root->_data) {
                remove(root->_pRight, x);
            }
            else if (x < root->_data) {
                remove(root->_pLeft, x);
            }
            else if (x == root->_data) {
                CNode *del = root;

                if (root->_pLeft == NULL) {
                    root = root->_pRight;
                    delete del;
                }
                else if (root->_pRight == NULL) {
                    root = root->_pLeft;
                    delete del;
                }
                else {
                    CNode *leftMost = root->_pRight;
                    while (leftMost->_pLeft != NULL) {
                        leftMost = leftMost->_pLeft;
                    }
                    int temp = leftMost->_data;
                    remove(root, temp);
                    root->_data = temp;
                }
            }
        }

        bool isEmptyTree(CNode* root) {
            return root == NULL;
        }

        void insert(CNode*& root, int data) {
            if (isEmptyTree(root)) {
                CNode* p = new CNode(data);
                root = p;
            }
            else if (data > root->_data) {
                insert(root->_pRight, data);
            }
            else if (data < root->_data) {
                insert(root->_pLeft, data);
            }
        }

        void LNR(CNode* root) {
            if (root != NULL) {
                LNR(root->_pLeft);
                cout << root->_data << " ";
                LNR(root->_pRight);
            }
        }
};

int main(int argc, char const *argv[]) {
    CTree *tree = new CTree;

    tree->insert(2);
    tree->insert(1);
    tree->insert(3);
    tree->insert(6);
    tree->insert(-45);

    tree->LNR();
    cout << endl;

    tree->remove(2);
    tree->LNR();
    cout << endl;

    return 0;
}
