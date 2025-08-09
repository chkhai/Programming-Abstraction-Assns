/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);

void undoTheMove(Set<string>& cities, Set<string>& chosenCities, Vector< Set<string> >& result);

void implementCities(Set<string> &cities, Vector<Set<string>> & locations);

int main() {
    Set<string> cities;
    Vector<Set<string>> locations;
    Vector<Set<string>> result;
    implementCities(cities, locations);
    int numHospitals = getInteger("Enter the number of hospitals: ");
    while (numHospitals < 0) {
        numHospitals = getInteger("The number of hospitals can't be negative: ");
    }
    if (canOfferUniversalCoverage(cities, locations, numHospitals, result)) {
        cout << "Full coverage will be provided!\n";
        cout << result.toString() << endl;
    }
    else {
        cout << "Full coverage can't be provided!" << endl;
    }
    return 0;
}

void implementCities(Set<string>& cities, Vector<Set<string>>& locations) {
    cities += "A", "B", "C", "D", "E", "F";
    Set<string> citiesCovered1;
    Set<string> citiesCovered2;
    Set<string> citiesCovered3;
    Set<string> citiesCovered4;
    citiesCovered1 += "A", "B", "C";
    citiesCovered2 += "A", "C", "D";
    citiesCovered3 += "B", "F";
    citiesCovered4 += "C", "E", "F";
    locations += citiesCovered1, citiesCovered2, citiesCovered3, citiesCovered4;
}

void undoTheMove(Set<string>& cities, Set<string>& chosenCities, Vector< Set<string> >& result) {
    for (string elem : chosenCities) {
        cities.add(elem);
    }
    result.remove(result.size() - 1);
}

bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations, int numHospitals,
    Vector< Set<string> >& result) {
    if (cities.size() == 0) return true;
    if (locations.size() == 0) return false;
    if (numHospitals == 0) return false;
    Set<string> chosenCities;
    Set<string> lastHosp = locations[locations.size() - 1];
    locations.remove(locations.size() - 1);
    for(string elem : lastHosp){
        if (cities.contains(elem)) {
            cities.remove(elem);
            chosenCities.add(elem);
        }
    }
    result += lastHosp;
    if (canOfferUniversalCoverage(cities, locations, numHospitals - 1, result)) return true;
    undoTheMove(cities, chosenCities, result);
    if (canOfferUniversalCoverage(cities, locations, numHospitals, result)) {
        locations += lastHosp;
        return true;
    }
    locations += lastHosp;
    return false;
}

