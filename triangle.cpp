#include "triangle.h"

using namespace std;

// обчислення відстані між двома точками
double distance(const point &p1, const point &p2){
    return sqrt(pow (p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
} 

// Векторний добуток AB × AC
double cross(const point &p1, const point &p2, const point &p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
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
bool triangle::contains(const point &p, int method) const {
    triangle t1 = {A, B, p};
    triangle t2 = {B, C, p};
    triangle t3 = {C, A, p};

    double S_main = area();
    double S_sum = t1.area() + t2.area() + t3.area(); 

    if(fabs(S_main - S_sum) < 1e-9){
        return true;
    } else {
        return false;
    }
}

//Перевірка на приналежність точки до трикутника
bool triangle::containsVectorMethod(const point &p) const {

    double cross1 = (B.x - A.x) * (p.y - A.y) - (B.y - A.y) * (p.x - A.x);
    double cross2 = (C.x - B.x) * (p.y - B.y) - (C.y - B.y) * (p.x - B.x);
    double cross3 = (A.x - C.x) * (p.y - C.y) - (A.y - C.y) * (p.x - C.x);

    bool has_neg = (cross1 < 0) || (cross2 < 0) || (cross3 < 0);
    bool has_pos = (cross1 > 0) || (cross2 > 0) || (cross3 > 0);

    // Якщо всі знаки однакові — точка всередині або на межі
    if (!(has_neg && has_pos)) {
        if (fabs(cross1) < 1e-9 && ifOnBorder(p, A, B)){
            cout << "Точка лежить на межі АВ" << endl;
        } else if (fabs(cross2) < 1e-9 && ifOnBorder(p, B, C)) {
            cout << "Точка лежить на межі BC" << endl;
        } else if (fabs(cross3) < 1e-9 && ifOnBorder(p, C, A)) {
            cout << "Точка лежить на межі CA" << endl;
        } else {
            cout << "Точка всередині трикутника" << endl;
        }

        return true;
    }

    return false;


}

bool triangle::isDegenerate(int method) const {
    return area() < 1e-9;
}

bool ifOnBorder(const point &p, const point &a, const point &b) {
    double crossProd = (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
    if (fabs(crossProd) > 1e-9) return false;

    double dotProd = (p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y);
    double squaredLengthAB = pow(b.x - a.x, 2) + pow(b.y - a.y, 2);

    return dotProd >= 0 && dotProd <= squaredLengthAB;
}
