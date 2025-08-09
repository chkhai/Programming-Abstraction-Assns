/*
 * File: KarelGoesHome.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Karel Goes Home
 * warmup problem for Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
//#include "console.h"
using namespace std;

/* Given a street number and avenue number, which are 1-indexed,
 * returns the number of paths Karel can take back home that only
 * moves left or down.
 */
int numPathsHome(int street, int avenue);

int main() {
    cout << numPathsHome(2, 3) << "\n";
    cout << numPathsHome(1, 5) << "\n";
    cout << numPathsHome(2, 4) << "\n";
    cout << numPathsHome(3, 4) << "\n";
    cout << numPathsHome(5, 6) << "\n";
    return 0;
}

int numPathsHome(int street, int avenue) {
    if (street == 1 and avenue == 1) return 0;
    if (street == 1) return 1;
    if (avenue == 1) return 1;
    if (street != 1 and avenue != 1) return 2 + numPathsHome(street , avenue - 1) + numPathsHome(street - 1, avenue);
}
