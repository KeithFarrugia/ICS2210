#ifndef SKIP_LIST_H
#define SKIP_LIST_H
#include <algorithm>
#include <iostream>
#include <queue>
#include <cmath>
#include <climits>
#include <iomanip>
#include <string.h>

class SkipList {
private:
	typedef struct node_t {
		int value;
		node_t** jumpTo;
		node_t(int k, int level) : value(k) {
			jumpTo = new node_t*[level];
			memset(jumpTo, 0, sizeof(node_t*) * (level));
		}
	}node_t;

    typedef enum coin_t{
        Heads, Tails
    }coin_t;


public:
    SkipList(int MAX_LEVEL);

    int generateLevel();
    void insert(int value);
    void printList();
    void clearStatistics();
    void calculateStatistics();
    
private:
    const int MAX_LEVEL;
    int highest_current_level;

    SkipList::node_t* start_node;
    
    // -------------------------  Insertion Functions
    SkipList::node_t* searchInsert(int value, node_t** update);
    SkipList::coin_t flipCoin();
    void create_And_insert(int value, int level, SkipList::node_t** update);

    // ------------------------- Statistics
    void updateStatistics();
    // -------------- Steps
    int temporarySteps;
    std::vector<int> stepsRecord;
    // -------------- Rotations
    int temporaryPromotions;
    std::vector<int> promotionRecord;

};

#endif // SKIP_LIST_H