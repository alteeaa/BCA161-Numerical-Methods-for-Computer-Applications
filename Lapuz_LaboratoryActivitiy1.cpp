// Laboratory Exercise 1
// Estimate exp(x) using the Maclaurin series, accurate to at least
// 4 significant figures.
//
// Maclaurin series:  e^x = 1 + x + x^2/2! + x^3/3! + ...
//
// Instead of recomputing x^i / i! from scratch every time (slow, and
// risks overflow for large i), each new term is built from the
// previous one:
//      term_i = term_(i-1) * x / i
//
// We stop adding terms once the approximate percent relative error
// |ea| drops below the threshold es = 0.5 * 10^(2 - n), where n is
// the number of significant figures we want (n = 4 here -> es = 0.005).

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    double x;
    double term, sum, prevSum, ea;
    int i;

    cout << "Estimate of exp(x) that is accurate to at least 4 significant figures\n\n";
    cout << "Enter X> ";
    cin >> x;
    cout << "\n\n";

    // Stopping threshold for n = 4 significant figures
    const int n = 4;
    double es = 0.5 * pow(10, 2 - n);   // es = 0.005

    cout << "Iter#\texp(" << fixed << setprecision(8) << x << ")\t\t|ea|\n\n";

    // --- Iteration 1: just the first term (term 0 = 1), no error yet ---
    i = 1;
    term = 1.0;
    sum = 1.0;
    cout << i << "\t" << fixed << setprecision(8) << sum
         << "\t\t-----------\n";

    // --- Keep adding terms until the estimate stabilizes ---
    do {
        i++;
        prevSum = sum;

        term = term * x / (i - 1);   // build next term from the previous one
        sum = sum + term;            // add it to the running total

        ea = fabs((sum - prevSum) / sum) * 100.0;

        cout << i << "\t" << fixed << setprecision(8) << sum
             << "\t\t" << fixed << setprecision(8) << ea << "\n";

    } while (ea > es);

    return 0;
}
