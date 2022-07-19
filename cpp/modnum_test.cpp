#include <bits/stdc++.h>
#include "modnum.h"
using namespace std;

int main() {
    // Printing a simple value
    modnum printValue(100);
    printf("Test 1: %d (expected 100)\n", printValue.val());
    printf("Test 2: %d (expected 999999907)\n", (-printValue).val());

    // using +=, -=, *=, /=
    modnum a(6);
    printf("Test 3: %d (expected 13)\n", (a += modnum(7)).val());

    // using +,-,*,/
    modnum b(13);
    printf("Test 4: %d (expected 33)\n", (b + modnum(20)).val());

    // using ++
    modnum c(40), d(50);
    d++;
    printf("Test 5: %d (expected 41)\n", (++c).val());
    printf("Test 6: %d (expected 51)\n", d.val());

    return 0;
}
