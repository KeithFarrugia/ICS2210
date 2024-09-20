#include "RedBlack.h"

/** =========================================================================================================
 *         Left Rotate
 *     y                x
 *    ╱ ╲              ╱ ╲
 *   A   x    ==>     y   C
 *      ╱ ╲          ╱ ╲
 *     z   C        A   z
 * ========================================================================================================== 
 */
void RedBlackTree::rotateLeft(RedBlackTree::node_t* y) {
    
    RedBlackTree::node_t* x = y->right;
    RedBlackTree::node_t* z = x->left;
    
    // ---------------------------------- Make right child of y the left child of x
    y->right = z;
    
    // ---------------------------------- Parent of z => y (if it exists)
    if (z != nullptr){
        z->parent = y;
    }

    
    // ---------------------------------- Parent of x = Parent of y
    x->parent = y->parent;
    
    // ---------------------------------- Update the root of the entire tree (Meaning whatever was the parent of y)
    
    if (y->parent == nullptr){        // ---------------------- This means y was the root so x is the new root
        this->rootNode = x;
    
    }else if (y == y->parent->left){  // ---------------------- If y was the left child of its parent then x is the new left child of that parent
        y->parent->left = x;

    }else if (y == y->parent->right){ // ---------------------- If y was the right child of its parent then x is the new right child of that parent
        y->parent->right = x;
    }
    
    // ---------------------------------- x's NEW left child is y
    x->left = y;
    y->parent = x;
}


/** =========================================================================================================
 *         Right Rotate
 *       y                x
 *      ╱ ╲              ╱ ╲
 *     x   C    ==>     A   y
 *    ╱ ╲                  ╱ ╲
 *   A   z                z   C
 * ========================================================================================================== 
 */
void RedBlackTree::rotateRight(RedBlackTree::node_t* y) {

    RedBlackTree::node_t* x = y->left;
    RedBlackTree::node_t* z = x->right;
    
    y->left = z;
    
    if (z != nullptr){
        z->parent = y;
    }

    // ---------------------------------- Parent of x = Parent of y
    x->parent = y->parent;
    
    // ---------------------------------- Update the root of the entire tree (Meaning whatever was the parent of y)

    if (y->parent == nullptr){        // ---------------------- This means y was the root so x is the new root
        this->rootNode = x;
    
    }else if (y == y->parent->left){  // ---------------------- If y was the left child of its parent then x is the new left child of that parent
        y->parent->left = x;

    }else if (y == y->parent->right){ // ---------------------- If y was the right child of its parent then x is the new right child of that parent{
        y->parent->right = x;
    }

    // ---------------------------------- x's NEW right child is y
    x->right = y;
    y->parent = x;
}