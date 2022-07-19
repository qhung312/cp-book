#include <bits/stdc++.h>
#include "matrix.h"
using namespace std;

int main() {
    // Adding and subtracting
    matrix<int> a(1, 2, 5), b(1, 2, 6);
    a += b;
    cout << a;
    a -= b;
    cout << a;

    // Multiplying matrix
    matrix<int> c(2, 1, 15);
    cout << a * c << "\n";

    //
    return 0;
}
