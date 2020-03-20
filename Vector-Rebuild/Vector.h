#ifndef VECTOR_H_
#define VECTOR_H_

#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

template <class T>
class CVector {
    public: 
        ///////////////////
        /** Constructor **/
        ///////////////////
        CVector(unsigned int size, T originalData) {
            try {
                if (size == 0) {
                    throw 1
                }

                _capacity = 2 * size;
                _a = new T[_capacity];
                _size = size;

                for (int i = 0; i < _capacity; i++) {
                    _a[i] = originalData;
                }
            }
            catch (int n) {
                cout << "Kich thuoc ban dau cua vector khong the bang 0\n";
            }
        }

        ///////////////////////////////////
        /** Hàm liên quan đến Iterator **/
        ///////////////////////////////////
        T* begin() {
            return _a;
        }
        T* end() {
            return _a + _size;
        }

        /////////////////////////////////////////////////
        /** Hàm liên quan đến kích thước của vector **/
        /////////////////////////////////////////////////
        bool empty() {
            return _a == NULL;
        }
        unsigned int size() {
            return _size;
        }
        unsigned int capacity() {
            return _capacity;
        }
        void resize(unsigned int size) {
            // if (size <= _size) {
            //     _size = size;
            // }
            // else {
            //     if (_capacity == 0) {
            //         _capacity = 1;
            //     }
            //     while (size > _capacity) {
            //         _capacity *= 2;
            //     }
            //     T *a = new T[_capacity];
            //     for (int i = 0; i < _size; i++) {
            //         a[i] = _a[i];
            //     }

            // }
        }

        /////////////////////////////////////////////
        /**  Truy cập phần tử bên trong vector  **/
        /////////////////////////////////////////////
        T operator[](unsigned int index) {
            try {
                if (index >= _size) {
                    throw 1;
                }
                return _a[index];
            }
            catch (int n) {
                cout << "Tham so truyen vao > size of vector\n";
            }
        }
        T at(unsigned int index) {
            return *this[index];
        }
        T* front() {
            return begin();
        }
        T* last() {
            return end();
        }

        ////////////////////////////////////////////
        /** Sửa đổi phần tử bên trong vector **/
        ////////////////////////////////////////////
        void push_back(T data) {

        }

    private:    
        T *_a = NULL;
        unsigned int _size = 0;
        unsigned int _capacity = 0;
};

#endif