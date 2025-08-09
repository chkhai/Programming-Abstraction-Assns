/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include <vector>
#include <fstream>
#include <string>
#include "map.h"
#include "random.h"
using namespace std;

const int numOfWords = 2000;

/* Function prototypes*/
Map<string, Vector<char>> analyzeText(ifstream& fileReader, int markovModel);
string detectMostUsed(Map<string, Vector<char>>& frequencies);
string generateRandomText(Map<string, Vector<char>>& frequencies, string mostUsed);
ifstream openFile();
int getMarkovModel();

Map<string, Vector<char>> analyzeText(ifstream& fileReader, int markovModel) {
    Map<string, Vector<char>> frequencies;
    string str;
    char ch;
    for (int i = 0; i < markovModel; i++) {
        ch = fileReader.get();
        str += ch;
    }
    while (fileReader.get(ch)) {
        frequencies[str].push_back(ch);
        str = str.substr(1) + ch;
    }
    return frequencies;
}

string detectMostUsed(Map<string, Vector<char>>& frequencies) {
    string str = "";
    int max = 0;
    for(string elem : frequencies){
        if (frequencies[elem].size() > max) {
            max = frequencies[elem].size();
            str = elem;
        }
    }
    return str;
}

string generateRandomText(Map<string, Vector<char>>& frequencies, string mostUsed) {
    string res = mostUsed;
    for(int i = 0; i < numOfWords - mostUsed.length(); i++){
        if (frequencies[mostUsed].size() == 0) break;
        char ch = frequencies[mostUsed][randomInteger(0, frequencies[mostUsed].size()-1)];
        res += ch;
        mostUsed = mostUsed.substr(1) + ch;
    }
    return res;
}

ifstream openFile() {
    ifstream fileReader;
    string filename = getLine("Enter file name: ");
    fileReader.open(filename);
    while (!fileReader) {
        filename = getLine("File wasn't found! Enter valid file name: ");
        fileReader.open(filename);
    }
    return fileReader;
}

int getMarkovModel() {
    int num = getInteger("Enter markov model(1 to 10): ");
    while (num > 10 || num < 1) {
        num = getInteger("Number must be from one to ten! Enter new one: ");
    }
    return num;
}

int main() {
    ifstream fileReader = openFile();
    int markovModel = getMarkovModel();
    Map<string, Vector<char>> frequencies = analyzeText(fileReader, markovModel);
    string mostUsed = detectMostUsed(frequencies);
    string result = generateRandomText(frequencies, mostUsed);
    cout << result << endl;
    return 0;
}
