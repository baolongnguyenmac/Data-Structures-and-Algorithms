#include "iostream"
using namespace std;

#include "stdio.h"
#include "stdlib.h"

class CNodeAVL {
    public:
        CNodeAVL() {
            _data = -1;
            _pRight = _pLeft = NULL;
        }
        CNodeAVL(int data) {
            _data = data;
            _pRight = _pLeft = NULL;
        }

        int getData() {
            return _data;
        }
        void setData(int data) {
            _data = data;
        }
        void setPLeft(CNodeAVL *p) {
            _pLeft = p;
        }
        CNodeAVL* getPLeft() {
            return _pLeft;
        }
        void setPRight(CNodeAVL *p) {
            _pRight = p;
        }
        CNodeAVL* getPRight() {
            return _pRight;
        }

        void addNode(int data) {
            if (_data == -1) {
                _data = data;
            } else if (data > _data) {
                if (_pRight == NULL) {
                    _pRight = new CNodeAVL;
                }
                _pRight->addNode(data);
            } else if (data < _data) {
                if (_pLeft == NULL) {
                    _pLeft = new CNodeAVL;
                }
                _pLeft->addNode(data);
            }
            // balance(this);
        }

        int height() {
            if (this == NULL) {
                return 0;
            }
            int left = _pLeft->height();
            int right = _pRight->height();
            if (left > right) {
                return left + 1;
            }
            return right + 1;
        }

        int diff() {
            return _pLeft->height() - _pRight->height();
        }

        CNodeAVL* leftRotate() {
            CNodeAVL *q = this->_pRight;
            this->_pRight = q->getPLeft();
            q->setPLeft(this);
            return q;
        }

        CNodeAVL* rightRotate() {
            CNodeAVL *q = this->_pLeft;
            this->_pLeft = q->getPRight();
            q->setPRight(this);
            return q;
        }

        void balance(CNodeAVL *root) {
            int delta = root->diff();

            if (delta > 1) {
                if (root->_pLeft->diff() >= 0) {
                    root = rightRotate();
                }
                else {
                    // _pLeft->leftRotate();
                    root->_pLeft = root->_pLeft->leftRotate();
                    root = rightRotate();
                }
            }
            else if (delta < -1) {
                if (_pRight->diff() <= 0) {
                    root = leftRotate();
                }
                else {
                    // _pRight->rightRotate();
                    root->_pRight = root->_pRight->rightRotate();
                    root = leftRotate();
                }
            }
        }

        CNodeAVL* search(int x) {
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

        int countNode() {
            if (this == NULL) {
                return 0;
            }
            return _pLeft->countNode() + _pRight->countNode() + 1;
        }

    private:
        int _data;
        CNodeAVL *_pLeft;
        CNodeAVL *_pRight;
};