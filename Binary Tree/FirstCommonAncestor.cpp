/*
    * tìm node cha chung gần nhất của 2node đầu vào
    * tham khảo từ https://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/
    * tham khảo từ cracking the coding interview
*/

#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

#include "string"
#include "vector"

enum POS {
    LEFT,
    RIGHT
};

struct NODE {
    int data;
    NODE *pParent = NULL;
    NODE *pLeft = NULL;
    NODE *pRight = NULL;
};

NODE* getNode(int data) {
    NODE *p = new NODE;
    p->data = data;
    return p;
}

NODE* findNode(int data, NODE *pRoot) {
    if (pRoot != NULL) {
        if (pRoot->data == data) {
            return pRoot;
        }
        NODE *left = findNode(data, pRoot->pLeft);
        NODE *right = findNode(data, pRoot->pRight);
        if (left != NULL) {
            return left;
        }
        return right;
    }
    return NULL;
}

// chúng ta sẽ thống nhất không add các node có giá trị trùng nhau vào cây
// vì làm nv sẽ khiến hàm findIntersect bị sai :))
bool insert(int data, NODE *&pRoot, POS pos = LEFT, int parent = 0) {
    // cây rỗng
    if (pRoot == NULL) {
        pRoot = getNode(data);
        return true;
    }

    // tìm node parent 
    NODE *pParent = findNode(parent, pRoot);
    if (pParent != NULL) {  // nếu tìm thấy -> ngon 
        if (pos == LEFT && pParent->pLeft == NULL) {
            pParent->pLeft = getNode(data);
            pParent->pLeft->pParent = pParent;
            return true;
        }
        else if (pos == RIGHT && pParent->pRight == NULL) {
            pParent->pRight = getNode(data);
            pParent->pRight->pParent = pParent;
            return true;
        }
    }
    return false;   // không tìm thấy parent hoặc tìm thấy nhưng pos đã là hoa có chủ :) 
}

void BFS(NODE *pRoot) {
    vector<NODE*> queue;
    NODE *temp = pRoot;
    queue.push_back(temp);

    while (!queue.empty()) {
        temp = queue[0];
        queue.erase(queue.begin());
        if (temp->pLeft != NULL) {
            queue.push_back(temp->pLeft);
        }
        if (temp->pRight != NULL) {
            queue.push_back(temp->pRight);
        }
        cout << temp->data << " ";
    }
}

int height(NODE *p) {
    int h = 0;
    while (p != NULL) {
        h++;
        p = p->pParent;
    }
    return h;
}

NODE* findIntersect(int _p, int _q, NODE *pRoot) {
    NODE *p = findNode(_p, pRoot), *q = findNode(_q, pRoot);
    if (p == NULL || q == NULL) {
        return NULL;
    }

    int delta = height(p) - height(q);
    while (delta > 0) {
        p = p->pParent;
        delta--;
    }
    while (delta < 0) {
        q = q->pParent;
        delta++;
    }
    while (p->pParent != NULL) {
        if (p == q) {
            return p;
        }
        p = p->pParent;
        q = q->pParent;
    }
}

int main(int argc, char const *argv[]) {
    NODE *pRoot = NULL;

    insert(1, pRoot);
    insert(2, pRoot, LEFT, 1);
    insert(3, pRoot, RIGHT, 1);
    insert(4, pRoot, LEFT, 2);
    insert(5, pRoot, RIGHT, 2);
    insert(7, pRoot, RIGHT, 3);
    insert(6, pRoot, LEFT, 3);
    insert(9, pRoot, LEFT, 6);

    cout << findIntersect(4, 2, pRoot)->data << endl;

    return 0;
}
