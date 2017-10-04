//
// Created by Cristobal M on 10/3/17.
//

#include <utility>
#include <cmath>
#include <random>
#include <unordered_map>
#include "commontypes.h"
#include "SplitHeuristic.h"

std::pair<int, int> SplitHeuristic::mostDistantPair(vRect &vRect) {
  float minX, minY, minX1, minY1;
  minX = minY = minX1 = minY1 = std::numeric_limits::infinity();
  float maxX, maxY, maxX2, maxY2;
  maxX = maxY = maxX2 = maxY2 = -std::numeric_limits::infinity();
  int rightmostx1, leftmostx2, uppermosty1, lowermosty2;
  rightmostx1 = leftmostx2 = uppermosty1 = lowermosty2 = -1;
  for(int i = 0; i < vRect.size(); i++){
    Rectangle &rect = vRect[i];
    if(maxX < rect.x1){
      maxX = rect.x1;
      rightmostx1 = i;
    }
    if(minX > rect.x2){
      minX = rect.x2;
      leftmostx2 = i;
    }
    if(maxY < rect.y1){
      maxY = rect.y1;
      uppermosty1 = i;
    }
    if(minY > rect.y2){
      minY = rect.y2;
      lowermosty2 = i;
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
  int lesserRect, mostRect;
  if(xDimSeparationNorm >= yDimSeparationNorm){
    lesserRect = leftmostx2;
    mostRect = rightmostx1;
  }
  else{
    lesserRect = lowermosty2;
    mostRect = uppermosty1;
  }

  return std::make_pair(lesserRect, mostRect);
}

bool SplitHeuristic::horMostDistantDimension(vRect &vRect) {
  float minX, minY, minX1, minY1;
  minX = minY = minX1 = minY1 = std::numeric_limits::infinity();
  float maxX, maxY, maxX2, maxY2;
  maxX = maxY = maxX2 = maxY2 = -std::numeric_limits::infinity();
  for(int i = 0; i < vRect.size(); i++){
    Rectangle &rect = vRect[i];
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
  if(xDimSeparationNorm >= yDimSeparationNorm){
    return true;
  }
  return false;
}





std::vector<long> SplitHeuristic::fisherYatesVariation(long result_size, long choice_set_size) {
  std::vector<long> result;
  std::unordered_map<long, long> state;
  std::srand((time(0)));

  for(long i = 0; i < result_size; i++){
    long random_number = (std::rand() % (choice_set_size - i)) + i;
    long whichRand = random_number;
    long whichI = i;
    if(state.find(random_number) != state.end()){
      whichRand = state[random_number];
    }
    if(state.find(i) != state.end()){
      whichI = state[i];
    }
    state[i] = whichRand;
    state[random_number] = whichI;
  }

  for(int i = 0; i < result_size; i++){
    result.push_back(state[i]+1);
  }
  return result;
}

/*
float SplitHeuristic::areaIncrease(Rectangle &dst, Rectangle &src) {
  float xInc, yInc;
  if(src.x1 <= dst.x1 ){
    xInc = (float) std::max(0.0,  dst.x1 - src.x1);
  }
  else{
    xInc = (float) std::max(0.0, src.x2 - dst.x2);
  }

  if(src.y1 <= dst.y2){
    yInc = (float) std::max(0.0, dst.y1 - src.y1);
  }
  else{
    yInc = (float) std::max(0.0, src.y2 - dst.y2);
  }
  float rectDeltaX = (dst.x2 - dst.x1);
  float rectDeltaY = (dst.y2 - dst.y1);
  float rectArea = rectDeltaX * rectDeltaY;
  float incToArea = (rectDeltaX + xInc) * (rectDeltaY + yInc);

  return incToArea - rectArea;
}
 */

