#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

class CNode {
    public:
        CNode(int data) {
            _data = data;
        }

    private:
        int _data;
        CNode *_pNext = NULL;
        friend class CList;
};

class CList {
    public:
        bool isEmptyList() {
            return _pHead == NULL;
        }

        void addTail(int data) {
            if (isEmptyList()) {
                _pHead = _pTail = new CNode(data);
            }
            else {
                _pTail->_pNext = new CNode(data);
                _pTail = _pTail->_pNext;
            }
        }

        void printList() {
            for (CNode *p = _pHead; p != NULL; p = p->_pNext) {
                cout << p->_data << " ";
            }
            cout << endl;
        }

        bool deleteNode(int del) {
            if (_pHead->_data == del) {
                CNode *d = _pHead;
                _pHead = _pHead->_pNext;
                delete d;
            }
            else {
                for (CNode *p = _pHead; p != NULL; p = p->_pNext) {
                    if (p->_pNext == NULL) {
                        return false;
                    }
                    else if (p->_pNext->_data == del) {
                        CNode *d = p->_pNext;
                        p->_pNext = p->_pNext->_pNext;
                        delete d;
                    }
                }
            }
            return true;
        }

    private:
        CNode *_pHead = NULL;
        CNode *_pTail = NULL;
};

int main(int argc, char const *argv[]) {
    CList p;
    p.addTail(1);
    p.addTail(2);
    p.addTail(3);
    p.addTail(4);
    p.addTail(5);

    // p.deleteNode(1);
    p.deleteNode(3);

    p.printList();

    return 0;
}
