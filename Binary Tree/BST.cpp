#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

#include "vector"

template <class T>
class CNodeLinkedList {
    public:
        CNodeLinkedList(T data) {
            _data = data;
        }
        int getData() {
            return _data;
        }

    private:
        T _data;
        CNodeLinkedList *_pNext = NULL;
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
                _pHead = _pTail = new CNodeLinkedList<T>(data);
            }
            else {
                _pTail->_pNext = new CNodeLinkedList<T>(data);
                _pTail = _pTail->_pNext;
            }
        }

        void printList() {
            for (CNodeLinkedList<T> *p = _pHead; p != NULL; p = p->_pNext) {
                cout << p->_data << " ";
            }
            cout << endl;
        }

    private:
        CNodeLinkedList<T> *_pHead = NULL;
        CNodeLinkedList<T> *_pTail = NULL;
};

class CNode {
    public:
        CNode() {
            _data = -1;
            _pLeft = _pRight = NULL;
        }
        CNode(int data) {
            _data = data;
            _pLeft = _pRight = NULL;
        }

        int getData() {
            return _data;
        }
        CNode* getPLeft() {
            return _pLeft;
        }
        CNode* getPRight() {
            return _pRight;
        }

        void setData(int data) {
            _data = data;
        }
        void setPLeft(CNode *p) {
            _pLeft = p;
        }
        void setPRight(CNode *p) {
            _pRight = p;
        }

        friend ostream& operator<<(ostream &os, CNode *p) {
            os << p->_data;
            return os;
        }

    private:
        int _data;
        CNode *_pLeft;
        CNode *_pRight;
        friend class CTree;
};

class CTree {
    public:
        CTree() {
            _pRoot = NULL;
        }
        CTree(int data) {
            CNode *p = new CNode(data);
            _pRoot = p;
        }

        void remove(int x) {
            remove(_pRoot, x);
        }

        void insert(int data) {
            insert(_pRoot, data);
        }

        int height() {
            return height(_pRoot);
        }

        int countNode() {
            return countNode(_pRoot);
        }

        void LNR() {
            LNR(_pRoot);
        }

        void NLR() {
            NLR(_pRoot);
        }

        void LRN() {
            LRN(_pRoot);
        }

        CNode* search(int x) {
            return search(_pRoot, x);
        }

        void BFS() {
            BFS(_pRoot);
        }

        CTree createBSTfromSortedArr(int a[], int left, int right) {
            CTree tree;
            createBSTfromSortedArr(tree._pRoot, a, left, right);
            return tree;
        }

        vector<CList<CNode*> > createVectorList() {
            return createVectorList(_pRoot);
        }

        bool isBalanced() {
            if (checkHeight(_pRoot) == -1) {
                return false;
            }
            return true;
        }

        bool isValidBST() {
            // // method1
            // return isValidBST(_pRoot);

            // method 2
            return isValidBST(_pRoot, NULL);
        }

    private:
        // valid BST
        // CÀI ĐẶT BẰNG ĐỆ QUY Min/Max (sách ngta gọi nv :>)
        bool isValidBST(CNode *pRoot) {
            if (pRoot == NULL) {
                return true;
            }
            if (pRoot->_pLeft != NULL && pRoot->_data <= pRoot->_pLeft->_data) {
                return false;
            }
            if (pRoot->_pRight != NULL && pRoot->_data >= pRoot->_pRight->_data) {
                return false;
            }
            return isValidBST(pRoot->_pLeft) && isValidBST(pRoot->_pRight);

            /*  another idea: Duyệt NLR sau đó lưu vào 1 mảng -> kiểu tra tính tăng dần của mảng đó 
                => quá ease nên méo cài :>
            */
        }

        // valid BST
        // CÀI ĐẶT BẰNG ĐỆ QUY theo kiểu LNR
        bool isValidBST(CNode *pRoot, int *lastData) {
            /*
                ý tưởng: duyệt cây theo kiểu LNR và kiểm tra tăng dần trực tiếp trên cây chứ k thông qua mảng
                hình dung: 
                    add lần lượt các node 2, 1, 3 vào cây
                    thứ tự duyệt sẽ là 1, 2, 3
                    khi đó, 1 sẽ là lastData so với 2 (trong TH đang xét node 2), 2 sẽ là lastData so với 3 (trong TH đang xét node 3)
                    vì 1 lý do nào đó mà 1 > 2 (lastData > proot->data) thì sẽ return false
            */

            if (pRoot == NULL) {
                return true;
            }
            if (!isValidBST(pRoot->_pLeft, lastData)) {
                return false;
            }
            if (lastData != NULL && *lastData > pRoot->_data) {
                return false;
            }
            *lastData = pRoot->_data;
            if (!isValidBST(pRoot->_pRight, lastData)) {
                return false;
            }

            return true;
        }

        // check if balanced ver dev (not coder)
        int checkHeight(CNode *pRoot) {
            if (pRoot == NULL) {
                return 0;
            }
            int left = checkHeight(pRoot->_pLeft);
            if (left == -1) {
                return -1;
            }
            int right = checkHeight(pRoot->_pRight);
            if (right == -1) {
                return -1;
            }

            if (abs(left - right) > 1) {    // tìm thấy lỗi 
                return -1;
            }

            if (left > right) {
                return left + 1;
            }
            return right +1;
            
        }

        // create a minimal tree from a sorted array (increasing order)
        void createBSTfromSortedArr(CNode *&pRoot, int a[], int left, int right) {
            if (left <= right) {
                int mid = (left + right) / 2;
                pRoot = new CNode(a[mid]);
                createBSTfromSortedArr(pRoot->_pLeft, a, left, mid - 1);
                createBSTfromSortedArr(pRoot->_pRight, a, mid + 1, right);
            }
        }

        void createListByGivenLevel(CNode *pRoot, CList<CNode*> &list, int level) {
            if (pRoot != NULL) {
                if (level == 1) {
                    list.addTail(pRoot);
                }
                else {
                    createListByGivenLevel(pRoot->_pLeft, list, level - 1);
                    createListByGivenLevel(pRoot->_pRight, list, level - 1);
                }
            }
        }

        //  create a linked list of all the nodes at each depth 
        // (e.g., if you have a tree with depth D, you'll have D linked lists
        vector<CList<CNode*> > createVectorList(CNode *pRoot) {
            vector<CList<CNode*> > linkedListByLevelOrder;
            int h = height();

            for (int i = 1; i <= h; i++) {
                CList<CNode*> temp;
                createListByGivenLevel(pRoot, temp, i);
                linkedListByLevelOrder.push_back(temp);
            }
            return linkedListByLevelOrder;
        }

        void remove(CNode *&pRoot, int x) {
            if (pRoot == NULL) {
                return;
            }
            else if (pRoot->_data > x) {
                remove(pRoot->_pLeft, x);
            }
            else if (pRoot->_data < x) {
                remove(pRoot->_pRight, x);
            }
            else if (pRoot->_data == x) {
                CNode *del = pRoot;

                // node co 1 con or k co con
                if (pRoot->_pLeft == NULL) {
                    pRoot = pRoot->_pRight;
                    delete del;
                }
                else if (pRoot->_pRight == NULL) {
                    pRoot = pRoot->_pLeft;
                    delete del;
                }
                else {  // node 2 con
                    CNode *leftMost = pRoot->_pRight;
                    while (leftMost->_pLeft != NULL) {
                        leftMost = leftMost->_pLeft;
                    }
                    int temp = leftMost->_data;
                    remove(pRoot, temp);
                    pRoot->_data = temp;
                }
            }
        }

        void insert(CNode *&pRoot, int data) {
            if (pRoot == NULL) {
                CNode *p = new CNode(data);
                pRoot = p;
            }
            else if (data < pRoot->_data) {
                insert(pRoot->_pLeft, data);
            }
            else if (data > pRoot->_data) {
                insert(pRoot->_pRight, data);
            }
        }

        int height(CNode *pRoot) {
            if (pRoot == NULL) {
                return 0;
            }
            int left = height(pRoot->_pLeft);
            int right = height(pRoot->_pRight);
            if (left > right) {
                return left + 1;
            }
            return right + 1;
        }

        int countNode(CNode *pRoot) {
            if (pRoot == NULL) {
                return 0;
            }
            return countNode(pRoot->_pLeft) + countNode(pRoot->_pRight) + 1;
        }

        void LNR(CNode *pRoot) {
            if (pRoot != NULL) {
                LNR(pRoot->_pLeft);
                cout << pRoot->_data << " ";
                LNR(pRoot->_pRight);
            }
        }

        void NLR(CNode *pRoot) {
            if (pRoot != NULL) {
                cout << pRoot->_data << " ";
                NLR(pRoot->_pLeft);
                NLR(pRoot->_pRight);
            }
        }

        void LRN(CNode *pRoot) {
            if (pRoot != NULL) {
                LRN(pRoot->_pLeft);
                LRN(pRoot->_pRight);
                cout << pRoot->_data << " ";
            }
        }

        CNode* search(CNode *pRoot, int x) {
            if (pRoot != NULL) {
                if (pRoot->_data == x) {
                    return pRoot;
                }
                else if (pRoot->_data > x) {
                    return search(pRoot->_pLeft, x);
                }
                else {
                    return search(pRoot->_pRight, x);
                }
            }
            return NULL;
        }

        bool isBST(CNode *pRoot) {
            if (pRoot == NULL) {
                return true;
            }
            if (pRoot->_pLeft != NULL && pRoot->_pLeft->_data > pRoot->_data) {
                return false;
            }
            if (pRoot->_pRight != NULL && pRoot->_pRight->_data < pRoot->_data) {
                return false;
            }
            if (!isBST(pRoot->_pLeft) || !isBST(pRoot->_pRight)) {
                return false;
            }
            return true;
        }

        void BFS(CNode *pRoot) {
            vector<CNode*> queue;
            CNode *temp = pRoot;
            queue.push_back(temp);

            while (!queue.empty()) {
                temp = queue[0];
                queue.erase(queue.begin());
                if (temp->_pLeft != NULL) {
                    queue.push_back(temp->_pLeft);
                }
                if (temp->_pRight != NULL) {
                    queue.push_back(temp->_pRight);
                }
                cout << temp->_data << " ";
            }
        }

        CNode *_pRoot;
};

int main(int argc, char const *argv[]) {
    CTree *tree = new CTree;

    tree->insert(5);
    tree->insert(3);
    tree->insert(7);
    tree->insert(2);
    tree->insert(8);
    tree->insert(6);
    tree->insert(4);

    tree->LRN();

    // if (tree->isValidBST()) {
    //     cout << "dung cmnr\n";
    // }
    // else {
    //     cout << "fuck\n";
    // }

    // if (tree->isBalanced()) {
    //     cout << "balanced\n";
    // }
    // else {
    //     cout << "meos balance\n";
    // }

    // vector<CList<CNode*> > listOfList = tree->createVectorList();
    // for (int i = 0; i < listOfList.size(); i++) {
    //     listOfList[i].printList();
    //     cout << endl;
    // }

    // tree->LNR();
    // cout << endl;

    // tree->remove(1);

    // tree->LNR();

    // tree->BFS();

    // int a[] = {1,2,3,4,5,6,7,8,9};
    // *tree = tree->createBSTfromSortedArr(a, 0, 8);
    // tree->BFS();

    return 0;
}