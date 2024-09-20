#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <algorithm>
#include <iostream>
#include <queue>
#include <cmath>
#include <climits>
#include <iomanip>


class AVLTree{
private:
    typedef struct node_t {
        int value;    
        int height; 
        AVLTree::node_t *left;  
        AVLTree::node_t *right;

        node_t(int val) : value(val), left(nullptr), right(nullptr), height(1) {}
    }node_t;

public:
    AVLTree();

    void insert(int value);

    void inOrderTraversal();
    int getNumLeaves();
    int getHeight();
    void printTree();
    void clearStatistics();
    void calculateStatistics();

private:
    // ------------------------- Utility Functions 
    AVLTree::node_t* rootNode;
    int getNodeHeight(AVLTree::node_t* nodde);
    int getBalance(AVLTree::node_t* node);

    // ------------------------- Rotate Functions
    AVLTree::node_t* rightRotate    (AVLTree::node_t* y);
    AVLTree::node_t* leftRotate     (AVLTree::node_t* y);
    AVLTree::node_t* leftRightRotate(AVLTree::node_t* y);
    AVLTree::node_t* rightLeftRotate(AVLTree::node_t* y);

    // ------------------------- Insert Function
    AVLTree::node_t* insertUtil(AVLTree::node_t* node, int key);

    //------------------------- Get Number of Leaves
    int getNumLeavesUtil(node_t* node);

    // ------------------------- Printing Functions
    void inOrderTraversalUtil(node_t* node);
    void printTreeUtil(const std::string& prefix, const AVLTree::node_t* node, bool isLeft);

    // ------------------------- Statistics
    void updateStatistics();
    // -------------- Steps
    int temporarySteps;
    std::vector<int> stepsRecord;
    // -------------- Rotations
    int temporaryRotations;
    std::vector<int> rotationsRecord;
};
#endif // AVL_TREE_H