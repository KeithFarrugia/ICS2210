#include "Avl.h"


/** =========================================================================================================
 *         Right Rotate
 *       y                x
 *      ╱ ╲              ╱ ╲
 *     x   C    ==>     A   y
 *    ╱ ╲                  ╱ ╲
 *   A   z                z   C
 * ========================================================================================================== 
 */
AVLTree::node_t* AVLTree::rightRotate(AVLTree::node_t *y){  
    AVLTree::node_t *x = y->left;  
    AVLTree::node_t *z = x->right;  
  
    // Perform rotation  
    x->right = y;  y->left = z;  
  
    // Updated Heights  =      MAX     (Height of Left SubTree   ,  Height of Right SubTree)        +  Current Node
    y->height           =      std::max(getNodeHeight(y->left)   ,  getNodeHeight(y->right))        +       1;  
    x->height           =      std::max(getNodeHeight(x->left)   ,  getNodeHeight(x->right))        +       1;  
  
    // Return new root  
    return x;  
}  

/** =========================================================================================================
 *         Left Rotate
 *     y                x
 *    ╱ ╲              ╱ ╲
 *   A   x    ==>     y   C
 *      ╱ ╲          ╱ ╲
 *     z   C        A   z
 * ========================================================================================================== 
 */
AVLTree::node_t* AVLTree::leftRotate(AVLTree::node_t *y){  
    AVLTree::node_t *x = y->right;  
    AVLTree::node_t *z = x->left;  
  
    // Perform rotation  
    x->left = y;  
    y->right = z;  
  
    // Updated Heights  =      MAX     (Height of Left SubTree   ,  Height of Right SubTree)        +  Current Node
    y->height           =      std::max(getNodeHeight(y->left)   ,  getNodeHeight(y->right))        +       1;  
    x->height           =      std::max(getNodeHeight(x->left)   ,  getNodeHeight(x->right))        +       1;    
  
    // Return new root  
    return x;  
}  

/** =========================================================================================================
 *             Left                 Right                Rotate
 *     y                    y                    z
 *    ╱ ╲                  ╱ ╲                  ╱ ╲
 *   x   C      ==>       z   C      ==>       x   y
 *  ╱ ╲                  ╱ ╲                  ╱ ╲ ╱ ╲
 * A   z                x   D                A  B C  D
 *    ╱ ╲              ╱ ╲
 *   B   D            A   B
 * ========================================================================================================== 
 */

AVLTree::node_t* AVLTree::leftRightRotate(AVLTree::node_t* y) {
    y->left = leftRotate(y->left);   // Perform left rotation on y's left child
    return rightRotate(y);           // Perform right rotation on y
}

/** =========================================================================================================
 *            Right                Left                 Rotate
 *    y                    y                    z
 *   ╱ ╲                  ╱ ╲                  ╱ ╲
 *  A   x      ==>       A   z      ==>       x   y
 *     ╱ ╲                  ╱ ╲              ╱ ╲ ╱ ╲
 *    z   C                B   y            A  B C  D
 *   ╱ ╲                      ╱ ╲
 *  B   D                    C   D
 * ========================================================================================================== 
 */
AVLTree::node_t* AVLTree::rightLeftRotate(AVLTree::node_t* y) {
    y->right = rightRotate(y->right);  // Perform right rotation on y's right child
    return leftRotate(y);              // Perform left rotation on y
}