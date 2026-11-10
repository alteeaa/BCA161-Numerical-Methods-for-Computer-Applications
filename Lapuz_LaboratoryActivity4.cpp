// Laboratory Exercise 4
// Newton-Raphson Method
//
// Idea: from the current guess Xi, extend the tangent line to the curve.
// Where that tangent crosses the x-axis is the next guess (Eq. 6.6):
//      X(i+1) = Xi - f(Xi) / f'(Xi)
// Unlike the bracketing methods of Chapter 5, only ONE starting guess is
// needed, and it does not have to bracket the root.
//
// Stopping rule (Sec. 6.2.1): |ea| = |(X_new - X_old) / X_new| * 100 < es.
// For at least 3 significant figures, es = 0.5 * 10^(2-3) = 0.05%.
//
// Safeguards recommended in Sec. 6.2.3 and used here:
//   - an upper limit on the number of iterations (imax)
//   - a check for f'(x) = 0 (division by zero in Eq. 6.6)
 
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
 
// f(x) = 10 + 5exp(-0.1x)sin(0.2x) - x
double f(double x) {
    return 10.0 + 5.0 * exp(-0.1 * x) * sin(0.2 * x) - x;
}
 
// f'(x) = -0.5exp(-0.1x)sin(0.2x) + exp(-0.1x)cos(0.2x) - 1
double df(double x) {
    return -0.5 * exp(-0.1 * x) * sin(0.2 * x)
           + exp(-0.1 * x) * cos(0.2 * x) - 1.0;
}
 
int main() {
    double xi, xnew, fx, dfx, ea;
    const double es = 0.05;   // stopping tolerance, in percent
    const int imax = 100;     // safeguard: cap on iterations
    int iter = 0;
 
    cout << "Newton-Raphson Method:\n";
    cout << "f(x) = 10 + 5exp(-0.1 x)sin(0.2x) - x\n";
    cout << "Search Interval = [1, 20]\n";
    cout << "es = 0.05%\n\n";
    cout << "Enter Xi> "; cin >> xi;
    cout << "\n";
 
    cout << "Iter#\tXi\t\tf(xi)\t\tf'(xi)\t\t|ea|\n";
    cout << iter << "\t" << fixed << setprecision(8) << xi
         << "\t--------\t--------\t--------\n";
 
    do {
        fx = f(xi);
        dfx = df(xi);
 
        if (dfx == 0.0) {   // safeguard: a flat tangent never crosses the x-axis
            cout << "f'(x) = 0 at x = " << xi << ". Try a different Xi.\n";
            return 1;
        }
 
        xnew = xi - fx / dfx;                     // Eq. (6.6)
        ea = fabs((xnew - xi) / xnew) * 100.0;    // approximate % relative error
        iter++;
 
        // f(xi) and f'(xi) are the values at the OLD guess used for this step;
        // Xi shown is the NEW estimate it produced.
        cout << iter << "\t"
             << fixed << setprecision(8) << xnew << "\t"
             << fixed << setprecision(8) << fx << "\t"
             << fixed << setprecision(8) << dfx << "\t"
             << fixed << setprecision(8) << ea << "\n";
 
        xi = xnew;
 
    } while (ea > es && iter < imax);
 
    cout << "\nApproximate root = " << fixed << setprecision(8) << xi << "\n";
 
    return 0;
}