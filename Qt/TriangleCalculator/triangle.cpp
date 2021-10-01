#include "triangle.h"


double Triangle::getPerimeter(){
    return calculatePerimeter();
}
double Triangle::getSquare(){
    return calculateSquare();
}
double Triangle::calculatePerimeter(){
    a = sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
    b = sqrt(pow(point3.x - point2.x, 2) + pow(point3.y - point2.y, 2));
    c = sqrt(pow(point1.x - point3.x, 2) + pow(point1.y - point3.y, 2));
    p = a+b+c;
    return p;
}
double Triangle::calculateSquare(){
    p = calculatePerimeter();
    double pp = p/2;
    s = sqrt(pp*(pp-a)*(pp-b)*(pp-c));
    return s;
}
