//
// Created by Cristobal M on 10/5/17.
//

#include "../src/GreeneSplit.h"
#include "../src/LinearSplit.h"

#include <gtest/gtest.h>
#include "../src/RandomRectangleGenerator.h"
#include "../src/IOControl.h"
#include "../src/RTreeController.h"

TEST(RandomGenerationTest, CanRead) {
    SplitHeuristic *heuristic = new LinearSplit();
    std::string input = "canread.txt";
    RandomRectangleGenerator::generateDataFile(30000000, input);
    int rootIndex = IOControl::processInput(input, heuristic);
    RTreeController controller(rootIndex, heuristic);

    delete heuristic;
}
