//
// Created by Cristobal M on 9/26/17.
//

#include <limits>
#include "LinearSplit.h"


void LinearSplit::split(vRect &node) {
  float minX = std::numeric_limits<float>::infinity();
  float maxX = -minX;
  float minY = minX;
  float maxY = -minX;
  unsigned long currentNodeSize = node.size();
  for(Rectangle rectangle : node){
    if(maxX < rectangle.x1){
      maxX = rectangle.x1;
    }
    if(minX > rectangle.x2){
      minX = rectangle.x2;
    }
    if(maxY < rectangle.y1){
      maxY = rectangle.y1;
    }
    if(minY > rectangle.y2){
      minY = rectangle.y2;
    }
  }
  unsigned long pairCount = 0;
  for(Rectangle rect1 : node) {
    for (Rectangle rect2 : node){

    }
  }
}
