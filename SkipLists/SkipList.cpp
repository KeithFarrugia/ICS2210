#include "SkipList.h"
/** ======================================================================
 * -------------------- Constructor
 * =======================================================================
 */

SkipList::SkipList(int MAX_LEVEL): MAX_LEVEL(MAX_LEVEL), highest_current_level(0) {
    start_node = new node_t(INT_MIN, MAX_LEVEL);
    temporarySteps = 0; temporaryPromotions = 0;
}

/** ======================================================================
 * -------------------- Coin Flip
 * flip a coin 50 50 chance
 * returns heads or tails
 * =======================================================================
 */
SkipList::coin_t SkipList::flipCoin() {
    return rand() % 2 == 0 ? Heads : Tails;
}

/** ======================================================================
 * -------------------- generate level
 * Generates the level of the node in orderwords how many
 * down/up steps it has.
 * =======================================================================
 */
int SkipList::generateLevel() {
    SkipList::coin_t coin = SkipList::Heads;
    int generatedLevel = 0;

    // ---------------------- If its Heads and we haven't reached Max Level add a level
    while (coin == SkipList::Heads && generatedLevel < MAX_LEVEL) {
        temporaryPromotions++;
        generatedLevel++;
        coin = flipCoin();
    }

    return generatedLevel;
}
/** ======================================================================
 * -------------------- Search Insert
 * searches the array for the position to place the value
 * =======================================================================
 */
SkipList::node_t* SkipList::searchInsert(int value, SkipList::node_t** update){
    SkipList::node_t* current = start_node;
    
    for (int i = highest_current_level; i >= 0; i--) {
        while (current->jumpTo[i] != nullptr && current->jumpTo[i]->value < value) {
            temporarySteps++;
            current = current->jumpTo[i];
        }
        temporarySteps++;
        update[i] = current;
    }
    
    return current;
}
/** ======================================================================
 * -------------------- Create insert
 * function that creates the node and updates the pointers in 
 * order to insert the node into the list
 * =======================================================================
 */
void SkipList::create_And_insert(int value, int level, SkipList::node_t** update){
    node_t* newNode = new node_t(value, level);

    // -------------------- update the pointers for for the nodes to insert the node
    for (int i = 0; i < level; i++) {
        newNode->jumpTo[i] = update[i]->jumpTo[i];
        update[i]->jumpTo[i] = newNode;
    }
}

/** ======================================================================
 * -------------------- Insert
 * this is the main insert function makes use of the other utility
 * functions mentioned previously
 * =======================================================================
 */
void SkipList::insert(int value) {
    SkipList::node_t* update[MAX_LEVEL + 1];
    SkipList::node_t* current;

    current = searchInsert(value, update)->jumpTo[0];

    // -------------------- Check if value is a duplicate
    if (current == nullptr || current->value != value) {

        // -------------------- Randomly Generate the nodes Level
        int generatedLevel = generateLevel();
        
        // -------------------- If this is now the highest level node we
        // -------------------- need to update both the starting node and the
        // -------------------- highest current Level
        if (generatedLevel > highest_current_level) {
            for (int i = highest_current_level; i < generatedLevel; i++) {
                update[i] = start_node;
            }
            highest_current_level = generatedLevel;
        }

        // -------------------- Insert and update the Linked list
        create_And_insert(value, generatedLevel, update);
    
    // -------------------- Key already in use
    }else{}
    updateStatistics();
}

/** ======================================================================
 * -------------------- Print List
 * Prints the nodes and the levels in the skip list
 * =======================================================================
 */
void SkipList::printList() {
    std::cout << "==================SKIP LIST================== " << std::endl;
    for (int i = highest_current_level - 1; i >= 0; i--) {
        node_t* node = start_node->jumpTo[i];
        std::cout << "Level " << i << ": ";
        while (node != nullptr) {
            std::cout << node->value << " ";
            node = node->jumpTo[i];
        }
        std::cout << std::endl;
    }
}



