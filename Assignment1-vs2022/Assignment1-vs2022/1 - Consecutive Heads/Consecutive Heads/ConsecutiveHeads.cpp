/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "vector.h"
#include "simpio.h"
#include "random.h"
using namespace std;

bool isThreeHeadsInARow(Vector<int> headsAndTails) {
    if (headsAndTails.size() < 3) return false;
    for (int i = 1; i < headsAndTails.size() - 1; i++) {
        if (headsAndTails[i - 1] == 1 && headsAndTails[i] == 1 && headsAndTails[i + 1] == 1) {
            return true;
        }
    }
    return false;
}

int main() {
    Vector<int> headsAndTails;
    int count = 0;
    while (true) {
        count++;
        int coin = randomInteger(0,1);
        headsAndTails.push_back(coin);
        if (coin == 1) {
            cout << "heads" << endl;
        }else {
            cout << "tails" << endl;
        }
        if (isThreeHeadsInARow(headsAndTails)) {
            cout << "It took " << count << " times to get 3 consecutive heads." << endl;
            break;
        }
    }
    return 0;
}
