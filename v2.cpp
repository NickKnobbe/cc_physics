#include "v2.h"
#include <cmath>

V2::V2() : x(0.0), y(0.0) {}
V2::V2(float _x, float _y) : x(_x), y(_y) {}
V2::V2(const V2& other) : x(other.x), y(other.y) {}
V2::~V2() {}

float V2::dist(V2& to) {
    float xDist = to.x - x;
    float yDist = to.y - y;
    float sqd = xDist * xDist + yDist * yDist;
    return std::sqrt(sqd);
}

float V2::dist_sqd(V2& to) {
    float xDist = to.x - x;
    float yDist = to.y - y;
    return xDist * xDist + yDist * yDist;
}

V2 V2::operator+(V2 other) {
    return V2(x + other.x, y + other.y);
}