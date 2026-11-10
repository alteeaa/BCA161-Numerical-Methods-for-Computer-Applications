// Laboratory Exercise 5
// Newton-Raphson Method
//
// f(x) = 5 - 8x exp(-0.2x)
// Starting guess X0 = 14, stop when |ea| < es = 0.05%.
//
// Newton-Raphson formula (Eq. 6.6):
//      X(i+1) = Xi - f(Xi) / f'(Xi)
// Derivative (product rule):
//      f'(x) = -8exp(-0.2x) + 1.6x exp(-0.2x) = exp(-0.2x) * (1.6x - 8)
//
// Like the manual calculation done to 6 decimal places, each new estimate is
// rounded to 6 decimals before it is used in the next iteration.
//
// Precautionary steps from Sec. 6.2.3 used here:
//   - an upper limit on the number of iterations (imax)
//   - a check for f'(x) = 0 (division by zero in Eq. 6.6)
 
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
 
double f(double x) {
    return 5.0 - 8.0 * x * exp(-0.2 * x);
}
 
double df(double x) {
    return exp(-0.2 * x) * (1.6 * x - 8.0);
}
 
// Round a value to 6 decimal places.
double r6(double v) {
    return round(v * 1000000.0) / 1000000.0;
}
 
int main() {
    double xi, xnew, fx, dfx, ea;
    const double es = 0.05;   // stopping tolerance, in percent
    const int imax = 100;     // safeguard: cap on iterations
    int iter = 0;
 
    cout << "Newton-Raphson Method:\n";
    cout << "f(x) = 5 - 8xexp(-0.2x)\n";
    cout << "es = 0.05%\n\n";
    cout << "Enter Xi> "; cin >> xi;
    cout << "\n";
 
    cout << "Iter#\tXi\t\tf(xi-1)\t\tf'(xi-1)\t|ea|\n";
    cout << iter << "\t" << fixed << setprecision(6) << xi
         << "\t--------\t--------\t--------\n";
 
    do {
        fx = f(xi);
        dfx = df(xi);
 
        if (dfx == 0.0) {   // safeguard: a flat tangent never crosses the x-axis
            cout << "f'(x) = 0 at x = " << xi << ". Try a different Xi.\n";
            return 1;
        }
 
        xnew = r6(xi - fx / dfx);                 // Eq. (6.6)
        ea = fabs((xnew - xi) / xnew) * 100.0;    // approximate % relative error
        iter++;
 
        // f(xi-1) and f'(xi-1) are the values at the PREVIOUS guess, which
        // were used to produce the new estimate Xi shown in this row.
        cout << iter << "\t"
             << fixed << setprecision(6) << xnew << "\t"
             << fixed << setprecision(6) << fx << "\t"
             << fixed << setprecision(6) << dfx << "\t"
             << fixed << setprecision(6) << ea << "\n";
 
        xi = xnew;
 
    } while (ea > es && iter < imax);
 
    cout << "\nApproximate root = " << fixed << setprecision(6) << xi << "\n";
 
    return 0;
}