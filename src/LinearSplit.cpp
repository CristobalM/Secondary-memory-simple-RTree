//
// Created by Cristobal M on 9/26/17.
//


#include "LinearSplit.h"


std::pair<vRect, vRect> LinearSplit::split(vRect &vRect) {
  vRect node1, node2;
  std::pair<int,int> distantRects = mostDistantPair(vRect);

  Rectangle &rect1 = vRect[distantRects.first];
  Rectangle &rect2 = vRect[distantRects.second];

  std::vector<long> randomPermutation = fisherYatesVariation(vRect.size()-2, vRect.size()-2);

  for(long selectedIndex :  randomPermutation){
    if(selectedIndex == distantRects.first) {
      selectedIndex = vRect.size() - 1;
    }
    else if(selectedIndex == distantRects.second) {
      selectedIndex = vRect.size() - 2;
    }
  }

}
