#include <iostream>
#include <vector>
#include "Rectangle.h"
#include "SplitHeuristic.h"
#include "LinearSplit.h"
#include "RandomRectangleGenerator.h"
#include "IOControl.h"
#include "RTreeController.h"


int main() {

    SplitHeuristic *heuristic = new LinearSplit();
    std::string input = "generated30M.txt";
    RandomRectangleGenerator::generateDataFile(30000000, input);
    int rootIndex = IOControl::processInput(input, heuristic);
    RTreeController controller(rootIndex, heuristic);

    delete heuristic;
    return 0;
}
