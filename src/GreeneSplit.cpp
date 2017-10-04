//
// Created by Cristobal M on 9/26/17.
//

#include <algorithm>
#include <cmath>
#include "GreeneSplit.h"

splittedNode GreeneSplit::split(vRect &vrect) {
  if (horMostDistantDimension(vrect)){
    std::sort(vrect.begin(), vrect.end(), [](const Rectangle& lhs, const Rectangle& rhs){ return lhs.y1 < rhs.y1; });
  }
  else{
    std::sort(vrect.begin(), vrect.end(), [](const Rectangle& lhs, const Rectangle& rhs){ return lhs.x1 < rhs.x1; });
  }
  vRect vrect2;
  for (int i = DEFAULT_MEMORY_SIZE; i >= DEFAULT_MEMORY_SIZE/2; i--){
    vrect2.push_back(std::move(vrect[i]));
    vrect.pop_back();
  }
  return std::pair(vrect, vrect2);
}


bool GreeneSplit::horMostDistantDimension(vRect &vrect) {
  float minX, minY, minX1, minY1;
  minX = minY = minX1 = minY1 = std::numeric_limits::infinity();
  float maxX, maxY, maxX2, maxY2;
  maxX = maxY = maxX2 = maxY2 = -std::numeric_limits::infinity();
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
