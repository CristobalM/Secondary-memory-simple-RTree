//
// Created by Cristobal M on 9/26/17.
//


#include "LinearSplit.h"
#include "SplitBuilder.h"
#include "FilenameGenerator.h"



void permutateVRect(vRect &which, std::vector<long> &permutation){
  vRect whichCopy(which);
  for(int i = 0; i < which.size(); i++){
    which[permutation[i]] = whichCopy[i];
  }
}

std::pair<vRect, vRect> LinearSplit::split(vRect &vrect, std::string parentFilename, int parentRectangleIndex) {
  vRect node1;
  vRect node2;
  std::pair<int,int> distantRects = mostDistantPair(vrect);

  Rectangle &rect1 = vrect[distantRects.first];
  Rectangle &rect2 = vrect[distantRects.second];

  Rectangle mbr1 = rect1.deriveParent(FilenameGenerator::generateNewFilename());
  Rectangle mbr2 = rect2.deriveParent(FilenameGenerator::generateNewFilename());


  std::vector<long> randomPermutation = fisherYatesVariation(vrect.size(), vrect.size());
  permutateVRect(vrect, randomPermutation);

  SplitBuilder splitBuilder(vrect);

  while(vrect.size() > 0){
    Rectangle selectedRect = splitBuilder.getBackRectangle();
    float toIncreaseArea1 = mbr1.areaIncrease(selectedRect);
    float toIncreaseArea2 = mbr2.areaIncrease(selectedRect);
    if(toIncreaseArea1 <= toIncreaseArea2){
      //node1.push_back(selectedRect);
      splitBuilder.putLeft();
    }
    else{
      splitBuilder.putRight();
    }
  }

  for(long selectedIndex : randomPermutation){
    Rectangle &selectedRect = vrect[selectedIndex];
    float toIncreaseArea1 = mbr1.areaIncrease(selectedRect);
    float toIncreaseArea2 = mbr2.areaIncrease(selectedRect);
    if(toIncreaseArea1 <= toIncreaseArea2){
      node1.push_back(selectedRect);
    }
    else{
      node2.push_back(selectedRect);
    }
  }





}
