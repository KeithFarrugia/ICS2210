#include "RedBlack.h"


RedBlackTree::RedBlackTree(){
    rootNode = nullptr;
    temporarySteps = 0; temporaryRotations = 0;
}

/** ======================================================================
 * -------------------- Insert Function
 * Inserts a new node to the Tree
 * Keeps a pointer to that node inorder to make sure no Red- Red
 * Conflicts have occured
 * =======================================================================
 */
// ------------------------------------ Main Insert Function (Wrapper)
void RedBlackTree::insert(int value) {
    RedBlackTree::node_t* newNode = new RedBlackTree::node_t(value);
    insertUtil(this->rootNode, newNode);
    fixRedRedConflict(newNode);
    updateStatistics();
}

// ------------------------------------ Internal Insert used by the interface accesible insert
void RedBlackTree::insertUtil(RedBlackTree::node_t*& root, RedBlackTree::node_t* newNode) {
    
    // ------------------------ Update number of steps
    temporarySteps++;

    // ------------------------ Check if Root is Empty
    if (root == nullptr) { root = newNode;  return; }

    if (newNode->value < root->value) {
        insertUtil(root->left, newNode);
        root->left->parent = root;
    } else if (newNode->value > root->value) {
        insertUtil(root->right, newNode);
        root->right->parent = root;
    }
}

/** ======================================================================
 * -------------------- Swap Node Colours
 * Swaps to node's Colours with each other
 * =======================================================================
 */
void RedBlackTree::swapNodeColours(RedBlackTree::node_t*& node1, RedBlackTree::node_t*& node2) {
    // -------------------- Make sure neither Node is null
    if(node1 == nullptr || node2 == nullptr){return;}
    
    RedBlackTree::colour_t temp = getNodeColour(node1);
    node1->colour = getNodeColour(node2);
    node2->colour = temp;
}

RedBlackTree::colour_t RedBlackTree::getNodeColour(const RedBlackTree::node_t* node) {
    return (node == nullptr) ? RedBlackTree::Black : node->colour;
}

/** ======================================================================
 * -------------------- Get the Height
 * Gets the Height of the RED BLACK tree
 * =======================================================================
 */

int RedBlackTree::getHeight() {
    return getHeightUtil(rootNode);
}

int RedBlackTree::getHeightUtil(node_t* node) {
    if (node == nullptr)
        return 0;
    
    int leftHeight = getHeightUtil(node->left);
    int rightHeight = getHeightUtil(node->right);
    
    return std::max(leftHeight, rightHeight) + 1;
}

/** ======================================================================
 * -------------------- Get number of leaves
 * Returns the Number of leaves in an RED BLACK Tree
 * =======================================================================
 */

int RedBlackTree::getNumLeaves() {
    return getNumLeavesUtil(rootNode);
}

int RedBlackTree::getNumLeavesUtil(node_t* node) {
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
void RedBlackTree::inOrderTraversal() {
    inOrderTraversalUtil(this->rootNode);
    std::cout << std::endl;
}

// ------------------------------------ Internal Inorder Traversal used by the interface accesible Inorder Traversal
void RedBlackTree::inOrderTraversalUtil(RedBlackTree::node_t* node) {
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
void RedBlackTree::printTree(){
    if (rootNode == nullptr) {
        std::cout << "Tree is empty." << std::endl;
        return;
    }
    // ----------------------------- Print Root Node
    std::cout   << (getNodeColour(rootNode) == RedBlackTree::Black ? "Black" : "Red") 
                << "[" << rootNode->value << "]" << std::endl;
    // ----------------------------- Start Printing Child Nodes
    printTreeUtil("", rootNode->right, true);
    printTreeUtil("", rootNode->left , false);
}

// ------------------------ Internal Function Varient
void RedBlackTree::printTreeUtil(const std::string& prefix, const RedBlackTree::node_t* node, bool isRight){
    if (node != nullptr) {
        std::cout << prefix;
        std::cout << (isRight ? "├──" : "└──");
        std::cout   << (getNodeColour(node) == RedBlackTree::Black ? "Black" : "Red") 
                    << "["<<node->value << "]" <<std::endl;

        // ----------------------------- Enter the next tree level - left and right branch
        printTreeUtil(prefix + (isRight ? "│   " : "    "), node->right, true);
        printTreeUtil(prefix + (isRight ? "│   " : "    "), node->left, false);
    }
}