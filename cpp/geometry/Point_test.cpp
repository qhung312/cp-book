#include <bits/stdc++.h>
#include "Point.h"
using namespace std;
using ll = long long;

int main() {
    Point<int> a(2, 3), b(3, 4);
    cout << "Test 1 (expected (5,7)): " << (a + b) << "\n";
    cout << "Test 2 (expected (6,9)): " << a*3 << "\n";
    return 0;
}
