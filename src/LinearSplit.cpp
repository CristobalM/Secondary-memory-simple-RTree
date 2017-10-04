//
// Created by Cristobal M on 9/26/17.
//


#include "LinearSplit.h"


std::pair<vRect, vRect> LinearSplit::split(vRect &vRect, std::string parentFilename, int parentRectangleIndex) {
  vRect node1;
  vRect node2;
  std::pair<int,int> distantRects = mostDistantPair(vRect);

  Rectangle &rect1 = vRect[distantRects.first];
  Rectangle &rect2 = vRect[distantRects.second];

  std::vector<long> randomPermutation = fisherYatesVariation(vRect.size(), vRect.size());

  for(long selectedIndex : randomPermutation){
    Rectangle &selectedRect = vRect[selectedIndex];
    float toIncreaseArea1 = Rectangle::areaIncrease(rect1, selectedRect);
    float toIncreaseArea2 = Rectangle::areaIncrease(rect2, selectedRect);
    if(toIncreaseArea1 <= toIncreaseArea2){
      node1.push_back(selectedRect);
    }
    else{
      node2.push_back(selectedRect);
    }
  }

}
