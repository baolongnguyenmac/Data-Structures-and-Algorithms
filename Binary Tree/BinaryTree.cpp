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

        void addNode(int data) {
            if (_data == -1) {
                _data = data;
            } else if (data > _data) {
                if (_pRight == NULL) {
                    _pRight = new CNode;
                }
                _pRight->addNode(data);
            } else if (data < _data) {
                if (_pLeft == NULL) {
                    _pLeft = new CNode;
                }
                _pLeft->addNode(data);
            }
        }

        void NLR() {
            if (_data != -1) {
                cout << _data << " ";
                if (_pLeft != NULL) {
                    _pLeft->NLR();
                }
                if (_pRight != NULL) {
                    _pRight->NLR();
                }
            } else {
                cout << "Cay rong\n";
            }
        }

        void LNR() {
            if (_data != -1) {
                if (_pLeft != NULL) {
                    _pLeft->LNR();
                }
                cout << _data << " ";
                if (_pRight != NULL) {
                    _pRight->LNR();
                }
            }
        }

        void LRN() {
            if (_data != -1) {
                if (_pLeft != NULL) {
                    _pLeft->LRN();
                }
                if (_pRight != NULL) {
                    _pRight->LRN();
                }
                cout << _data << " ";
            }
        }

        CNode* search(int x) {
            if (x == _data) {
                return this;
            }
            if (x > _data && _pRight != NULL) {
                return _pRight->search(x);
            }
            if (x < _data && _pLeft != NULL) {
                return _pLeft->search(x);
            }
            return NULL;
        }

        int height() {
            if (_pLeft == NULL && _pRight == NULL) {
                if (_data == -1) {
                    return 0;
                }
                return 1;
            }
            int left = 0, right = 0;
            if (_pLeft != NULL) {
                left = _pLeft->height();
            }
            if (_pRight != NULL) {
                right = _pRight->height();
            }
            if (left > right) {
                return left + 1;
            }
            return right + 1;
        }

        int countNode() {
            if (_pLeft == NULL && _pRight == NULL) {
                if (_data == -1) {
                    return 0;
                }
                return 1;
            }
            int left = 0, right = 0;
            if (_pLeft != NULL) {
                left = _pLeft->countNode();
            }
            if (_pRight != NULL) {
                right = _pRight->countNode();
            }
            return left + right + 1;
        }

        // void remove(int x) {
        //     if (x > _data && _pRight != NULL) {
        //         _pRight->remove(x);
        //     }
        //     else if (x < _data && _pLeft != NULL) {
        //         _pLeft->remove(x);
        //     }
        //     else {
        //         CNode *del = this;
        //         if (del->_pLeft == NULL && del->_pRight == NULL) {
        //             delete del;
        //             del = NULL;
        //         }
        //     }
        // }

    private:
        int _data;
        CNode *_pLeft;
        CNode *_pRight;
};


int main(int argc, char const *argv[]) {
    CNode *myTree = new CNode;

    myTree->addNode(6);
    myTree->addNode(9);
    myTree->addNode(1);
    myTree->addNode(2);
    myTree->addNode(5);
    myTree->addNode(4);

    cout << myTree->search(6)->getData() << endl;
    cout << myTree->height() << endl;
    cout << myTree->countNode() << endl;

    return 0;
}
