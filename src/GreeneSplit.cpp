//
// Created by Cristobal M on 9/26/17.
//

#include <algorithm>
#include <cmath>
#include <limits>
#include "GreeneSplit.h"
#include "FilenameGenerator.h"

splittedNode GreeneSplit::split(vRect &vrect) {
  if (horMostDistantDimension(vrect)){
    std::sort(vrect.begin(), vrect.end(), [](const Rectangle& lhs, const Rectangle& rhs){ return lhs.y1 < rhs.y1; });
  }
  else{
    std::sort(vrect.begin(), vrect.end(), [](const Rectangle& lhs, const Rectangle& rhs){ return lhs.x1 < rhs.x1; });
  }
  vRect vrectl;
  vRect vrectr;
  for (int i = DEFAULT_MAX_NODE_SIZE; i >= DEFAULT_MAX_NODE_SIZE/2; i--){
    vrectl.push_back(std::move(vrect[i]));
    vrect.pop_back();
  }
  for (int i = DEFAULT_MAX_NODE_SIZE/2 - 1; i>= 0; i--){
    vrectr.push_back(std::move(vrect[i]));
    vrect.pop_back();
  }
  splittedNode sn;
  sn.left = vrectl;
  sn.right = vrectr;
  sn.leftParent = MBR(vrectl);
  sn.rightParent = MBR(vrectr);
  return sn;
}


bool GreeneSplit::horMostDistantDimension(vRect &vrect) {
  float minX, minY, minX1, minY1;
  minX = minY = minX1 = minY1 = std::numeric_limits<float>::infinity();
  float maxX, maxY, maxX2, maxY2;
  maxX = maxY = maxX2 = maxY2 = -std::numeric_limits<float>::infinity();
  for(int i = 0; i < vrect.size(); i++){
    Rectangle &rect = vrect[i];
    if(maxX < rect.x1){
      maxX = rect.x1;
    }
    if(minX > rect.x2){
      minX = rect.x2;
    }
    if(maxY < rect.y1){
      maxY = rect.y1;
    }
    if(minY > rect.y2){
      minY = rect.y2;
    }
    if(minX1 > rect.x1){
      minX1 = rect.x1;
    }
    if(maxX2 < rect.x2){
      maxX2 = rect.x2;
    }
    if(minY1 > rect.y1){
      minY1 = rect.y1;
    }
    if(maxY2 < rect.y2){
      maxY2 = rect.y2;
    }
  }
  float xDimSeparationNorm = std::abs(maxX - minX)/(maxX2 - minX1);
  float yDimSeparationNorm = std::abs(maxY - minY)/(maxY2 - minY1);

  return xDimSeparationNorm >= yDimSeparationNorm;

}

Rectangle GreeneSplit::MBR(vRect &vect) {
  float minX1, minY1;
  minX1 = minY1 = std::numeric_limits<float>::infinity();
  float maxX2, maxY2;
  maxX2 = maxY2 = -std::numeric_limits<float>::infinity();
  for (auto &rect : vect){
    if (rect.x1 < minX1){
      minX1 = rect.x1;
    }
    if (rect.x2 > maxX2){
      maxX2 = rect.x2;
    }
    if (rect.y1 < minY1){
      minY1 = rect.y1;
    }
    if (rect.y2 > maxY2){
      maxY2 = rect.y2;
    }
  }
  return Rectangle(minX1, maxX2, minY1, maxY2, FilenameGenerator::generateNewIndex());
}

std::string GreeneSplit::heuristicName() {
  return "GreeneSplit";
}
