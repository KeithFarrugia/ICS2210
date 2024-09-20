#include "RedBlack.h"

void RedBlackTree::updateStatistics(){    
    stepsRecord.push_back(temporarySteps);
    rotationsRecord.push_back(temporaryRotations);

    temporarySteps = 0;
    temporaryRotations = 0;
}

void RedBlackTree::clearStatistics(){
    temporarySteps = 0;
    temporaryRotations = 0;
    stepsRecord.clear();
    rotationsRecord.clear();
}

void RedBlackTree::calculateStatistics() {
    std::cout << std::left << std::setw(25) << "==================== RedBlack Statistics ====================\n";

    // --------------------------- Validation
    if (stepsRecord.empty() || rotationsRecord.empty()){std::cout << "No insertions where made\n";return;}

    // --------------------------- Variables for Steps Statistics
    int minSteps = INT_MAX, maxSteps = INT_MIN;
    double meanSteps = 0.0, stdDevSteps = 0.0;
    int medianSteps;

    // --------------------------- Variables for Rotation Statistics
    int minRotations = INT_MAX, maxRotations = INT_MIN;
    double meanRotations = 0.0, stdDevRotations = 0.0;
    int medianRotations;


    // ================================================================ Steps Statistics

    // --------------- Max and Min
    for (int step : stepsRecord) {
        meanSteps += step;
        if (step < minSteps){ minSteps = step;}
        if (step > maxSteps){ maxSteps = step;}
    }

    // --------------- Mean
    meanSteps /= stepsRecord.size();

    // --------------- Standard Derivation
    for (int step : stepsRecord) {  stdDevSteps += (step - meanSteps) * (step - meanSteps);  }
    stdDevSteps = std::sqrt(stdDevSteps / stepsRecord.size());

    // --------------- Median Steps    
    std::sort(stepsRecord.begin(), stepsRecord.end());
    if (stepsRecord.size() % 2 == 0){
        medianSteps = (stepsRecord[stepsRecord.size() / 2 - 1] + stepsRecord[stepsRecord.size() / 2]) / 2;
    }else{
        medianSteps = stepsRecord[stepsRecord.size() / 2];
    }


    // ================================================================ Rotation Statistics

    // --------------- Max and Min
    for (int rotation : rotationsRecord) {
        meanRotations += rotation;
        if (rotation < minRotations){ minRotations = rotation;}
        if (rotation > maxRotations){ maxRotations = rotation;}
    }
    // --------------- Mean
    meanRotations /= rotationsRecord.size();

    // --------------- Standard Derivation
    for (int rotation : rotationsRecord) { stdDevRotations += (rotation - meanRotations) * (rotation - meanRotations); }
    stdDevRotations = std::sqrt(stdDevRotations / rotationsRecord.size());

    // --------------- Median Steps    
    std::sort(rotationsRecord.begin(), rotationsRecord.end());
    if (rotationsRecord.size() % 2 == 0){
        medianRotations = (rotationsRecord[rotationsRecord.size() / 2 - 1] + rotationsRecord[rotationsRecord.size() / 2]) / 2;
    }else{
        medianRotations = rotationsRecord[rotationsRecord.size() / 2];
    }

    // ================================================================ Other Statistics
    int treeHeight = getHeight();
    int numLeaves = getNumLeaves();

    // ================================================================ Printing
    std::cout << std::setw(8) << std::left << "HEIGHT: " << treeHeight  << std::endl;    
    std::cout << std::setw(8) << std::left << "LEAVES: " << numLeaves   << std::endl;

    std::cout << std::left  << std::setw(8) << "Steps Statistics:\n";
    std::cout << "MIN: "    << std::setw(8) << std::left << minSteps;
    std::cout << "MAX: "    << std::setw(8) << std::left << maxSteps;
    std::cout << "MEAN: "   << std::setw(8) << std::left << std::fixed << std::setprecision(3) << meanSteps ;
    std::cout << "STD: "    << std::setw(8) << std::left << std::fixed << std::setprecision(3) << stdDevSteps;
    std::cout << "MED: "    << std::setw(8) << std::left << std::fixed << std::setprecision(3) << medianSteps;
    std::cout <<"\n";

    std::cout << std::setw(8) << std::left << "Rotations Statistics:\n";
    std::cout  << "MIN: "   << std::setw(8) << std::left << minRotations;
    std::cout  << "MAX: "   << std::setw(8) << std::left << maxRotations;
    std::cout  << "MEAN: "  << std::setw(8) << std::left << std::fixed << std::setprecision(3) << meanRotations;
    std::cout  << "STD: "   << std::setw(8) << std::left << std::fixed << std::setprecision(3) << stdDevRotations;
    std::cout  << "MED: "   << std::setw(8) << std::left << std::fixed << std::setprecision(3) << medianRotations;
    std::cout <<"\n";

}