#include "iostream"
using namespace std;

#include "stdio.h"
#include "stdlib.h"

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

    private:
        int _data;
        CNode *_pLeft;
        CNode *_pRight;
};