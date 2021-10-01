#ifndef POINT_H
#define POINT_H

#include <math.h>

struct Point{
    int x = 0;
    int y = 0;
};

class Triangle{
private:
    double a = 0,b = 0,c = 0;
    double p = 0;
    double s = 0;
    double calculatePerimeter();
    double calculateSquare();
public:
    Point point1, point2, point3;
    double getPerimeter();
    double getSquare();
};

#endif // POINT_H
