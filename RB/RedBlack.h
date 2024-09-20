#ifndef RED_BLACK_H
#define RED_BLACK_H
#include <algorithm>
#include <iostream>
#include <queue>
#include <cmath>
#include <climits>
#include <iomanip>


class RedBlackTree {
private:
    typedef enum colour_t { 
        Red,
        Black
    }colour_t;

    typedef struct node_t {
        int value;
        RedBlackTree::colour_t colour;
        node_t *left, *right, *parent;

        node_t(int data) : value(data), parent(nullptr), left(nullptr), right(nullptr), colour(RedBlackTree::Red) {}
    }node_t;

public:

    RedBlackTree();

    void insert(int data);

    void inOrderTraversal();
    void printTree();
    int getNumLeaves();
    int getHeight();
    void clearStatistics();
    void calculateStatistics();
    
private:
    RedBlackTree::node_t* rootNode;

    // ------------------------- Rotate Function
    void rotateLeft     (RedBlackTree::node_t* y);
    void rotateRight    (RedBlackTree::node_t* y);

    // ------------------------- Util Functions
    RedBlackTree::colour_t getNodeColour    (const RedBlackTree::node_t* node);
    void swapNodeColours                    (RedBlackTree::node_t*& node1, RedBlackTree::node_t*& node2);
    
    // ------------------------- Insert Function
    void insertUtil (RedBlackTree::node_t*& root, RedBlackTree::node_t* newNode);

    // ------------------------- Conflict Functions
    void fixRedRedConflict  (RedBlackTree::node_t* node);
    void fixTwoRedChildNodes(RedBlackTree::node_t*& GrandParent);

    //------------------------- Get Tree Hight
    int getHeightUtil(node_t* node) ;
    //------------------------- Get Number of Leaves
    int getNumLeavesUtil(node_t* node);

    // ------------------------- Print Functions
    void printTreeUtil          (const std::string& prefix, const RedBlackTree::node_t* node, bool isRight);
    void inOrderTraversalUtil   (RedBlackTree::node_t* node) ;


     // ------------------------- Statistics
    void updateStatistics();
    // -------------- Steps
    int temporarySteps;
    std::vector<int> stepsRecord;
    // -------------- Rotations
    int temporaryRotations;
    std::vector<int> rotationsRecord;
};
#endif