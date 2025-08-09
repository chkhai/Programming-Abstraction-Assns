/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "fstream";
#include "simpio.h"
#include "tokenscanner.h"
using namespace std;

const double c0 = -15.9;
const double c1 = 0.39;
const double c2 = 11.8;

/* Function prototypes */
struct stats;
stats findOutStats(string filename);
int countSyllables(string str);
bool isSyllable(char ch);


struct stats {
    int numWords = 0;
    int numSentences = 0;
    int numSyllables = 0;
    double gradeLevel = 0.0;
};

/*
* Opens file, reads the information and calculates the number of
* sentences, words and syllables. After that, we close the file and
* return the result.
*/
stats findOutStats(string filename) {
    stats result;
    ifstream input;
    string line;
    input.open(filename);
    while (!input) {
        cout << "Name is unvalid!" << endl;
        filename = getLine("Enter valid one! ");
        input.open(filename);
    }
    while (getline(input, line)) {
        TokenScanner scanner(line);
        scanner.ignoreWhitespace();
        scanner.addWordCharacters("'");
        scanner.addWordCharacters("-");
        while (scanner.hasMoreTokens()) {
            string tok = scanner.nextToken();
            if (isalpha(tok[0])) {
                result.numWords++;
                int syllables = countSyllables(tok);
                result.numSyllables += syllables;
            }
            else if (tok[0] == '.' || tok[0] == '!' || tok[0] == '?') {
                result.numSentences++;
            }
        }
    }
    if (result.numSentences == 0) result.numSentences == 1;
    if (result.numWords == 0) result.numWords == 1;
    result.gradeLevel = c0 + c1 * result.numWords / result.numSentences + c2 * result.numSyllables / result.numWords;
    input.close();
    return result;
}

/*
* This function counts syllables in one word.
*/
int countSyllables(string str) {
    int result = 0;
    for (int i = 0; i < str.length()-1; i++) {
        if (isSyllable(str[i]) && !isSyllable(str[i + 1])) {
            result++;
        }
    }
    if (isSyllable(str[str.length() - 1]) && str[str.length() - 1] != 'e') result++;
    if (result == 0) result = 1;
    return result;
}

/*
* This boolean detects whether character is syllable or not.
*/
bool isSyllable(char ch) {
    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'y'
        || ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' || ch == 'Y') {
        return true;
    }
    return false;
}

int main() {
    string filename = getLine("Enter file name to count its grade level: ");
    stats grade = findOutStats(filename);
    if (grade.numSentences != 0 && grade.numWords != 0 && grade.numSyllables != 0) {
        cout << "Words: "  << grade.numWords << endl;
        cout << "Syllables: " << grade.numSyllables << endl;
        cout << "Sentences: " << grade.numSentences << endl;
        cout << "The Flesch-Kincaid grade level of this text is " << grade.gradeLevel << endl;
    }
    else {
        cout << "File wasn't found." << endl;
    }
    return 0;
}


