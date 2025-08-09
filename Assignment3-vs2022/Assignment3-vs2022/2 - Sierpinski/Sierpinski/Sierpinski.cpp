/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include "simpio.h"
#include <vector>
using namespace std;

void drawTriangle(GPoint p1, GPoint p2, GPoint p3, GWindow &window) {
    window.drawLine(p1, p2);
    window.drawLine(p2, p3);
    window.drawLine(p1, p3);
}

Vector<GPoint> calculatePoints(GPoint p1, GPoint p2, GPoint p3) {
    Vector<GPoint> result;
    result += {0, 0};
    result += {0, 0};
    result += {0, 0};
    GPoint temp1 = p1;
    result[0] = { p1.getX() / 2 + p2.getX() / 2, p1.getY() / 2 + p2.getY() / 2 };
    result[1] = { p2.getX() / 2 + p3.getX() / 2,  p2.getY() / 2 + p3.getY() / 2 };
    result[2] = { temp1.getX() / 2 + p3.getX() / 2, temp1.getY() / 2 + p3.getY() / 2 };
    return result;
}

void drawSierpinskiTriangle(int spModul, GWindow& window, GPoint p1, GPoint p2, GPoint p3) {
    if (spModul == 0) return;
    Vector <GPoint> newTrianglePoints = calculatePoints(p1, p2, p3);
    drawTriangle(p1, p2, p3, window);
    drawSierpinskiTriangle(spModul - 1, window, p1, newTrianglePoints[0], newTrianglePoints[2]);
    drawSierpinskiTriangle(spModul - 1, window, p2, newTrianglePoints[1], newTrianglePoints[0]);
    drawSierpinskiTriangle(spModul - 1, window, p3, newTrianglePoints[2], newTrianglePoints[1]);
}

int main() {
    int spModul = getInteger("Enter sierpinski modul: ");
    int size = getInteger("Enter size of triangle's side: ");
    GWindow window;
    GPoint p1(window.getWidth() / 2 - size / 2, window.getHeight() / 2 + size / (2 * sqrt(3)));
    GPoint p2(window.getWidth() / 2 + size / 2, window.getHeight() / 2 + size / (2 * sqrt(3)));
    GPoint p3(window.getWidth() / 2, window.getHeight() / 2 - size / sqrt(3));
    drawTriangle(p1, p2, p3, window);
    drawSierpinskiTriangle(spModul, window, p1, p2, p3);
    return 0;
}
