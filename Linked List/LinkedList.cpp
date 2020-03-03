#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

class CNode {
    public:
        CNode(int data) {
            _data = data;
        }

        bool operator==(CNode *p) {
            if (_data == p->_data && _pNext == p->_pNext) {
                return true;
            }
            return false;
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

        bool deleteNode(CNode *del) {
            if (del == _pHead) {
                _pHead = _pHead->_pNext;
                delete del;
                return true;
            }
            else {
                for (CNode *q = _pHead; q != NULL; q = q->_pNext) {
                    if (q->_pNext == del) {
                        q->_pNext = q->_pNext->_pNext;
                        delete del;
                        return true;
                    }
                }
            }
            return false;
        }

        void deleteDuplicatedNode() {
            for (CNode *p = _pHead; p != NULL; p = p->_pNext) {
                for (CNode *q = p->_pNext; q != NULL; q = q->_pNext) {
                    if (p->_data == q->_data) {
                        deleteNode(q);
                    }
                }
            }
        }

    private:
        CNode *_pHead = NULL;
        CNode *_pTail = NULL;
};

int main(int argc, char const *argv[]) {
    CList p;
    p.addTail(1);
    p.addTail(1);
    p.addTail(2);
    p.addTail(2);
    p.addTail(2);

    // p.deleteNode(1);
    // p.deleteNode(3);

    p.deleteDuplicatedNode();

    p.printList();

    return 0;
}
