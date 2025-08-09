/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include <vector>
#include "console.h"
#include "lexicon.h"
#include "simpio.h"
#include "queue.h"

using namespace std;

/*  function prototypes */
Vector<string> findPath(string start, string destination, Lexicon &listOfWords);
Set<string> findOneLetDiffWords(Lexicon& listOfWords, string word);
void printOutput(string start, string destination, Lexicon& lexicon);
pair<string, string> chooseWords(Lexicon& lexicon);
void playTheGame(Lexicon& lexicon);

int main() {
    Lexicon listOfWords("EnglishWords.dat");
    playTheGame(listOfWords);
    return 0;
}

void playTheGame(Lexicon& lexicon) {
    while (true) {
        pair<string, string> startAndDestination = chooseWords(lexicon);
        string start = startAndDestination.first;
        string destination = startAndDestination.second;
        if (start == "") break;
        if (start.length() == destination.length()) {
            printOutput(start, destination, lexicon);
        }
        else {
            cout << "No Ladder Found!\n";
        }
    }
}

void printOutput(string start, string destination, Lexicon &lexicon) {
    Vector<string> path = findPath(start, destination, lexicon);
    if (!path.isEmpty()) {
        for (int i = 0; i < path.size(); i++) {
            if (i != path.size() - 1) {
                cout << path[i] << " -> ";
            }
            else {
                cout << path[i] << "\n";
            }
        }
    }
    else {
        cout << "No Ladder Found!\n";
    }
}

pair<string, string> chooseWords(Lexicon& lexicon) {
    string first = getLine("Enter start word (RETURN to quit): ");
    if (first == "") return {"", ""};
    string last = getLine("Enter destination word: ");
    while (!lexicon.contains(first) || !lexicon.contains(last)) {
        first = getLine("Enter valid input (RETURN to quit): ");
        if (first == "") return {"", ""};
        last = getLine("Enter destination word: ");
    }
    return {first, last};
}


Vector<string> findPath(string start, string destination, Lexicon &lexicon) {
    Vector<string> path;
    Queue<Vector<string>> allPaths;
    Set<string> savedWords;
    savedWords.add(start);
    path.push_back(start);
    allPaths.enqueue(path);
    Vector<string> selectedLadder;
    while (!allPaths.isEmpty()) {
        selectedLadder = allPaths.dequeue();
        string last = selectedLadder[selectedLadder.size() - 1];
        if (last == destination) return selectedLadder;
        Set<string> oneLettDifWords = findOneLetDiffWords(lexicon, last);
        for(string elem : oneLettDifWords) {
            if (!savedWords.contains(elem)) {
                savedWords.add(elem);
                Vector<string> copy(selectedLadder);
                copy.push_back(elem);
                allPaths.enqueue(copy);
            }
        }
    }
    path.clear();
    return path;
}

Set<string> findOneLetDiffWords(Lexicon& lexicon, string word) {
    Set<string> list;
    for (int i = 0; i < word.length(); i++) {
        for (int j = 0; j < 26; j++) {
            char ch = 'a' + j;
            string copyString = word;
            copyString[i] = ch;
            if (lexicon.contains(copyString)) {
                list.add(copyString);
            }
        }
    }
    return list;
}