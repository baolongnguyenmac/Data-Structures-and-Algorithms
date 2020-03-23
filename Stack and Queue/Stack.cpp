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
        // add item to head
        void push(T data) {
            if (isEmpty()) {
                _pHead = _pTail = new CNode<T>(data);
            }
            else {
                CNode<T> *p = new CNode<T>(data);
                p->_pNext = _pHead;
                _pHead = p;
            }
        }

        // remove the top item
        void pop() {
            try {
                if (isEmpty()) {
                    throw 1;
                }
                CNode<T> *del = _pHead;
                _pHead = _pHead->_pNext;
                delete del;
            }
            catch (int n) {
                cout << "Loi stack rong.\n";
            }
        }

        // return value of the top item
        CNode<T>* peek() {
            if (_pHead == NULL) {
                throw 1;
            }
            return _pHead;
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

        CStack(T data) {
            _pHead = _pTail = new CNode<T>(data);
        }
        CStack(){}

        ~CStack() {
            if (_pHead != NULL) {
                CNode<T> *temp;
                while (_pHead != NULL) {
                    temp = _pHead;
                    _pHead = _pHead->_pNext;
                    delete temp;
                }
                _pHead = _pHead = NULL;
            }
        }

    private:
        CNode<T> *_pHead = NULL;
        CNode<T> *_pTail = NULL;
};

int main(int argc, char const *argv[]) {

    #pragma region demo stack
    #if 1
        CStack<int> s;
        s.push(1);
        s.push(2);
        // s.push(3);
        // s.push(4);

        s.printStack();
        s.pop();
        s.pop();

        try {
            cout << s.peek()->getData() << endl;
        }
        catch(int n) {
            cout << "Loi stack rong\n";
        }
        s.printStack();
    #endif
    #pragma endregion



    return 0;
}
