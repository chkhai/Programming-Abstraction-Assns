/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
    cout << stringToInt("18") << endl;
    cout << stringToInt("-15") << endl;
    cout << intToString(12) << endl;
    cout << intToString(-3) << endl;
    cout << intToString(6) << endl;
    return 0;
}

string intToString(int n) {
    if (n == 0) return "0";
    if (n < 0) {
        int nMod = -n;
        if (nMod < 10) return string("-") + char(nMod + '0');
        return string("-") + intToString(nMod / 10) + char(nMod % 10 + '0');
    }
    if (n < 10) return string("") + char(n + '0');
    return intToString(n / 10) + char(n % 10 + '0');
}

int stringToInt(string str) {
    if (str[0] == '-') {
        string strMod = str.substr(1);
        if (strMod.length() < 2) return -1 * (strMod[0] - '0');
        return -1 * (stringToInt(strMod.substr(0, strMod.length() - 1)) * 10 + strMod[strMod.length() - 1] - '0');
    }
    if (str.length() < 2) return str[0] - '0';
    return stringToInt(str.substr(0, str.length() - 1)) * 10 + str[str.length() - 1] - '0';
}

