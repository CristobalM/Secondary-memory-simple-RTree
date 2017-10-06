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

    vRect dataMBRS = controller.extractDataMBRS();
    Rectangle query = Rectangle::findMBR(dataMBRS);

    std::vector<int> result = controller.search(query);
    //IOControl::checkCache(controller.getControllerPrefix(), true);
    delete heuristic;
    EXPECT_EQ(result.size(), dataMBRS.size());
}

TEST(SearchTest, OutsideIntersectsNone) {
    SplitHeuristic *heuristic = new LinearSplit();
    std::string input = "canread2.txt";
    RandomRectangleGenerator::generateDataFile(114, input);
    RTreeController controller = IOControl::processInput(input, heuristic);

    Rectangle query(100000, 100001, 100000, 100001);

    //vRect dataMBRS = controller.extractDataMBRS();
   // Rectangle query = Rectangle::findMBR(dataMBRS);

    std::vector<int> result = controller.search(query);
    //IOControl::checkCache(controller.getControllerPrefix(), true);
    delete heuristic;
    EXPECT_EQ(result.size(), 0);
}
