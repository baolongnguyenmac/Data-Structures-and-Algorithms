#include "BinaryTree.h"
// #include "AVLTree.h"

int main(int argc, char const *argv[]) {
    CNode *myTree = new CNode;

    myTree->addNode(6);
    myTree->addNode(9);
    myTree->addNode(1);
    myTree->addNode(2);
    myTree->addNode(5);
    myTree->addNode(4);

    cout << myTree->search(6)->getData() << endl;
    cout << myTree->height() << endl;
    cout << myTree->countNode() << endl;

    return 0;
}