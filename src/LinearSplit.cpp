//
// Created by Cristobal M on 9/26/17.
//

#include "LinearSplit.h"


void LinearSplit::split(RTree &rTree) {
  float minX = std::numeric_limits<float>::infinity();
  float maxX = -minX;
  float minY = minX;
  float maxY = -minX;
  unsigned long currentNodeSize = rTree.getNode().size();
  for(Rectangle rectangle : rTree.getNode()){
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
  for(Rectangle rect1 : rTree.getNode()) {
    for (Rectangle rect2 : rTree.getNode()){

    }
  }
}
