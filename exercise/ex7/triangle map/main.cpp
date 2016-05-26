#include <iostream>

using namespace std;

double triangleMap (double x, double r) {
    if ( x < 0.5) {return r*x; }
    else {return r - r*x; }
}

int main() {
    int steps = 100;

    double r = 0.1;

    for (double x = 0; x <= 1.0; x+=1./steps) {
        cout << triangleMap(x,r) << endl;
    }
    return 0;
}