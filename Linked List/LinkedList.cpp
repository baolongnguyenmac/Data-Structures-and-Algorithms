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
    // p.deleteNode(3);

    p.printList();

    return 0;
}
