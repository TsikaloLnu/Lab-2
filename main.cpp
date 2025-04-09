#include <iostream>
#include "triangle.h"

using namespace std;

int main(){
    triangle t;
    cout << "Введіть координати трикутника (Ax Ay Bx By Cx Cy): ";
    cin >> t.A.x >> t.A.y >> t.B.x >> t.B.y >> t.C.x >> t.C.y;

    int method;
    cout << "Оберіть метод обчислення площі: \n"
         << "1 - формула Герона\n"
         << "2 - Метод Гаусса\n"
         << "3 - метод векторного добутку\n"
         << "Ваш вибір: ";
    cin >> method;

    if (method == HERON || method == GAUSS){
        if (t.isDegenerate(method)){
            cout << "Трикунтник вироджений!" << endl;
            return 0;
        }

        cout << "Площа трикутника: " << t.area(method) << endl;
    }

    int n;
    cout << "Введіть к-ть точок для перевірки: ";
    cin >> n;

    for (int i = 0; i < n; i++){
        point p;
        cout << "Введіть координати точки " << i + 1 << ": ";
        cin >> p.x >> p.y;

        switch (method){
            case HERON:
            case GAUSS:
                if( t.contains(p, method)){
                    cout << "Точка " << i + 1 << " належить трикутнику" << endl;
                }else {
                    cout << "Точка " << i + 1 << " не належить трикутнику" << endl; 
                }
                break;
                case VECTOR:
                if (t.containsVectorMethod(p)) {
                    
                } else {
                    cout << "Точка " << i + 1 << " не належить трикутнику" << endl;
                }
                break;

            default:
                cout << "Невідомий метод" << endl;
                return 1;
        }
    }

    return 0;
}