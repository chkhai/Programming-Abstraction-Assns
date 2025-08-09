/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

Set<string> findRnas(string protein, Map<char, Set<string> >& codons);

bool isNotProtein(string protein, Map<char, Set<string> >& codons);

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();
    string protein = getLine("Enter protein to detect its codons: ");
    listAllRNAStrandsFor(protein, codons);
    /* [TODO: Implement this!] */
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}

Set<string> findRnas(string protein, Map<char, Set<string> >& codons) {
    Set<string> result;
    if(protein.length() == 1){
        for (string elem : codons.get(protein[0])) {
            result.add(elem);
        }
        return result;
    }
    string withoutFirst = protein.substr(1);
    Set<string> allButFirst = findRnas(withoutFirst, codons);
    for (string elem1 : allButFirst) {
        for (string elem2 : codons.get(protein[0])) {
            string res = elem2 + elem1;
            result.add(res);
        }
    }
    return result;
}

bool isNotProtein(string protein, Map<char, Set<string> >& codons) {
    for (int i = 0; i < protein.length(); i++) {
        if (!codons.containsKey(protein[i])) return true;
    }
    return false;
}

void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons) {
    if (protein.length() == 0 || isNotProtein(protein, codons)) {
        cout << "No RNA's Found!" << endl;  
        return;
    }
    Set<string> rnas = findRnas(protein, codons);
    for(string elem : rnas){
        cout << elem << endl;
    }
 }
