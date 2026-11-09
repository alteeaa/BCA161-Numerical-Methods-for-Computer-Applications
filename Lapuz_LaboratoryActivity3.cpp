// Laboratory Exercise 3
// Modified False Position Method
//
// False position joins (Xl, f(Xl)) and (Xu, f(Xu)) with a straight line
// and uses where that line crosses zero as the next estimate Xr.
// Plain false position can be "one-sided": one end stays fixed while the
// other creeps toward the root. To fix this, il and iu count how many
// times in a row Xl (or Xu) has stayed put. When a counter reaches 2,
// the function value at that stuck end is halved, which breaks the stall.
 
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
 
int problem = 1;   // 1 = 10cos(x+0.8)exp(-0.3x),  2 = x^10 - 1
 
double f(double x) {
    if (problem == 1)
        return 10.0 * cos(x + 0.8) * exp(-0.3 * x);
    return pow(x, 10) - 1.0;
}
 
int main() {
    double xl, xu, xr = 0.0, xrold;
    double fl, fu, fr;
    double ea = 0.0;
    const double es = 0.05;   // stopping tolerance, in percent
    const int imax = 100;     // safety cap on iterations
    int il = 0, iu = 0, iter = 0;
 
    cout << "Modified False Position Method\n";
    cout << "[1] f(x) = 10cos(x+0.8)exp(-0.3x)\n";
    cout << "[2] f(x) = x^10 - 1\n";
    cout << "Select problem> "; cin >> problem;
    cout << "\n";
 
    cout << "Modified False Position Method:\n";
    if (problem == 1) {
        cout << "f(x) = 10cos(x+0.8)exp(-0.3x)\n";
        cout << "Search Interval = [4, 10]\n";
    } else {
        cout << "f(x) = x^10 - 1\n";
        cout << "Search Interval = [0, 1.3]\n";
    }
    cout << "es = 0.05%\n\n";
 
    cout << "Enter Xl> "; cin >> xl;
    cout << "Enter Xu> "; cin >> xu;
    cout << "\n";
 
    fl = f(xl);
    fu = f(xu);
 
    if (fl * fu >= 0) {
        cout << "Xl and Xu do not bracket a root (f(Xl)*f(Xu) is not negative).\n";
        return 1;
    }
 
    cout << "Iter#\tXl\t\tXu\t\tXr\t\tf(xl)\t\tf(xr)\t\tf(xu)\t\t|ea|\n";
 
    do {
        xrold = xr;
        xr = xu - fu * (xl - xu) / (fl - fu);   // Eq. (5.7)
        fr = f(xr);
        iter++;
 
        // Print the bracket values BEFORE this pass updates them.
        cout << iter << "\t"
             << fixed << setprecision(6) << xl << "\t"
             << fixed << setprecision(6) << xu << "\t"
             << fixed << setprecision(6) << xr << "\t"
             << fixed << setprecision(6) << fl << "\t"
             << fixed << setprecision(6) << fr << "\t"
             << fixed << setprecision(6) << fu << "\t";
 
        if (iter == 1) {
            cout << "-----------\n";   // no previous Xr to compare yet
        } else {
            ea = fabs((xr - xrold) / xr) * 100.0;   // Eq. (5.2)
            cout << fixed << setprecision(6) << ea << "\n";
        }
 
        double test = fl * fr;
        if (test < 0) {
            // root is in the lower part: Xu moves down to Xr
            xu = xr;
            fu = fr;
            iu = 0;
            il++;
            if (il >= 2) fl = fl / 2.0;   // Xl stalled twice: halve f(Xl)
        } else if (test > 0) {
            // root is in the upper part: Xl moves up to Xr
            xl = xr;
            fl = fr;
            il = 0;
            iu++;
            if (iu >= 2) fu = fu / 2.0;   // Xu stalled twice: halve f(Xu)
        } else {
            ea = 0.0;   // f(Xr) is exactly zero: root found
        }
 
    } while ((iter == 1 || ea > es) && iter < imax);
 
    cout << "\nApproximate root = " << fixed << setprecision(6) << xr << "\n";
    cout << "f(" << fixed << setprecision(6) << xr << ") = "
         << fixed << setprecision(6) << f(xr) << "\n";
 
    return 0;
}
 