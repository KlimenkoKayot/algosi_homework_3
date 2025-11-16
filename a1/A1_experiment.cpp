#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>

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
                     int N, int seed = 42) {
    mt19937 gen(seed);
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

double exactArea() {
    return 0.25 * M_PI + 1.25 * asin(0.8) - 1.0;
}

void runExperiment() {
    vector<Circle> circles = {
        {1.0, 1.0, 1.0},
        {1.5, 2.0, sqrt(5.0)/2.0},
        {2.0, 1.5, sqrt(5.0)/2.0}
    };

    double exact = exactArea();
    
    ofstream out("experiment_results.csv");
    out << "N,WideArea,NarrowArea,WideError,NarrowError" << endl;
    
    for (int N = 100; N <= 100000; N += 500) {
        // Широкая область [0,3]x[0,3]
        double wideArea = monteCarloArea(circles, 0.0, 3.0, 0.0, 3.0, N);
        double wideError = fabs(wideArea - exact) / exact;
        
        // Узкая область [1,2]x[1,2]  
        double narrowArea = monteCarloArea(circles, 1.0, 2.0, 1.0, 2.0, N);
        double narrowError = fabs(narrowArea - exact) / exact;
        
        out << N << "," << wideArea << "," << narrowArea << ","
            << wideError << "," << narrowError << endl;
    }
    
    out.close();
}

int main() {
    runExperiment();
    cout << "Эксперимент завершен. Результаты сохранены в experiment_results.csv" << endl;
    return 0;
}
