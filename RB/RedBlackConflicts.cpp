#include "RedBlack.h"
/** ============================================================================================================================================
 *                      Parent(RedBlackTree::Black)                              Parent(RedBlackTree::Red)
 *                          ╱         ╲                              =>                   ╱         ╲
 *      Left(RedBlackTree::Red)     Right(RedBlackTree::Red)             Left(RedBlackTree::Black)  Right(RedBlackTree::Black)
 * =============================================================================================================================================
 */
void RedBlackTree::fixTwoRedChildNodes(RedBlackTree::node_t*& parent){
    RedBlackTree::node_t* leftChild  = parent->left;
    RedBlackTree::node_t* rightChild = parent->right;

    parent->colour = RedBlackTree::Red;
    leftChild->colour = rightChild->colour = RedBlackTree::Black;

    // Make Sure that the parent's new colour has not caused a conflict.
    fixRedRedConflict(parent);
}


/** ============================================================================================================================================
 * Fixes Consecutive RedBlackTree::Red node Issues in the Tree
 * =============================================================================================================================================
 */
void  RedBlackTree::fixRedRedConflict(RedBlackTree::node_t* node) {
    // ========================================================= Base Case

    // ----------------------- If this is the Null => Finished 
    if (node == nullptr) {
        return;
    }   
    // ----------------------- If this is the root => Finished 
    else if (node == rootNode){
        rootNode->colour = RedBlackTree::Black;
        return;
    }   
    // ----------------------- If Current == Black => Finished
    else if(getNodeColour(node) == RedBlackTree::Black){
        return;
    }   
    // ----------------------- If Parent == Black  => Finished
    else if(getNodeColour(node->parent) == RedBlackTree::Black){
        return;
    }

    // ========================================================= Inductive Case
    RedBlackTree::node_t* parent      = node->parent;
    RedBlackTree::node_t* grandparent = parent->parent;

    /** ===================================== Case 1
     * Parent is the left child 
     * of the grand parent
     * 
     *    [Grand Parent] {Red}
     *        ╱             ╲
     *  [Parent]{Red}     [Uncle]
     * ======================================
     */
    if (parent == grandparent->left) {
        RedBlackTree::node_t* uncle = grandparent->right;

        // ---------------------------- Both Parent and Uncle are Red
        if (getNodeColour(uncle) == RedBlackTree::Red) {
            fixTwoRedChildNodes(grandparent);

        // ---------------------------- Uncle is Red
        } else if (getNodeColour(uncle) == RedBlackTree::Black) {
            // ------------------------- Check if there is need for a right rotation (meaning right left rotation needed)
            if (node == parent->right) {  
                rotateLeft(parent);
                node = parent; parent = node->parent;
            }
            rotateRight(grandparent);
            swapNodeColours(parent, grandparent);
            node = parent;
            fixRedRedConflict(node);
            // ------------------------- Update Rotations
            temporaryRotations++;
        }


    /** ===================================== Case 2
     * Parent is the right child 
     * of the grand parent
     * 
     *    [Grand Parent] {Red}
     *        ╱             ╲
     *   [Uncle]        [Parent]{Red}
     * ======================================
     */
    } else {
        RedBlackTree::node_t* uncle = grandparent->left;
        if (getNodeColour(uncle) == RedBlackTree::Red) {
            fixTwoRedChildNodes(grandparent);
        } else {
            // ------------------------- Check if there is need for a left rotation (meaning left right rotation needed)
            if (node == parent->left) {
                rotateRight(parent);
                node = parent; parent = node->parent;
            }
            rotateLeft(grandparent);
            swapNodeColours(parent, grandparent);
            node = parent;
            fixRedRedConflict(node);
            // ------------------------- Update Rotations
            temporaryRotations++;
        }
    }
}


