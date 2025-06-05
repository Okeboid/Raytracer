//
// Created by adith on 02-01-2025.
//
#include "rectangle.h"

Rectangle::Rectangle(double length, double width,double thick, vec3 center, vec3 color){
  this->length = length;
  this->width = width;
  this->_center = center;
  this->_color = color;
}