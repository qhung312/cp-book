#include <bits/stdc++.h>
#include "dsu.h"
using namespace std;

int main() {
    dsu d(5);
    d.join(0, 1);
    d.join(2, 3);
    printf("Test 1: %d (expected 3)\n", d.getCCCount());
    printf("Test 2: %d (expected 2)\n", d.getMaxSize());
    printf("Test 3: %d (expected 2)\n", d.sizeOf(1));
    printf("Test 4: %d (expected 0)\n", d.same(0, 4));
    printf("Test 5: %d (expected 1)\n", d.same(0, 1));
    return 0;
}
