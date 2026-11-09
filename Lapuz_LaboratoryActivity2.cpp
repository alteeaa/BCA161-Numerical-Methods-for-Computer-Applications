// Laboratory Exercise 2
// Bisection Method
//
// Idea: if f(Xl) and f(Xu) have opposite signs, a root lies between them.
// Cut the interval in half (Xr = (Xl + Xu) / 2), keep the half where the
// sign change happens, and repeat until the approximate error is small.
//
// Error formula used in this lab (Eq. 5.3, bisection only):
//      |ea| = | (Xu - Xl) / (Xu + Xl) | * 100%
 
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
 
// Change this function to solve a different f(x).
double f(double x) {
    return 10.0 * cos(x + 0.8) * exp(-0.3 * x);
}
 
int main() {
    double xl, xu, xr, fl, fu, fr, ea;
    const double es = 0.05;   // stopping tolerance, in percent
    const int imax = 100;     // safety cap so the loop can never run forever
    int iter = 0;
 
    cout << "Laboratory Exercise 2\n";
    cout << "Bisection Method: f(x) = 10*cos(x+0.8)*exp(-0.3*x), es = 0.05%\n\n";
    cout << "Enter Xl> "; cin >> xl;
    cout << "Enter Xu> "; cin >> xu;
    cout << "\n";
 
    fl = f(xl);
    fu = f(xu);
 
    // Step 1 of Fig. 5.5: the guesses must bracket a root, f(Xl)*f(Xu) < 0
    if (fl * fu >= 0) {
        cout << "Xl and Xu do not bracket a root (f(Xl)*f(Xu) is not negative).\n";
        return 1;
    }
 
    cout << "Iter#\tXl\t\tXu\t\tXr\t\tf(xl)\t\tf(xr)\t\tf(xu)\t\t|ea|\n";
 
    do {
        xr = (xl + xu) / 2.0;                         // Step 2: midpoint
        fr = f(xr);
        ea = fabs((xu - xl) / (xu + xl)) * 100.0;     // Eq. (5.3)
        iter++;
 
        // Print the row using the bracket BEFORE it gets updated below.
        cout << iter << "\t"
             << fixed << setprecision(6) << xl << "\t"
             << fixed << setprecision(6) << xu << "\t"
             << fixed << setprecision(6) << xr << "\t"
             << fixed << setprecision(6) << fl << "\t"
             << fixed << setprecision(6) << fr << "\t"
             << fixed << setprecision(6) << fu << "\t"
             << fixed << setprecision(6) << ea << "\n";
 
        // Step 3: decide which half contains the root
        double test = fl * fr;
        if (test < 0) {          // sign change in the lower half
            xu = xr;
            fu = fr;
        } else if (test > 0) {   // sign change in the upper half
            xl = xr;
            fl = fr;
        } else {                 // f(Xr) is exactly zero: root found
            ea = 0.0;
        }
 
    } while (ea > es && iter < imax);
 
    cout << "\nApproximate root = " << fixed << setprecision(6) << xr << "\n";
    cout << "f(" << fixed << setprecision(6) << xr << ") = "
         << fixed << setprecision(6) << f(xr) << "\n";
 
    return 0;
}