#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<vector>

using namespace std;

class AVLNode {
    private:
    AVLNode* leftChild;
    int data; int height;
    AVLNode* rightChild;


    public:
    AVLNode(int data) {
        this->data = data;
        this->height = 1; // Lets say the height of a single node is 1 and of a null node is 0 
        this->leftChild = this->rightChild = NULL;
    }
    bool isLeafNode();
    bool hasOneChild();
    bool hasTwoChildren();

    friend class AVLTree; // because to let the methods of AVLTree access the private members
};

class AVLTree {
    private:
    AVLNode* rootNode = NULL;

    void inOrderTraversal(AVLNode* node);
    void preOrderTraversal(AVLNode* node);
    void postOrderTraversal(AVLNode* node);
    void levelOrderTraversal(AVLNode* node);
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    AVLNode* LLRotate(AVLNode* node);
    AVLNode* LRRotate(AVLNode* node);
    AVLNode* RLRotate(AVLNode* node);
    AVLNode* RRRotate(AVLNode* node);
    AVLNode* rcrInsert(AVLNode* node, int data);
    AVLNode* rotateIfNecessary(AVLNode* node);
    AVLNode* deleteNode(AVLNode* node, int target);

    public:
    void inOrderTraversal() { inOrderTraversal(this->rootNode); }
    void preOrderTraversal() { preOrderTraversal(this->rootNode); }
    void postOrderTraversal() { postOrderTraversal(this->rootNode); }
    void levelOrderTraversal() { levelOrderTraversal(this->rootNode); }
    void insert(int data) { this->rootNode = rcrInsert(this->rootNode, data); }
    void deleteNode(int target) { this->rootNode = deleteNode(this->rootNode, target); }
    int height() { return height(rootNode); }
};

int main(void) {
    AVLTree t1;
    printf("An AVL Tree is ready to Use\n");
    printf("README\n");
    printf("==================================================\n");
    printf("The height of a single Node is considered as 1 and that of a null node is 0\n");
    printf("This tree has data of integer type \nIf different type is needed, you may change it in the source code\n");
    printf("The Balance Factor of a leaf node and a null node is 0\n");
    printf("==================================================\n");


    int element;
    int choice;
    while (true) {
        printf("1. Insert(data)\n");
        printf("2. Delete(target)\n");
        printf("3. Height(data)\n");
        printf("4. PreOrderTraversal\n");
        printf("5. PostOrderTraversal\n");
        printf("6. InOrderTraversal\n");
        printf("7. LevelOrderTraversal\n");
        printf("8. Exit\n");

        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        printf("======================================\n");
        switch (choice) {
            case 1:
                scanf("%d", &element);
                printf("Adding %d to Tree\n", element);
                t1.insert(element);
                break;
            case 2:
                scanf("%d", &element);
                printf("Deleting %d from Tree\n", element);
                t1.deleteNode(element);
                break;
            case 3:
                printf("Current Height: %d\n", t1.height());
                break;
            case 4:
                t1.preOrderTraversal();
                putchar('\n');
                break;
            case 5:
                t1.postOrderTraversal();
                putchar('\n');
                break;
            case 6:
                t1.inOrderTraversal();
                putchar('\n');
                break;
            case 7:
                t1.levelOrderTraversal();
                putchar('\n');
                break;
            case 8:
                printf("Press ctrl+c to Exit :) ");
                break;

            default:
                printf("Invalid Choice\n");
                break;
        }
        printf("======================================\n\n");

    }

    return 0;
};

bool AVLNode::isLeafNode() {
    if (this->leftChild == NULL && this->rightChild == NULL) {
        return true;
    } else return false;
};
bool AVLNode::hasOneChild() {
    if (this->leftChild == NULL ^ this->rightChild == NULL) {
        return true;
    } else return false;
};
bool AVLNode::hasTwoChildren() {
    if (this->leftChild != NULL && this->rightChild != NULL) {
        return true;
    } else return false;
}


AVLNode* AVLTree::rcrInsert(AVLNode* node, int data) {
    if (node == NULL) {
        AVLNode* newNode = new AVLNode(data);
        return newNode;
    } else {
        if (data > node->data) {
            node->rightChild = rcrInsert(node->rightChild, data);
        } else if (data < node->data) {
            node->leftChild = rcrInsert(node->leftChild, data);
        }
        node->height = height(node);

        return rotateIfNecessary(node);
    }
};

int AVLTree::height(AVLNode* node) {
    if (node == NULL) return 0;
    else {
        int leftHeight = (node->leftChild) ? node->leftChild->height : 0;
        int rightHeight = (node->rightChild) ? node->rightChild->height : 0;

        return ((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1;
    }
};

int AVLTree::balanceFactor(AVLNode* node) {
    if (node == NULL) return 0;
    else return (height(node->leftChild) - height(node->rightChild));
};

AVLNode* AVLTree::rotateIfNecessary(AVLNode* node) {
    // if node is balanced just return it
    if (abs(balanceFactor(node)) <= 1) return node;
    else {
        // decide what kind of rotation is necessary
        if (balanceFactor(node) == 2 && balanceFactor(node->leftChild) == 1) {
            return LLRotate(node);
        } else if (balanceFactor(node) == 2 && balanceFactor(node->leftChild) == -1) {
            return LRRotate(node);
        } else if (balanceFactor(node) == -2 && balanceFactor(node->rightChild) == -1) {
            return RRRotate(node);
        } else if (balanceFactor(node) == -2 && balanceFactor(node->rightChild) == 1) {
            return RLRotate(node);
        } else {
            printf("Something is not balanced and its quiet not right");
            return node;
        }
    }
};

void AVLTree::inOrderTraversal(AVLNode* node) {
    if (node == NULL) return;
    else {
        inOrderTraversal(node->leftChild);
        printf("%d ", node->data);
        inOrderTraversal(node->rightChild);
    }
}
void AVLTree::preOrderTraversal(AVLNode* node) {
    if (node == NULL) return;
    else {
        printf("%d ", node->data);
        preOrderTraversal(node->leftChild);
        preOrderTraversal(node->rightChild);
    }
}
void AVLTree::postOrderTraversal(AVLNode* node) {
    if (node == NULL) return;
    else {
        postOrderTraversal(node->leftChild);
        postOrderTraversal(node->rightChild);
        printf("%d ", node->data);
    }
}
void AVLTree::levelOrderTraversal(AVLNode* node) {
    if (node == NULL) return;
    else {
        vector<AVLNode*> treeQueue;
        treeQueue.push_back(node);

        while (!(treeQueue.empty())) {
            AVLNode* tempCursor = treeQueue.front();
            treeQueue.erase(treeQueue.begin());

            if (tempCursor != NULL) {
                printf("%d ", tempCursor->data);
                treeQueue.push_back(tempCursor->leftChild);
                treeQueue.push_back(tempCursor->rightChild);
            } else continue;
        }
    }
}

AVLNode* AVLTree::LLRotate(AVLNode* node) {
    AVLNode* nodeCopy = node; // final rightChild
    AVLNode* nodeLCopy = node->leftChild; // final centerNode
    AVLNode* nodeLLCopy = node->leftChild->leftChild; // final leftChild, un-altered

    nodeCopy->leftChild = nodeLCopy->rightChild;
    nodeLCopy->rightChild = nodeCopy;

    nodeCopy->height = height(nodeCopy); // height must be calculated
    nodeLCopy->height = height(nodeCopy); // in this order only

    return nodeLCopy;
}
AVLNode* AVLTree::LRRotate(AVLNode* node) {
    AVLNode* nodeCopy = node; // final rightChild
    AVLNode* nodeLCopy = node->leftChild; // final leftChild
    AVLNode* nodeLRCopy = node->leftChild->rightChild; // final centerNode

    nodeLCopy->rightChild = nodeLRCopy->leftChild;
    nodeCopy->leftChild = nodeLRCopy->rightChild;

    nodeLRCopy->rightChild = nodeCopy;
    nodeLRCopy->leftChild = nodeLCopy;

    nodeLCopy->height = height(nodeLCopy); // height must be calculated
    nodeCopy->height = height(nodeCopy); // in this order only
    nodeLRCopy->height = height(nodeLRCopy);

    return nodeLRCopy;
}
AVLNode* AVLTree::RRRotate(AVLNode* node) {
    AVLNode* nodeCopy = node; // final leftChild
    AVLNode* nodeRCopy = node->rightChild; // final centerNode
    AVLNode* nodeRRCopy = node->rightChild->rightChild; // final RightChild, un-altered

    nodeCopy->rightChild = nodeRCopy->leftChild;
    nodeRCopy->leftChild = nodeCopy;

    nodeCopy->height = height(nodeCopy); // height must be calculated
    nodeRCopy->height = height(nodeRCopy); // in this order only

    return nodeRCopy;
}
AVLNode* AVLTree::RLRotate(AVLNode* node) {
    AVLNode* nodeCopy = node; // final leftChild
    AVLNode* nodeRCopy = node->rightChild; // final rightChild
    AVLNode* nodeRLCopy = node->rightChild->leftChild; // final centerNode

    nodeCopy->rightChild = nodeRLCopy->leftChild;
    nodeRCopy->leftChild = nodeRLCopy->rightChild;

    nodeRLCopy->rightChild = nodeRCopy;
    nodeRLCopy->leftChild = nodeCopy;

    nodeRCopy->height = height(nodeRCopy); // height must be calculated
    nodeCopy->height = height(nodeCopy); // in this order only
    nodeRLCopy->height = height(nodeRLCopy);

    return nodeRLCopy;
}

AVLNode* AVLTree::deleteNode(AVLNode* node, int target) {
    if (node != NULL) {
        if (target > node->data) {
            node->rightChild = deleteNode(node->rightChild, target);
        } else if (target < node->data) {
            node->leftChild = deleteNode(node->leftChild, target);
        } else if (target == node->data) {
            if (node->isLeafNode()) {
                delete node; // clearing the memory of the targetNode
                node = NULL;
            } else if (node->hasOneChild()) {
                AVLNode* descendant;
                if (node->leftChild != NULL) {
                    descendant = node->leftChild;
                } else {
                    descendant = node->rightChild;
                }
                delete node;
                node = descendant;
            } else if (node->hasTwoChildren()) {
                // Here we look for the inorder-Predecessor and make it take node's place
                AVLNode* cursor = node->leftChild;
                AVLNode* tail = node;
                while (cursor->rightChild != NULL) {
                    tail = cursor;
                    cursor = cursor->rightChild;
                }
                int predecessor = cursor->data; // copying the data befor deletion
                // Here the predecessor will have max of one child so deleting it won't cause any complications
                if (cursor == tail->leftChild) {
                    tail->leftChild = deleteNode(tail->leftChild, cursor->data);
                } else {
                    tail->rightChild = deleteNode(tail->rightChild, cursor->data);
                }

                AVLNode* newNode = new AVLNode(predecessor);
                // Here we are reconnecting the left and rightChild to the predecessor
                newNode->leftChild = node->leftChild;
                newNode->rightChild = node->rightChild;

                node = newNode;
            }
        }
    } else {
        printf("Given element is not in Tree\n");
    }
    // finally after all calculations and case handlings we return the node
    return rotateIfNecessary(node);
}

