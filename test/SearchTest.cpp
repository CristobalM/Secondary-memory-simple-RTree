//
// Created by cristobal on 06-10-17.
//

#include <gtest/gtest.h>
#include "../src/SplitHeuristic.h"
#include "../src/LinearSplit.h"
#include "../src/RTreeController.h"
#include "../src/RandomRectangleGenerator.h"
#include "../src/IOControl.h"

TEST(SearchTest, BiggerIntersectsAll) {
    SplitHeuristic *heuristic = new LinearSplit();
    std::string input = "canread2.txt";
    RandomRectangleGenerator::generateDataFile(114, input);
    RTreeController controller = IOControl::processInput(input, heuristic);




    IOControl::checkCache(controller.getControllerPrefix(), true);

    delete heuristic;
}
