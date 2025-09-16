#include <iostream>
#include <cmath>
using namespace std;

const double EPS = 1e-5; // точность сравнения

//  ТОЧКА 
struct Point {
    double x, y;
};

// ввод точки
void readPoint(Point &p) {
    cin >> p.x >> p.y;
}

// вывод точки
void printPoint(const Point &p) {
    cout << "(" << p.x << ", " << p.y << ")";
}

//  КРУГ
struct Circle {
    Point center;
    double r;
};

// ввод круга
void readCircle(Circle &c) {
    cin >> c.center.x >> c.center.y >> c.r;
}

// вывод круга
void printCircle(const Circle &c) {
    cout << "Circle: center=(" << c.center.x << ", " << c.center.y 
         << "), radius=" << c.r << endl;
}

// длина окружности
double circumference(const Circle &c) {
    return 2 * M_PI * c.r;
}

// площадь круга
double area(const Circle &c) {
    return M_PI * c.r * c.r;
}

//  КВАДРАТ
struct Square {
    Point topLeft; // верхний левый угол
    double side;
};

// ввод квадрата
void readSquare(Square &s) {
    cin >> s.topLeft.x >> s.topLeft.y >> s.side;
}

// вывод квадрата
void printSquare(const Square &s) {
    cout << "Square: topLeft=(" << s.topLeft.x << ", " << s.topLeft.y 
         << "), side=" << s.side << endl;
}

// периметр квадрата
double perimeter(const Square &s) {
    return 4 * s.side;
}

// площадь квадрата
double area(const Square &s) {
    return s.side * s.side;
}

//  ФУНКЦИИ ДЛЯ ТОЧКИ 
double dist(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + 
                (a.y - b.y) * (a.y - b.y));
}

// принадлежность точки кругу
bool pointInCircle(const Point &p, const Circle &c) {
    return dist(p, c.center) < c.r - EPS;
}

// принадлежность точки квадрату
bool pointInSquare(const Point &p, const Square &s) {
    double x1 = s.topLeft.x;
    double y1 = s.topLeft.y;
    double x2 = x1 + s.side;
    double y2 = y1 - s.side; // вниз по y
    return (p.x > x1 + EPS && p.x < x2 - EPS && 
            p.y > y2 + EPS && p.y < y1 - EPS);
}

// точка на окружности
bool pointOnCircle(const Point &p, const Circle &c) {
    return fabs(dist(p, c.center) - c.r) < EPS;
}

// точка на квадрате
bool pointOnSquare(const Point &p, const Square &s) {
    double x1 = s.topLeft.x;
    double y1 = s.topLeft.y;
    double x2 = x1 + s.side;
    double y2 = y1 - s.side;

    bool onLeft   = fabs(p.x - x1) < EPS && p.y <= y1 && p.y >= y2;
    bool onRight  = fabs(p.x - x2) < EPS && p.y <= y1 && p.y >= y2;
    bool onTop    = fabs(p.y - y1) < EPS && p.x >= x1 && p.x <= x2;
    bool onBottom = fabs(p.y - y2) < EPS && p.x >= x1 && p.x <= x2;

    return onLeft ; onRight ; onTop || onBottom;
}

//  ПЕРЕСЕЧЕНИЯ 
// пересечение двух кругов
bool intersectCircles(const Circle &c1, const Circle &c2) {
    double d = dist(c1.center, c2.center);
    return d <= c1.r + c2.r + EPS && d >= fabs(c1.r - c2.r) - EPS;
}

// пересечение двух квадратов
bool intersectSquares(const Square &s1, const Square &s2) {
    double x1_min = s1.topLeft.x;
    double y1_max = s1.topLeft.y;
    double x1_max = x1_min + s1.side;
    double y1_min = y1_max - s1.side;

    double x2_min = s2.topLeft.x;
    double y2_max = s2.topLeft.y;
    double x2_max = x2_min + s2.side;
    double y2_min = y2_max - s2.side;

    bool overlapX = !(x1_max < x2_min || x2_max < x1_min);
    bool overlapY = !(y1_min > y2_max || y2_min > y1_max);

    return overlapX && overlapY;
}

// пересечение круга и квадрата
bool intersectCircleSquare(const Circle &c, const Square &s) {
    double x1 = s.topLeft.x;
    double y1 = s.topLeft.y;
    double x2 = x1 + s.side;
    double y2 = y1 - s.side;

    // ближайшая точка квадрата к центру круга
    double closestX = min(max(c.center.x, x1), x2);
    double closestY = min(max(c.center.y, y2), y1);

    Point closest{closestX, closestY};
    return dist(c.center, closest) <= c.r + EPS;
}

// ПРИНАДЛЕЖНОСТЬ ФИГУР 
// круг внутри круга
bool circleInCircle(const Circle &c1, const Circle &c2) {
    double d = dist(c1.center, c2.center);
    return d + c1.r <= c2.r + EPS;
}
// квадрат внутри квадрата
bool squareInSquare(const Square &s1, const Square &s2) {
    double x1 = s1.topLeft.x;
    double y1 = s1.topLeft.y;
    double x2 = x1 + s1.side;
    double y2 = y1 - s1.side;

    double X1 = s2.topLeft.x;
    double Y1 = s2.topLeft.y;
    double X2 = X1 + s2.side;
    double Y2 = Y1 - s2.side;

    return (x1 >= X1 - EPS && x2 <= X2 + EPS &&
            y1 <= Y1 + EPS && y2 >= Y2 - EPS);
}

// квадрат внутри круга
bool squareInCircle(const Square &s, const Circle &c) {
    Point p1 = s.topLeft;
    Point p2 = {s.topLeft.x + s.side, s.topLeft.y};
    Point p3 = {s.topLeft.x, s.topLeft.y - s.side};
    Point p4 = {s.topLeft.x + s.side, s.topLeft.y - s.side};

    return pointInCircle(p1, c) && pointInCircle(p2, c) &&
           pointInCircle(p3, c) && pointInCircle(p4, c);
}

// круг внутри квадрата
bool circleInSquare(const Circle &c, const Square &s) {
    double x1 = s.topLeft.x;
    double y1 = s.topLeft.y;
    double x2 = x1 + s.side;
    double y2 = y1 - s.side;

    return (c.center.x - c.r >= x1 - EPS &&
            c.center.x + c.r <= x2 + EPS &&
            c.center.y + c.r <= y1 + EPS &&
            c.center.y - c.r >= y2 - EPS);
}

//  MAIN (пример использования) 
int main() {
    Circle c;
    Square s;
    Point p;

    cout << "krug and radius: ";
    readCircle(c);
    printCircle(c);
    cout << "Area=" << area(c) << ", Length=" << circumference(c) << endl;

    cout << "kvadrat and storona: ";
    readSquare(s);
    printSquare(s);
    cout << "Area=" << area(s) << ", Perimeter=" << perimeter(s) << endl;

    cout << "tochka: ";
    readPoint(p);
    printPoint(p);
    cout << endl;

    cout << "tochka vnutri kruag? " << (pointInCircle(p, c) ? "YES" : "NO") << endl;
    cout << "tochka vnutri kvadrata? " << (pointInSquare(p, s) ? "YES" : "NO") << endl;
    cout << "tochka na okrujnoti? " << (pointOnCircle(p, c) ? "YES" : "NO") << endl;
    cout << "tochka na kvadrate? " << (pointOnSquare(p, s) ? "YES" : "NO") << endl;

    return 0;
}