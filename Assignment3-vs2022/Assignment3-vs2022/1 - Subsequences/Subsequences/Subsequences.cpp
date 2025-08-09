/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string or not.
 */
bool isSubsequence(string text, string subsequence);

int main() {
    while (true) {
        string text = getLine("Enter text(RETURN to quit): ");
        if (text == "") { 
            cout << "Thanks for playing!" << endl;
            break; 
        }
        string sub = getLine("Enter text to determine if its subsequence: ");
        if (isSubsequence(text, sub)) {
            cout << true << endl;
        }
        else {
            cout << false << endl;
        }
    }
    return 0;
}

bool isSubsequence(string text, string subsequence) {
    if (subsequence.length() == 0) return true;
    if (subsequence.length() > text.length()) return false;
    char textCh = text[1];
    char subCh = subsequence[1];
    if ((textCh == subCh)) return isSubsequence(text.substr(1), subsequence.substr(1));
    return isSubsequence(text.substr(1), subsequence);
}
