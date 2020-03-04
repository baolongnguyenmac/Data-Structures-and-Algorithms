#include "stdio.h"
#include "stdlib.h"

#include "vector"
using namespace std;

struct NODE {
    int data;
    NODE *pLeft;
    NODE *pRight;
};

NODE* getNode(int data) {
    NODE *p = new NODE;
    p->data = data;
    p->pRight = p->pLeft = NULL;
    return p;
}

void insertNode(int data, NODE *&pRoot) {
    if (pRoot == NULL) {
        pRoot = getNode(data);
    }
    else {
        if (data <pRoot->data) {
            insertNode(data, pRoot->pLeft);
        }
        else {
            insertNode(data, pRoot->pRight);
        }
    }
}

void BFS(NODE *pRoot) {
    vector<NODE*> queue;
    queue.push_back(pRoot);

    NODE *temp;
    while (!queue.empty()) {
        temp = queue[0];
        queue.erase(queue.begin());
        printf("%d ", temp->data);
        if (temp->pRight != NULL) {
            queue.push_back(temp->pRight);
        }
        if (temp->pLeft != NULL) {
            queue.push_back(temp->pLeft);
        }
    }
}

void NLR(NODE *proot) {
    if (proot != NULL) {
        printf("%d ", proot->data);
        NLR(proot->pLeft);
        NLR(proot->pRight);
    }
}

void createTree(NODE *&proot, int a[], int left, int right) {
    if (left <= right) {
        int mid = (right + left) / 2;
        proot = getNode(a[mid]);
        createTree(proot->pLeft, a, left, mid - 1);
        createTree(proot->pRight, a, mid + 1, right);
    }
}

int main(int argc, char const *argv[]) {
    NODE *p = NULL;
    int a[] = {1,2,3,4,5,6,7,8,9};
    createTree(p, a, 0, 8);

    // insertNode(5, p);
    // insertNode(7, p);
    // insertNode(3, p);
    // insertNode(2, p);
    // insertNode(4, p);
    // insertNode(6, p);
    // insertNode(8, p);

    BFS(p);
    // NLR(p);
    printf("\n");

    return 0;
}
