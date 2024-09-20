#include "Avl.h"


/** ======================================================================
 * -------------------- Utility Functions 
 * Constructor 
 * Calculate Node Height
 * Get the Balance of a node
 * =======================================================================
 */
AVLTree::AVLTree(){
    rootNode = nullptr;
    temporarySteps = 0; temporaryRotations = 0;
}

int AVLTree::getNodeHeight(AVLTree::node_t* node){
    if(node != nullptr){return node->height;}
    return 0;
}
int AVLTree::getBalance(AVLTree::node_t* node) {
    if (node == nullptr) return 0;
    return getNodeHeight(node->left) - getNodeHeight(node->right);
}

/** ======================================================================
 * -------------------- Insertion 
 * Inserts a value in the tree making sure to rotate as needed
 * =======================================================================
 */

// ------------------------ External Interface Function
void AVLTree::insert(int value){
    rootNode = insertUtil(rootNode, value);
    updateStatistics();
}

// ------------------------ Internal Function Varient
AVLTree::node_t* AVLTree::insertUtil(AVLTree::node_t* node, int value){
    // -------------------------------- Update number of Steps
    temporarySteps++;

    // -------------------------------- Base Case : Reached the end of a tree (meaning this is a leaf node)
    if (node == nullptr){ return new node_t(value);}  
  
    // -------------------------------- Recursive Case : Traverse the tree (Recursive call)
    if (value < node->value){
        node->left = insertUtil(node->left, value);  
    }else if (value > node->value){
        node->right = insertUtil(node->right, value);
    }else{
        return node;
    }
    
    // =========================================== After Recursion during the reverse traversal
    // Update and rebalance the tree

    // Updated Height   =      MAX     (Height of Left SubTree    ,  Height of Right SubTree)        +  Current Node
    node->height        = std::max     (getNodeHeight(node->left) ,  getNodeHeight(node->right))     +        1;  
  
    // get Balance for checking
    int balance = getBalance(node);  
  
    // -------------------------------- If Unbalanced -----------------
      
    // -------------------------------- Left Left Case  
    if (balance > 1 && value < node->left->value){ 
        temporaryRotations++;
        return rightRotate(node);  
        
    // -------------------------------- Right Right Case  
    }else if (balance < -1 && value > node->right->value){
        temporaryRotations++;
        return leftRotate(node);  
    
    // -------------------------------- Left Right Case
    }else if (balance > 1 && value > node->left->value){  
        temporaryRotations++;
        return leftRightRotate(node);
        
        
    // -------------------------------- Right Left Case  
    } else if (balance < -1 && value < node->right->value){  
        temporaryRotations++;
        return rightLeftRotate(node);
    }  
  
    /* return the (unchanged) node pointer */
    return node;  
}  

/** ======================================================================
 * -------------------- Get the Height
 * Gets the Height of the AVL tree
 * =======================================================================
 */

int AVLTree::getHeight() {
    return rootNode->height;
}

/** ======================================================================
 * -------------------- Get number of leaves
 * Returns the Number of leaves in an AVL Tree
 * =======================================================================
 */

int AVLTree::getNumLeaves() {
    return getNumLeavesUtil(rootNode);
}

int AVLTree::getNumLeavesUtil(node_t* node) {
    if (node == nullptr)
        return 0;
    
    if (node->left == nullptr && node->right == nullptr)
        return 1;
    
    return getNumLeavesUtil(node->left) + getNumLeavesUtil(node->right);
}

/** ======================================================================
 * -------------------- Inorder Traversal Function
 * Displays the Tre By performing an Inorder Traversal
 * =======================================================================
 */

// ------------------------------------ Main Inorder Traversal Function
void AVLTree::inOrderTraversal() {
    inOrderTraversalUtil(this->rootNode);
    std::cout << std::endl;
}

// ------------------------------------ Internal Inorder Traversal used by the interface accesible Inorder Traversal
void AVLTree::inOrderTraversalUtil(AVLTree::node_t* node) {
    if (node == nullptr){return;}
    
    inOrderTraversalUtil(node->left);
    std::cout << node->value << " ";
    inOrderTraversalUtil(node->right);
}

/** ======================================================================
 * -------------------- Print Tree In a Horizontal Tree Form
 * Prints the tree using branches and other symbols
 * =======================================================================
 */

// ------------------------ External Interface Function
void AVLTree::printTree(){
    if (rootNode == nullptr) {
        std::cout << "Tree is empty." << std::endl;
        return;
    }
    std::cout << rootNode->value << std::endl;
    printTreeUtil("", rootNode->right, true);
    printTreeUtil("", rootNode->left , false);
}

// ------------------------ Internal Function Varient
void AVLTree::printTreeUtil(const std::string& prefix, const AVLTree::node_t* node, bool isRight){
    if (node != nullptr) {
        std::cout << prefix;
        std::cout << (isRight ? "├──" : "└──");
        std::cout << node->value << std::endl;

        // Enter the next tree level - left and right branch
        printTreeUtil(prefix + (isRight ? "│   " : "    "), node->right, true);
        printTreeUtil(prefix + (isRight ? "│   " : "    "), node->left, false);
    }
}


