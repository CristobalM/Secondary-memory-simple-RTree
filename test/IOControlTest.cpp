//
// Created by cristobal on 28-09-17.
//

#include <gtest/gtest.h>
#include "../src/IOControl.h"

TEST(IOControlTest, WriteSerialization) {
  vRect vrect;
  std::string yes("yes");
  Rectangle someRect(0, 0, 0, 1, yes);
  vrect.push_back(someRect);
  IOControl::saveVRect(vrect, "hola");
  vRect vrectget;
  vrectget = IOControl::getVRect("hola");
  EXPECT_EQ(vrectget.size(), 1);
  EXPECT_EQ(vrect[0].x1, 0);
  EXPECT_EQ(vrect[0].x2, 0);
  EXPECT_EQ(vrect[0].y1, 0);
  EXPECT_EQ(vrect[0].y2, 1);
  EXPECT_EQ(vrect[0].address, "yes");
}
