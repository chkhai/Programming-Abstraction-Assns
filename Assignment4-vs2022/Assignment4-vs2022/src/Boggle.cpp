/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
Grid<char> generateCubes(int rows, int cols);
void playTheGame();
Grid<char> createGridFromUsersInput(string chars);
void usersMove(Grid<char>& letters, Lexicon& lexicon, Set<string>& usersFoundWords, int& usersPoints);
void computersMove(Grid<char>& letters, Lexicon& lexicon, Set<string>& usersFoundWords, int& computersPoints);
bool wordIsFoundableOnGrid(string word, Grid<char>& letters);
void wordIsCorrect(Vector<pair<int, int>>& routes, string word);
bool positionIsValid(pair<int, int> newPosition, Grid<char>& letters, Vector<pair<int, int>>& routes);
Vector<pair<int, int>> generateNextLocations(Grid<char>& letters, pair<int, int> location, Vector<pair<int, int>>& routes);
bool findTheRouteIfPossible(string target, Grid<char>& letters, pair<int, int> currPos, Vector<pair<int, int>>& routes);
void findAllWords(Grid<char>& letters, Lexicon& lexicon, Set<string> &allWords);

/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
    giveInstructions();
    while (true) {
        playTheGame();
        string playAgain = getLine("Type 'no' if you want to stop playing, anything else to continue: ");
        if (playAgain == "no") {
            cout << "Thanks for playing!" << endl;
            break;
        }
    }

    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

/* Function: generateCubes
* 
* This function generate random letters on the board.
*/
Grid<char> generateCubes(int rows, int cols) {
    Grid<char> result(rows, cols);
    Vector<string> copy;
    for (int i = 0; i < rows*cols; i++) {
        copy += STANDARD_CUBES[i];
    }
    for (int i = 0; i < copy.size(); i++) {
        int x = randomInteger(0,copy.size()-1);
        string temp = copy[x];
        copy[x] = copy[i];
        copy[i] = temp;
    }
    for (int i = 0; i < result.nRows; i++) {
        for (int j = 0; j < result.nCols; j++) {
            int random = randomInteger(0,5);
            result[i][j] = copy[rows * i + j][random];
            labelCube(i, j, result[i][j]);
        }
    }
    return result;
}

/* Function: createGridFromUsersInput 
* 
* If user decides to configure board by themselves, this method
* is called and grid is created.
*/
Grid<char> createGridFromUsersInput(string chars) {
    Grid<char> result(4,4);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = chars[4 * i + j];
            labelCube(i, j, result[i][j]);
        }
    }
    return result;
}

/* Function: playTheGame
* 
*  Main function for playing the game. We ask user about preferences
*  and then we start game. 
*/
void playTheGame() {
    string config = getLine("Do you want computer to randomise cubes('yes' or 'no'): ");
    Grid<char> letters;
    drawBoard(4, 4);
    while (config != "yes" and config != "no") {
        config = getLine("Please enter 'yes' or 'no': ");
    }
    if (config == "yes") {
        letters = generateCubes(4, 4);
    }
    else if (config == "no") {
        string chars = getLine("Please enter 16-character string to set up the board. The first 4 letters are the first row of the cubes, second 4 letter are second row and so on: ");
        letters = createGridFromUsersInput(toUpperCase(chars));
    }
    Lexicon lexicon("EnglishWords.dat");
    Set<string> usersFoundWords;
    int usersPoints = 0;
    int computersPoints = 0;
    usersMove(letters, lexicon, usersFoundWords, usersPoints);
    computersMove(letters, lexicon, usersFoundWords, computersPoints);
    if (computersPoints > usersPoints) {
        cout << "Computer won with total points of " << computersPoints << "!" << endl;
    }
    else if (computersPoints < usersPoints) {
        cout << "You won with total points of " << usersPoints << "!" << endl;
    }
    else {
        cout << "The game ended in a draw!" << endl;

    }
}

/*
*  Function: computersMove
* 
*  We find all words possible and then we write them on board.
*/
void computersMove(Grid<char>& letters, Lexicon& lexicon, Set<string>& usersFoundWords, int& computersPoints) {
    Set<string> allWords;
    findAllWords(letters, lexicon, allWords);
    for (string elem : allWords) {
        if (usersFoundWords.contains(elem)) continue;
        computersPoints += elem.length() - 3;
        recordWordForPlayer(elem, COMPUTER);
    }
}

/* Function: findWordsStartingWithPref
* 
* This function is very similar to user's recursive function. We have 2 base cases. 
* If lexicon doesn't contain word with current prefix we return. And if lexicon contains
* word, which's length is more than 3 we add this word to all words set. After that we
* generate next possible moves. And for each move we create new prefix, and call the same
* function for all of them. After for loop we remove last element from positions vector.
*/
void findWordsStartingWithPref(string pref, Grid<char>& letters, Lexicon& lexicon, Set<string>& allWords, pair<int, int> location, Vector<pair<int, int>> wordsRoute) {
    if (!lexicon.containsPrefix(pref)) return;
    if (lexicon.contains(pref) and pref.length() >= 4 and !allWords.contains(pref)) {
        allWords.add(pref);
    }
    wordsRoute.add(location);
    Vector<pair<int, int>> nextLocations = generateNextLocations(letters, location, wordsRoute);
    for (pair<int, int> pair : nextLocations) {
        string elem = pref + letters[pair.first][pair.second];
        findWordsStartingWithPref(elem, letters, lexicon, allWords, pair, wordsRoute);
    }
    wordsRoute.remove(wordsRoute.size()-1);
}

/* Function: findAllWords
* 
* This method finds all words for computer's turn. We use containsPrefix method 
* for every single letter on the board and we generate all words by calling 
* findWordsStartingWithPref method, which is the main recursive function for computer's turn.
*/
void findAllWords(Grid<char>& letters, Lexicon& lexicon, Set<string>& allWords) {
    for (int i = 0; i < letters.numRows(); i++) {
        for(int j = 0; j < letters.numCols(); j++){
            string pref = letters[i][j] + "";
            Vector<pair<int, int>> wordsRoute;
            pair<int, int> location;
            location.first = i;
            location.second = j;
            findWordsStartingWithPref(pref, letters, lexicon, allWords, location, wordsRoute);
        }
    }
}

/* Function: positionIsValid
* 
* This function is called in generateNextLocations function. We simply check if position is in the bounds 
* of the grid. And we also check if this position has already been used.
*/
bool positionIsValid(pair<int, int> newPosition, Grid<char>& letters, Vector<pair<int, int>>& routes) {
    if (newPosition.first < 0 || newPosition.first > letters.numCols() - 1) return false;
    if (newPosition.second < 0 || newPosition.second > letters.numRows() - 1) return false;
    for (int i = 0; i < routes.size(); i++) {
        if (routes[i] == newPosition) return false;
    }
    return true;
}

/* Function: generateNextLocations
* 
* This function generates next possible locations.
*/
Vector<pair<int, int>> generateNextLocations(Grid<char>& letters, pair<int, int> location, Vector<pair<int, int>>& routes) {
    Vector<pair<int, int>> nextLocations;
    pair<int, int> newPosition;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 and j == 0) continue;
            newPosition.first = location.first + i;
            newPosition.second = location.second + j;
            if(positionIsValid(newPosition, letters, routes)){
                nextLocations.add(newPosition);
            }
        }
    }
    return nextLocations;
}

/* Function: findTheRouteIfPossible
* 
* This is the main recursive function for users move. Firstly, we check the base cases. 
* Then we generate next possible moves. And after generating them, for all of them
* we call same function. We pass them target's substring and possible location. If any of
* them is true we return true. If we passed for loop, this means than none of the possible moves
* were correct, so we remove last element from vector of positions and return true.
* 
*/
bool findTheRouteIfPossible(string target, Grid<char>& letters, pair<int, int> currPos, Vector<pair<int, int>>& routes) {
    if (target.length() == 0) return true;
    if (target[0] != letters[currPos.first][currPos.second]) return false;
    routes.add(currPos);
    Vector<pair<int, int>> nextPossibleMoves = generateNextLocations(letters, currPos, routes);
    for(pair<int,int> loc : nextPossibleMoves){
        if(findTheRouteIfPossible(target.substr(1), letters, loc, routes)) return true;
    }
    routes.remove(routes.size() - 1);
    return false;
}

/* Function: wordIsCorrect
* 
* This function is called after word was found by recursive search. Firstly, we highlight cubes
* which add up to target word, and after 300 milisecond we erase them.
*/
void wordIsCorrect(Vector<pair<int, int>>& routes, string word) {
    recordWordForPlayer(word, HUMAN);
    for (int i = 0; i < routes.size(); i++) {
        highlightCube(routes[i].first, routes[i].second, true);
    }
    pause(300);
    for(int i = 0 ; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            highlightCube(i, j, false);
        }
    }
}

/* Function: wordIsFoundableOnGrid
* 
* Checks every single charachter on board, if any of the letters on board matches target's first character, we 
* call recursive function to dedicate if this word is achievable. If none of characters are target's first letter,
* we return false;
*/
bool wordIsFoundableOnGrid(string target, Grid<char>& letters) {
    Vector<pair<int, int>> routes;
    pair<int, int> location;
    bool isRightWay = false;
    for (int i = 0; i < letters.numRows(); i++) {
        for (int j = 0; j < letters.numCols(); j++) {
            if (target[0] != letters[i][j]) continue;
            location.first = i;
            location.second = j;
            isRightWay = findTheRouteIfPossible(target, letters, location, routes);
            if (!isRightWay) continue;
            wordIsCorrect(routes, target);
            return true;
        }
    }
    return false;
}

/* Function: usesMove
* 
* Checks users input and calculates score if the word is right.
*/
void usersMove(Grid<char>& letters, Lexicon& lexicon, Set<string>& usersFoundWords, int& usersPoints) {
    while (true) {
        string word = getLine("Enter a word(Hit RETURN if you don't have any words): ");
        if (word == "") {
            cout << "Now it's my turn! :)" << endl;
            break;
        }
        if (usersFoundWords.contains(toUpperCase(word))) {
            cout << "You've already guessed that word!" << endl;
            continue;
        }
        if (word.length() < 4 || !lexicon.contains(toUpperCase(word))) {
            cout << "Try valid input!" << endl;
            continue;
        }
        if (wordIsFoundableOnGrid(toUpperCase(word), letters)) {
            usersFoundWords += toUpperCase(word);
            usersPoints += word.length() - 3;
        }
        else {
            cout << "Word isn't on the board!" << endl;
        }
    }
}

// [TODO: Fill in the rest of the code]
