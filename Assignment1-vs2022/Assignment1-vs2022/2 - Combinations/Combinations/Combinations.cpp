/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

int cFunction(int n, int k) {
    if (n == k || k == 0) return 1;
    return cFunction(n - 1, k - 1) + cFunction(n-1, k);
}

int main() {
    cout << "Pascal triangle simulator!" << endl;
    int n = getInteger("Enter n: ");
    int k = getInteger("Enter k: ");
    cout << "C(n,k) is " << cFunction(n,k) << endl;
    return 0;
}
