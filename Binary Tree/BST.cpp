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
            // đến đoạn này, compiler sẽ nói là this == NULL luôn sai
            // nhưng thực tế là méo có chuyện đó nhé :)
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

        int countNode() {
            if (this == NULL) {
                return 0;
            }
            return _pLeft->countNode() + _pRight->countNode() + 1;
        }

        void remove(int x) {
            if (this == NULL) {
                return;
            }
            else if (x > _data) {
                _pRight->remove(x);
            }
            else if (x < _data) {
                _pLeft->remove(x);
            }
            else if (x == _data) {
                CNode *del = this;

                // node lá hoặc node có 1 con 
                if (del->_pLeft == NULL || del->_pRight == NULL) {
                    if (del->_pLeft != NULL) {
                        del = del->_pLeft;
                        // delete this;
                    }
                    else {
                        del = del->_pRight;
                        // delete this;
                    }
                }

                // node có 2 con 
                else {
                    CNode *leftMost = del->_pRight;
                    while (leftMost->_pLeft != NULL) {
                        leftMost = leftMost->_pLeft;
                    }
                    int temp = leftMost->_data;
                    remove(temp);
                    this->_data = temp;
                }
            }
        }

    private:
        int _data;
        CNode *_pLeft;
        CNode *_pRight;
};
