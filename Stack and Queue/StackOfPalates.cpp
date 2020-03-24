/*
    * Imagine a (literal) stack of plates. If the stack gets too high, it might topple.
    * Therefore, in real life, we would likely start a new stack when the previous stack exceeds some
    * threshold. Implement a data structure SetOfStacks that mimics this. SetOfStacks should be
    * composed of several stacks and should create a new stack once the previous one exceeds capacity.
    * SetOfStacks. push() and SetOfStacks. pop() should behave identically to a single stack
    * (that is, pop () should return the same values as it would if there were just a single stack). 
*/

#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

#include "vector"

class CNode {
    public:
        int getData() {
            return _data;
        }

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
        bool isEmpty() {
            return _pHead == NULL;
        }

        void addHead(int data) {
            if (isEmpty()) {
                _pHead = _pTail = new CNode(data);
            }
            else {
                CNode *p = new CNode(data);
                p->_pNext = _pHead;
                _pHead = p;
            }
        }

        void delHead() {
            if (isEmpty()) {
                throw 1;
            }
            CNode *del = _pHead;
            _pHead = _pHead->_pNext;
            delete del;
        }

        CNode* getHead() {
            return _pHead;
        }

        void printList() {
            for (CNode *p = _pHead; p != NULL; p = p->_pNext) {
                cout << p->_data << " ";
            }
        }

    private:
        CNode *_pHead = NULL;
        CNode *_pTail = NULL;
};

class CStack {
    public:
        CStack(int capacity) {
            _size = 0;
            _capacity = capacity;
        }

        bool isFull() {
            return _size == _capacity;
        }

        bool isEmpty() {
            return _list.isEmpty();
        }

        void push(int data) {
            try {
                push(data, *this);
            }
            catch (int n) {
                cout << "Stack overflow\n";
            }
        }

        int pop() {
            try {
                return pop(*this);
            }
            catch (int n) {
                cout << "stack empty - return INT_MAX\n";
            }
            return INT_MAX;
        }

        int peek() {
            try {
                return peek(*this);
            }
            catch (int n) {
                cout << "stack empty - return INT_MAX\n";
            }
            return INT_MAX;
        }

        void printStack() {
            try {
                printStack(*this);
            }
            catch (int n) {
                cout << "Stack rong\n";
            }
        }

    private:
        void push(int data, CStack &s) {
            if (s.isFull()) {
                throw 1;
            }
            s._list.addHead(data);
            s._size++;
        }

        int pop(CStack &s) {
            if (s.isEmpty()) {
                throw 1;
            }
            int top = s._list.getHead()->getData();
            s._list.delHead();
            s._size--;
            return top;
        }

        int peek(CStack s) {
            if (s.isEmpty()) {
                throw 1;
            }
            return s._list.getHead()->getData();
        }

        void printStack(CStack s) {
            if (s.isEmpty()) {
                throw 1;
            }
            s._list.printList();
        }

        CList _list;
        int _size;
        int _capacity;
        friend class CSetOfStacks;
};


class CSetOfStacks {
    public:
        CSetOfStacks(int capacity) {
            _capacity = capacity;
        }

        void push(int data) {
            try {
                push(data, *this);
            }
            catch (int n) {
                cout << "Stack Overflow\n";
            }
        }

        int pop() {
            try {
                return pop(*this);
            }
            catch (int n) {
                cout << "stack empty - return INT_MAX\n";
            }
            return INT_MAX;
        }

        int peek() {
            try {
                return peek(*this);
            }
            catch (int n) {
                cout << "stack empty - return INT_MAX\n";
            }
            return INT_MAX;
        }

        void printStack() {
            try {
                printStack(*this);
            }
            catch (int n) {
                cout << "stack empty\n";
            }
        }

    private:
        void printStack(CSetOfStacks s) {
            CStack *last = s.getLastStack();
            if (last == NULL) {
                throw 1;
            }
            if (last->isEmpty()) {
                s._setOfStacks.pop_back();
                if (s._setOfStacks.empty()) {
                    throw 1;
                }
            }
            for (int i = s._setOfStacks.size() - 1; i >= 0; i--) {
                s._setOfStacks[i]->printStack(*s._setOfStacks[i]);
            }
        }

        CStack* getLastStack() {
            if (_setOfStacks.empty()) {
                return NULL;
            }
            return _setOfStacks.back();
        }

        void push(int data, CSetOfStacks &s) {
            CStack *last = s.getLastStack();
            if (last == NULL || last->isFull()) {
                CStack *temp = new CStack(_capacity);
                temp->push(data, *temp);
                s._setOfStacks.push_back(temp);
            }
            else {
                last->push(data, *last);
            }
        }

        int pop(CSetOfStacks &s) {
            CStack *last = s.getLastStack();
            if (last == NULL) {
                throw 1;
            }
            if (last->isEmpty()) {
                s._setOfStacks.pop_back();
                if (s._setOfStacks.empty()) {
                    throw 1;
                }
            }
            last = s.getLastStack();
            return last->pop(*last);
        }

        int peek(CSetOfStacks s) {
            CStack *last = s.getLastStack();
            if (last == NULL) {
                throw 1;
            }
            if (last->isEmpty()) {
                s._setOfStacks.pop_back();
                if (s._setOfStacks.empty()) {
                    throw 1;
                }
            }
            last = s.getLastStack();
            return last->peek(*last);
        }

        vector<CStack*> _setOfStacks;
        int _capacity;
};

int main(int argc, char const *argv[]) {
    CSetOfStacks *s = new CSetOfStacks(3);
    for (int i = 0; i < 10; i++) {
        s->push(i);
    }

    for (int i = 0; i < 11; i++) {
        s->printStack();    
        cout << "pop: " << s->pop() << endl;
    }
    cout << endl;

    return 0;
}
