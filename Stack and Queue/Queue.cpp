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
        template <class U> friend class CQueue;
};

template <class T>
class CQueue {
    public:
        CQueue(T data) {
            _pHead = _pTail = new CNode<T>(data);
        }
        CQueue(){}

        bool isEmpty() {
            return _pHead == NULL;
        }

        // add item to tail
        void add(T data) {
            if (isEmpty()) {
                _pHead = _pTail = new CNode<T>(data);
            }
            else {
                _pTail->_pNext = new CNode<T>(data);
                _pTail = _pTail->_pNext;
            }
        }

        // remove the first item
        void remove() {
            try {
                if (isEmpty()) {
                    throw 1;
                }
                CNode<T> *temp = _pHead;
                _pHead = _pHead->_pNext;
                delete temp;
            }
            catch (int n) {
                cout << "stack rong\n";
            }
        }

        // return the first node in queue
        CNode<T>* peek() {
            try {
                if (_pHead == NULL) {
                    throw 1;
                }
                return _pHead;
            }
            catch(int n) {
                cout << "Loi queue rong\n";
            }
        }

        void printQueue() {
            cout << "<-";
            for (CNode<T> *p = _pHead; p != NULL; p = p->_pNext) {
                cout << p->_data << " ";
            }
            cout << "<-" << endl;
        }

    private:
        CNode<T> *_pHead = NULL;
        CNode<T> *_pTail = NULL;
};

int main(int argc, char const *argv[]) {
    #pragma region demo queue
    #if 1
        CQueue<int> q(1);
        q.add(2);
        q.add(3);
        q.add(4);

        q.printQueue();
    #endif
    #pragma endregion


    return 0;
}
