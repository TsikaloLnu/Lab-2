#include "triangle.h"

using namespace std;

// обчислення відстані між двома точками
double distance(const point &p1, const point &p2){
    return sqrt(pow (p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
} 

//формула Герона
double heronArea(const triangle &t){
    double a = distance (t.A, t.B);
    double b = distance(t.B, t.C);
    double c = distance(t.C, t.A);
    double s = (a + b + c) / 2;
    return sqrt( s * (s - a) * (s - b) * (s - c));
}

double triangle::area(int method) const{
    return (method == HERON) ? heronArea(*this) : gaussArea(*this);
}


//метод Гаусса
double gaussArea(const triangle &t){
    return 0.5 * fabs(t.A.x * (t.B.y - t.C.y) + t.B.x * (t.C.y - t.A.y) + t.C.x * (t.A.y - t.B.y));
}


//перевірка на приналежність точки до трикутника(методом площ)
bool triangle::contains(const point &p, int method) const{
    triangle t1 = {A, B, p};
    triangle t2 = {B, C, p};
    triangle t3 = {C, A, p};

    double S_main = area();
    double S_sum = t1.area() + t2.area() + t3.area(); 
    return fabs(S_main - S_sum) < 1e-9;
}

//Перевірка на приналежність точки до трикутника
bool triangle::containsVectorMethod(const point &p) const {

    double cross1 = (B.x - A.x) * (p.y - A.y) - (B.y - A.y) * (p.x - A.x);
    double cross2 = (C.x - B.x) * (p.y - B.y) - (C.y - B.y) * (p.x - B.x);
    double cross3 = (A.x - C.x) * (p.y - C.y) - (A.y - C.y) * (p.x - C.x);

    return (cross1 >= 0 && cross2 >= 0 && cross3 >= 0) || (cross1 <= 0 && cross2 <= 0 && cross3 <= 0);
}

bool triangle::isDegenerate(int method) const {
    return area() < 1e-9;
}