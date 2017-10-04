//
// Created by Cristobal M on 9/26/17.
//

#include <algorithm>
#include "GreeneSplit.h"

std::pair<vRect, vRect> GreeneSplit::split(vRect &vRect, std::string parentFilename, int parentRectangleIndex) {
  if (horMostDistantDimension(vRect)){
    std::sort(vRect.begin(), vRect.end(), [](const Rectangle& lhs, const Rectangle& rhs){ return lhs.y1 < rhs.y1; });
  }
  else{
    std::sort(vRect.begin(), vRect.end(), [](const Rectangle& lhs, const Rectangle& rhs){ return lhs.x1 < rhs.x1; });
  }
  vRect vRect2;
  for (int i = M; i >= M/2; i--){
    vRect2.push_back(std::move(vRect[i]));
    vRect.pop_back();
  }
  return std::pair(vRect, vRect2);
}
