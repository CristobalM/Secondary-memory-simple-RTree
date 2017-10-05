//
// Created by Cristobal M on 10/4/17.
//

#include "SplitBuilder.h"

SplitBuilder::SplitBuilder(vRect &vrect) : vrect(vrect) {}

void SplitBuilder::putLeft() {
  Rectangle lastElement = vrect.back();
  result.first.push_back(lastElement);
  vrect.pop_back();
}

void SplitBuilder::putRight() {
  Rectangle lastElement = vrect.back();
  result.second.push_back(lastElement);
  vrect.pop_back();
}

std::pair<vRect, vRect> SplitBuilder::getPair() {
  return result;
}

Rectangle &SplitBuilder::getBackRectangle() {
  return vrect.back();
}



