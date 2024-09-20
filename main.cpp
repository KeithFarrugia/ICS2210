#include <iostream>
#include <iomanip>
#include "AVL/Avl.h"
#include "RB/RedBlack.h"
#include "SkipLists/SkipList.h"

void swap(int* array, int index_1, int index_2){
    int temp = array[index_1];
    array[index_1] = array[index_2];
    array[index_2] = temp;
}


void knuthShuffle(int* array, int size) {
    for (int i = size - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        swap(array, i, j);        
    }
}

void printArray(int* array, int size){
    std::cout << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << std::setw(5) <<std::right << array[i] << " ";
        if((i+1) %20 == 0){std::cout << std::endl;}
    }
    std::cout << std::endl;
}
// ============================================================== Main Function ==========================================
int main(int, char**){
    std::srand(std::time(0));
    
    AVLTree avl;
    RedBlackTree rb;
    SkipList sl(30);
    
    // ------------------------------------------- Array of 5000 in the range 1-5000 
    const int knutharraySize = 5000;
    int knuthArray[knutharraySize];
    for (int i = 0; i < knutharraySize; ++i) {
        knuthArray[i] = i + 1;
    }
    knuthShuffle(knuthArray, knutharraySize);

    for (int i = 0; i < knutharraySize; ++i) {
        avl.insert(knuthArray[i]);
        rb.insert(knuthArray[i]);
        sl.insert(knuthArray[i]);
    }
    // ------------------------------------------ Statistics after 5000 inserts
    printf("\n\n -------------------------------- 5000 Inserts \n\n\n");
    avl.calculateStatistics();
    rb.calculateStatistics();
    sl.calculateStatistics();
    
    avl.clearStatistics();
    rb.clearStatistics();
    sl.clearStatistics();
    
    printf("\n\n -------------------------------- CLEAR \n\n\n");
    avl.calculateStatistics();
    rb.calculateStatistics();
    sl.calculateStatistics();

    // ------------------------------------------ Statistics after 1000 inserts
    printf("\n\n -------------------------------- 1000 Inserts \n\n\n");
    const int arraySize = 1000;
    int randomNumbers[arraySize];

    for (int i = 0; i < arraySize; ++i) {
        randomNumbers[i] = std::rand() % 100001;
        avl.insert(randomNumbers[i]);
        rb.insert(randomNumbers[i]);
        sl.insert(randomNumbers[i]);
    }

    avl.calculateStatistics();
    rb.calculateStatistics();
    sl.calculateStatistics();
    return 0;
}
