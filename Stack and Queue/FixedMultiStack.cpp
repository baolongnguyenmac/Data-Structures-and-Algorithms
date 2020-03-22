/*
    * implement 3 stacks in an array :>
    * the capacity of each stack can not be changed
    * idea: devide an array into 3 equal parts and do stuff
*/

// #ifndef FIXED_MULTI_STACK_
// #define FIXED_MULTI_STACK_

#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

class FixedMultiStack {
    public:
        FixedMultiStack(int sizeOfStack) {
            _capacity = sizeOfStack;
            _value = new int[sizeOfStack * _numOfStacks];
            for (int i = 0; i < _numOfStacks; i++) {
                _sizes[i] = 0;
            }
        }

        bool isFull(int stackNum) {
            return _sizes[stackNum] == _capacity;
        }

        bool isEmpty(int stackNum) {
            return _sizes[stackNum] == 0;
        }

        void pop(int stackNum) {
            try {
                if (isEmpty(stackNum)) {
                    throw 1;
                }
                _value[topIndexOfStack(stackNum)] = 0;
                _sizes[stackNum]--;
            }
            catch (int n) {
                cout << "Stack " << stackNum << " is empty\n";
            }
        }

        int peek(int stackNum) {
            try {
                if (isEmpty(stackNum)) {
                    throw 1;
                }
                return _value[topIndexOfStack(stackNum)];
            }
            catch (int n) {
                cout << "Stack " << stackNum << " is empty\n";
            }
        }

        int topIndexOfStack(int stackNum) {
            if (isEmpty(stackNum)) {
                return stackNum * _capacity;
            }
            return stackNum * _capacity + _sizes[stackNum] - 1;
        }

        void push(int data, int stackNum) {
            if (!isFull(stackNum)) {
                _sizes[stackNum]++;
                _value[topIndexOfStack(stackNum)] = data;
            }
            else {
                cout << "Stack " << stackNum << " is full\n";
            }
        }

        void printStack(int stackNum) {
            if (!isEmpty(stackNum)) {
                for (int i = 0; i < _sizes[stackNum]; i++) {
                    cout << _value[_capacity * stackNum + i] << " ";
                }
                cout << endl;
            }
            else {
                cout << "Stack " << stackNum << " is empty\n";
            }
        }

    private:
        const int _numOfStacks = 3;
        int _capacity = 0;
        int *_value = NULL;
        int *_sizes = new int[_numOfStacks];
};

int main(int argc, char const *argv[]) {
    FixedMultiStack *stack = new FixedMultiStack(3);
    stack->push(1, 0);
    stack->push(2, 0);
    stack->push(3, 0);
    stack->push(4, 1);
    stack->push(5, 1);
    stack->push(6, 1);
    stack->push(7, 2);
    stack->push(8, 2);
    stack->push(9, 2);


    stack->pop(0);
    stack->pop(1);
    stack->pop(2);
    stack->pop(0);
    stack->pop(1);
    stack->pop(2);
    stack->pop(0);
    stack->pop(1);
    stack->pop(2);

    for (int i = 0; i < 3; i++) {
        stack->printStack(i);
    }

    return 0;
}


// #endif