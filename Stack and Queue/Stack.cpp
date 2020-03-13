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

        T getData() {
            return _data;
        }

    private:
        T _data;
        CNode<T> *_pNext = NULL;
        template <class U> friend class CStack;
};

template <class T>
class CStack {
    public:
        void push(T data) {
            if (_pHead == NULL) {
                _pHead = _pTail = new CNode<T>(data);
            }
            else {
                CNode<T> *p = new CNode<T>(data);
                p->_pNext = _pHead;
                _pHead = p;
            }
        }

        void pop() {
            try {
                if (_pHead != NULL) {
                    CNode<T> *del = _pHead;
                    _pHead = _pHead->_pNext;
                    delete del;
                }
                else {
                    throw 1;
                }
            }
            catch (int n) {
                cout << "Stack rong. Loi nullptr\n";
            }
        }

        CNode<T>* peek() {
            try {
                if (_pHead == NULL) {
                    throw 1;
                }
                return _pHead;
            }
            catch(int n) {
                cout << "Stack rong. Loi nullptr\n";
            }
        }

        bool isEmpty() {
            return _pHead == NULL;
        }

        void printStack() {
            for (CNode<T> *p = _pHead; p != NULL; p = p->_pNext) {
                cout << p->_data << " ";
            }
            cout << endl;
        }

    private:
        CNode<T> *_pHead = NULL;
        CNode<T> *_pTail = NULL;
};

int main(int argc, char const *argv[]) {
    CStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    s.printStack();
    s.pop();
    s.pop();
    s.pop();
    s.pop();

    cout << s.peek()->getData();

    return 0;
}
