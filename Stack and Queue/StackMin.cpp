/*
    * implement a func that returns the min value of a stack whatever stack does
    * pop, push, min should take O(1) time
*/

#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

class CNode {
    public:
        CNode(int data) {
            _data = data;
        }

        int getData() {
            return _data;
        }

    private:
        int _data;
        CNode *_pNext = NULL;
        friend class CStack;
};

class CStack {
    public:
        // add item to head
        void push(int data) {
            if (isEmpty()) {
                _pHead = _pTail = new CNode(data);
            }
            else {
                CNode *p = new CNode(data);
                p->_pNext = _pHead;
                _pHead = p;
            }
        }

        bool isEmpty() {
            return _pHead == NULL;
        }

        void printStack() {
            for (CNode *p = _pHead; p != NULL; p = p->_pNext) {
                cout << p->_data << " ";
            }
            cout << endl;
        }

        CStack(int data) {
            _pHead = _pTail = new CNode(data);
        }
        CStack(){}

        ~CStack() {
            if (_pHead != NULL) {
                CNode *temp;
                while (_pHead != NULL) {
                    temp = _pHead;
                    _pHead = _pHead->_pNext;
                    delete temp;
                }
                _pHead = _pHead = NULL;
            }
        }

        // remove the top item
        int pop() {
            // try {
                if (isEmpty()) {
                    throw 1;
                }
                int meoMeo = _pHead->_data;
                CNode *del = _pHead;
                _pHead = _pHead->_pNext;
                delete del;
                return meoMeo;
            // }
            // catch (int n) {
            //     cout << "Loi stack rong.\n";
            // }
        }

        // return value of the top item
        int peek() {
            if (_pHead == NULL) {
                throw 1;
            }
            return _pHead->_data;
        }

    private:
        CNode *_pHead = NULL;
        CNode *_pTail = NULL;
};

class CStackWithMin : public CStack {
    public:
        void push(int data) {
            CStack::push(data);
            if (s1.isEmpty()) {
                s1.push(data);
            }
            else {
                if (s1.peek() > data) {
                    s1.push(data);
                }
            }
        }

        int pop() {
            try {
                int meoMeo = CStack::pop();
                if (meoMeo == s1.peek()) {
                    s1.pop();
                }
                return meoMeo;
            }
            catch (int n) {
                cout << "Loi stack rong\n";
            }
        }

        int min() {
            try {
                return s1.peek();
            }
            catch (int n) {
                cout << "Stack rong\n";
            }
        }

    private:
        CStack s1;
};

int main(int argc, char const *argv[]) {
    CStackWithMin s;
    int a[] = {8,0,2,5,9,-2,1,7,-69,69};
    int n = sizeof(a) / sizeof(int);
    for (int i = 0; i < n; i++) {
        if (rand() % 2 == 0) {
            cout << "Just pop => ";
            s.pop();
        }
        s.push(a[i]);
        cout << "stack push " << a[i] << " --- Min: " << s.min() << endl;
    }

    return 0;
}
