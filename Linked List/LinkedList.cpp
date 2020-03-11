#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

#include "cmath"

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

        // chia list ra làm 2 phần, 1 lớn hơn hoặc bằng x và 1 nhỏ hơn x :>
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

        /*  * mỗi list biểu diễn ngược 1 số tự nhiên, viết hàm tính tổng 2 list
            * cơ mà với kiểu viết code này thì công trừ nhân chia 2 list cũng được nữa :) 
            * input: (7->1->6) + (5->9->2) = 617 + 295 = 912
            * output: (2->1->9)
        */
        static CList<int> sumList(CList<int> l1, CList<int> l2) {
            int n1 = convertListToNumber(l1);
            int n2 = convertListToNumber(l2);

            return convertNumberToList(n1 + n2);
        }

        // // cũng là cộng list but 1 phiên bản chạy ngon hơn (chỉ mất O(m) với size(list1) = n < size(list2) = m)
        // CList<int> sumList(CList<int> l) {
        //     CList<int> result;
        //     int n1 = length(*this);
        //     int n2 = length(l);
        //     int n = n1>n2?n1:n2;

        //     for (int i = 0; i < n; i++) {

        //     }
        // }

        static bool isPalindrome(CList<int> list) {
            CList<int> reverse = reverseList(list);
            CNode<int> *q = reverse._pHead;

            for (CNode<int> *p = list._pHead; p != NULL; p = p->_pNext) {
                if (p->_data != q->_data) {
                    return false;
                }
                q = q->_pNext;
            }
            return true;
        }

    private:
        CNode<T> *_pHead = NULL;
        CNode<T> *_pTail = NULL;

        static CList<T> reverseList(CList<T> list) {
            CList<T> reverse;
            for (CNode<T> *p = list._pHead; p != NULL; p = p->_pNext) {
                reverse.addHead(p->_data);
            }
            return reverse;
        }

        void addHead(T data) {
            if (_pHead == NULL) {
                _pHead = _pTail = new CNode<T> (data);
            }
            else {
                CNode<T> *p = new CNode<T> (data);
                p->_pNext = _pHead;
                _pHead = p;
            }
        }

        int length(CList<T> list) {
            int count = 0;
            for (CNode<T> *p = list._pHead; p != NULL; p = p->_pNext) {
                count++;
            }
            return count;
        }

        static int convertListToNumber(CList<int> l) {
            int n = 0;
            int count = 0;
            for (CNode<int> *p = l._pHead; p != NULL; p = p->_pNext) {
                n = n + p->_data * pow(10, count);
                count++;
            }
            return n;
        }

        static CList<int> convertNumberToList(int n) {
            CList<int> list;
            while (n != 0) {
                list.addTail(n % 10);
                n/=10;
            }
            return list;
        }
};

// template <typename T>
int main(int argc, char const *argv[]) {
    // CList<int> p;
    // p.addTail(1);
    // p.addTail(9);
    // p.addTail(2);
    // p.addTail(8);
    // p.addTail(3);
    // p.addTail(7);
    // p.addTail(4);
    // p.addTail(6);
    // p.addTail(5);
    // p.addTail(0);

    // p = p.partition(5);

    // p.deleteNode(1);
    // p.deleteNode(3);

    // p.deleteDuplicatedNode();

    // cout << p.findNodeKth(3)->getData() << endl;

    // p.printList();

    // CList<int> p;
    // p.addTail(7);
    // p.addTail(1);
    // p.addTail(6);

    // CList<int> q;
    // q.addTail(5);
    // q.addTail(9);
    // q.addTail(2);

    // CList<int> kq = CList<int>::sumList(p, q);
    // kq.printList();

    // cout << CList<int>::convertListToNumber(p) << endl;
    // cout << CList<int>::convertListToNumber(q) << endl;

    CList<int> q;
    q.addTail(1);
    q.addTail(1);
    // q.addTail(0);

    cout << CList<int>::isPalindrome(q) << endl;

    return 0;
}
