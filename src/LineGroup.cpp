#include "LineGroup.h"

#include <iostream>
#include <string>
#include <cmath>

LineGroup::LineGroup(int x, int y) {

   this->leftX = x;

   this->y = y;
}

void LineGroup::setWidth(int rightX) {
   this->width = rightX - leftX;
}

void LineGroup::print() {

   for(int x = leftX; x < leftX + width; x++) {
      std::cout << "[" << x << "," << y << "]";
   }
}

int LineGroup::getLineNumber() {
   return this->y;
}

int LineGroup::getRightX() {
   return this->leftX + this->width;
}

int LineGroup::getLeftX() {
   return this->leftX;
}

bool LineGroup::nextTo(LineGroup * lg) {

   if(abs(this->y - lg->getLineNumber()) > 1) {
      return false;
   }
   else if(lg->getLeftX() >= this->leftX && lg->getLeftX() <= this->getRightX()) {
      return true;
   }
   else if(lg->getRightX() >= this->leftX && lg->getRightX() <= this->getRightX()) {
      return true;
   }
   else {
      return false;
   }
}

bool LineGroup::isSingle() {
   if(width == 0) {
      return true;
   }

   return false;
}
