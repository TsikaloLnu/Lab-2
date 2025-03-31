#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>

struct point {
    double x, y;
};

enum AreaMethod { HERON = 1, GAUSS = 2, VECTOR = 3 };

struct triangle {
    point A, B, C;
    double area(int method = HERON) const;
    bool contains(const point &p, int method = HERON) const;
    bool containsVectorMethod(const point &p) const;
    bool isDegenerate(int method = HERON) const;
};

double distance(const point &p1, const point &p2);
double heronArea(const triangle &t);
double gaussArea(const triangle &t);

#endif // TRIANGLE_H
