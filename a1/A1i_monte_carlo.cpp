#include <iostream>
#include <random>
#include <cmath>
#include <vector>

using namespace std;

struct Circle {
    double x, y, r;
};

bool pointInCircle(double x, double y, const Circle& c) {
    return (x - c.x) * (x - c.x) + (y - c.y) * (y - c.y) <= c.r * c.r;
}

bool pointInIntersection(double x, double y, const vector<Circle>& circles) {
    for (const auto& circle : circles) {
        if (!pointInCircle(x, y, circle)) {
            return false;
        }
    }
    return true;
}

double monteCarloArea(const vector<Circle>& circles, 
                     double xmin, double xmax, 
                     double ymin, double ymax, 
                     int N) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> xdist(xmin, xmax);
    uniform_real_distribution<> ydist(ymin, ymax);

    int count = 0;
    for (int i = 0; i < N; ++i) {
        double x = xdist(gen);
        double y = ydist(gen);
        if (pointInIntersection(x, y, circles)) {
            count++;
        }
    }

    double rectArea = (xmax - xmin) * (ymax - ymin);
    return static_cast<double>(count) / N * rectArea;
}

int main() {
    vector<Circle> circles(3);
    
    // Чтение входных данных
    for (int i = 0; i < 3; ++i) {
        cin >> circles[i].x >> circles[i].y >> circles[i].r;
    }

    // Определение ограничивающего прямоугольника
    double xmin = 1e9, xmax = -1e9, ymin = 1e9, ymax = -1e9;
    for (const auto& circle : circles) {
        xmin = min(xmin, circle.x - circle.r);
        xmax = max(xmax, circle.x + circle.r);
        ymin = min(ymin, circle.y - circle.r);
        ymax = max(ymax, circle.y + circle.r);
    }

    // Выбор оптимального количества точек для точности 0.01
    int N = 1000000;
    double area = monteCarloArea(circles, xmin, xmax, ymin, ymax, N);
    
    cout.precision(10);
    cout << fixed << area << endl;

    return 0;
}
