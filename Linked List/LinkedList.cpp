#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

template <class T>
class CNode {
    public:
        CNode(T data) {
            _data = data;
        }
        int getData() {
            return _data;
        }

        bool operator==(CNode<T> *p) {
            if (_data == p->_data && _pNext == p->_pNext) {
                return true;
            }
            return false;
        }

    private:
        int _data;
        CNode *_pNext = NULL;
        // tại sao lại là template<class U> mà không phải là template<class T>
        template <class U> friend class CList;
};


template <class T>
class CList {
    public:
        bool isEmptyList() {
            return _pHead == NULL;
        }

        void addTail(T data) {
            if (isEmptyList()) {
                _pHead = _pTail = new CNode<T>(data);
            }
            else {
                _pTail->_pNext = new CNode<T>(data);
                _pTail = _pTail->_pNext;
            }
        }

        void printList() {
            for (CNode<T> *p = _pHead; p != NULL; p = p->_pNext) {
                cout << p->_data << " ";
            }
            cout << endl;
        }

        bool deleteNode(T del) {
            if (_pHead->_data == del) {
                CNode<T> *d = _pHead;
                _pHead = _pHead->_pNext;
                delete d;
            }
            else {
                for (CNode<T> *p = _pHead; p != NULL; p = p->_pNext) {
                    if (p->_pNext == NULL) {
                        return false;
                    }
                    else if (p->_pNext->_data == del) {
                        CNode<T> *d = p->_pNext;
                        p->_pNext = p->_pNext->_pNext;
                        delete d;
                    }
                }
            }
            return true;
        }

        bool deleteNode(CNode<T> *del) {
            if (del == _pHead) {
                _pHead = _pHead->_pNext;
                delete del;
                return true;
            }
            else {
                for (CNode<T> *q = _pHead; q != NULL; q = q->_pNext) {
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
            for (CNode<T> *p = _pHead; p != NULL; p = p->_pNext) {
                for (CNode<T> *q = p->_pNext; q != NULL; q = q->_pNext) {
                    if (p->_data == q->_data) {
                        deleteNode(q);
                    }
                }
            }
        }

        CNode<T>* findNodeKth(int k) {
            int count = 1;
            CNode<T> *p = _pHead;

            for (; p != NULL; p = p->_pNext) {
                if (count != k) {
                    count++;
                }
                else {
                    return p;
                }
            }

            return NULL;
        }

        CList<int> partition(int x) {
            CList<int> before, after;

            for (CNode<int> *p = _pHead; p != NULL; p = p->_pNext) {
                if (p->_data >= x) {
                    after.addTail(p->_data);
                }
                else {
                    before.addTail(p->_data);
                }
            }

            before._pTail->_pNext = after._pHead;
            return before;
        }

    private:
        CNode<T> *_pHead = NULL;
        CNode<T> *_pTail = NULL;
};

// template <typename T>
int main(int argc, char const *argv[]) {
    CList<int> p;
    p.addTail(1);
    p.addTail(9);
    p.addTail(2);
    p.addTail(8);
    p.addTail(3);
    p.addTail(7);
    p.addTail(4);
    p.addTail(6);
    p.addTail(5);
    p.addTail(0);

    p = p.partition(5);

    // p.deleteNode(1);
    // p.deleteNode(3);

    // p.deleteDuplicatedNode();

    // cout << p.findNodeKth(3)->getData() << endl;

    p.printList();

    return 0;
}
