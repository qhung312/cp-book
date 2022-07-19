#include <bits/stdc++.h>
#include "bit.h"
using namespace std;

int main() {
    fenwick<int> f(5);
    f.add(0, 1);
    f.add(4, 5);
    printf("Test 1: %d (expected 1)\n", f.rangeSum(0, 1));
    printf("Test 2: %d (expected 6)\n", f.rangeSum(0, 4));

    reverse_fenwick<int> f2(6);
    f2.add(3, 10);
    f2.add(0, 2);
    f2.add(5, 20);
    printf("Test 3: %d (expected 12)\n", f2.rangeSum(0, 3));
    printf("Test 4: %d (expected 30)\n", f2.rangeSum(2, 5));
    return 0;
}
