//
// Created by Cristobal M on 9/26/17.
//

#include "RTree.h"

std::vector<int> RTree::search(Rectangle &rectangle) {
    return std::vector<int>();
}

void insert(Rectangle &rectangle) {
    if (this->isLeaf){
        /*if (this->node.length()== M){
         *  llamar a la heuristica
         *}*/
        this->node.push_back(rectangle);
    } else {
        Rectangle min_rectangle = null;
        float req_gr = std::numeric_limits<float>::max();
        float area = std::numeric_limits<float>::max();
        for (auto &node_rect : this->node) {
            float new_req_gr = required_growth(node_rect, rectangle);
            float new_area = node_rect.area();
                if (new_req_gr < req_gr){
                    area = new_area;
                    req_gr = new_req_gr;
                    min_rectangle = node_rect;
                } else if (new_req_gr == req_gr) {
                    if (area < new_area) {
                        area = new_area;
                        req_gr = new_req_gr;
                        min_rectangle = node_rect;
                    } else if (area == new_area){
                        if (rand() % 2 == 1) {
                            area = new_area;
                            req_gr = new_req_gr;
                            min_rectangle = node_rect;
                        }
                    }
                }
        }
        std::string current_name = "rtree" + std::to_string(save_number) + ".txt";
        std::string next_name = min_rectangle.address;
        IOControl::saveRTree(*this, current_name);
        save_number++;
        RTree next_rtree = IOControl::getRTree(next_name);
        next_rtree.insert(rectangle);
    }

}

const vRect &RTree::getNode() const {
    return node;
}

RTree::RTree(SplitHeuristic *splitHeuristic, std::string inputFilename) {
    this->splitHeuristic = splitHeuristic;
    this->inputFilename = inputFilename;
}
