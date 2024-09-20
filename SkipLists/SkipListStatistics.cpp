#include "SkipList.h"

void SkipList::updateStatistics(){
    stepsRecord.push_back(temporarySteps);
    promotionRecord.push_back(temporaryPromotions);

    temporarySteps = 0;
    temporaryPromotions = 0;
}

void SkipList::clearStatistics(){
    temporarySteps = 0;
    temporaryPromotions = 0;
    stepsRecord.clear();
    promotionRecord.clear();
}

void SkipList::calculateStatistics() {
    std::cout << std::left << std::setw(25) << "==================== SkipList Statistics ====================\n";

    // --------------------------- Validation
    if (stepsRecord.empty() || promotionRecord.empty()){std::cout << "No insertions where made\n";return;}

    // --------------------------- Variables for Steps Statistics
    int minSteps = INT_MAX, maxSteps = INT_MIN;
    double meanSteps = 0.0, stdDevSteps = 0.0;
    int medianSteps;

    // --------------------------- Variables for Promotion Statistics
    int minPromotions = INT_MAX, maxPromotions = INT_MIN;
    double meanPromotions = 0.0, stdDevPromotions = 0.0;
    int medianPromotions;


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


    // ================================================================ Promotion Statistics

    // --------------- Max and Min
    for (int promotion : promotionRecord) {
        meanPromotions += promotion;
        if (promotion < minPromotions){ minPromotions = promotion;}
        if (promotion > maxPromotions){ maxPromotions = promotion;}
    }
    // --------------- Mean
    meanPromotions /= promotionRecord.size();

    // --------------- Standard Derivation
    for (int promotion : promotionRecord) { stdDevPromotions += (promotion - meanPromotions) * (promotion - meanPromotions); }
    stdDevPromotions = std::sqrt(stdDevPromotions / promotionRecord.size());

    // --------------- Median Steps    
    std::sort(promotionRecord.begin(), promotionRecord.end());
    if (promotionRecord.size() % 2 == 0){
        medianPromotions = (promotionRecord[promotionRecord.size() / 2 - 1] + promotionRecord[promotionRecord.size() / 2]) / 2;
    }else{
        medianPromotions = promotionRecord[promotionRecord.size() / 2];
    }

    // ================================================================ Printing
    std::cout << std::setw(8) << std::left << "LEVELS: " << highest_current_level  << std::endl;

    std::cout << std::left  << std::setw(8) << "Steps Statistics:\n";
    std::cout << "MIN: "    << std::setw(8) << std::left << minSteps;
    std::cout << "MAX: "    << std::setw(8) << std::left << maxSteps;
    std::cout << "MEAN: "   << std::setw(8) << std::left << std::fixed << std::setprecision(3) << meanSteps ;
    std::cout << "STD: "    << std::setw(8) << std::left << std::fixed << std::setprecision(3) << stdDevSteps;
    std::cout << "MED: "    << std::setw(8) << std::left << std::fixed << std::setprecision(3) << medianSteps;
    std::cout <<"\n";

    std::cout << std::setw(8) << std::left << "Promotions Statistics:\n";
    std::cout  << "MIN: "   << std::setw(8) << std::left << minPromotions;
    std::cout  << "MAX: "   << std::setw(8) << std::left << maxPromotions;
    std::cout  << "MEAN: "  << std::setw(8) << std::left << std::fixed << std::setprecision(3) << meanPromotions;
    std::cout  << "STD: "   << std::setw(8) << std::left << std::fixed << std::setprecision(3) << stdDevPromotions;
    std::cout  << "MED: "   << std::setw(8) << std::left << std::fixed << std::setprecision(3) << medianPromotions;
    std::cout <<"\n";

}