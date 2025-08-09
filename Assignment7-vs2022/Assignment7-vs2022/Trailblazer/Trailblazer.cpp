/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
using namespace std;

Vector<Loc> makePath(Loc curr, Loc start, Grid<double>& world, Map<Loc, Loc>& parent) {
    Vector<Loc> res;
    while (true) {
        if (curr == start) break;
        res += curr;
        curr = parent[curr];
    }
    res += start;
    reverse(res.begin(), res.end());
    return res;
}

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
             double heuristic(Loc start, Loc end, Grid<double>& world)) {

    Map<Loc, double> shortestCosts;
    Map<Loc, Loc> parent;
    TrailblazerPQueue<Loc> nodesQueue;

    colorCell(world, start, YELLOW);
    Set<Loc> storedNodes;
    storedNodes += start;
    shortestCosts[start] = 0.0;
    nodesQueue.enqueue(start, heuristic(start, end, world));
    parent[start] = start;

    while (!nodesQueue.isEmpty()) {
        Loc curr = nodesQueue.dequeueMin();
        colorCell(world, curr, GREEN);
        
        if (curr == end) {
            Vector<Loc> res = makePath(curr, start, world, parent);
            return res;
        }
        double currDist = shortestCosts[curr];
        
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (i == 0 && j == 0) continue;
                Loc newLoc = { curr.row + j , curr.col + i };
                
                if (newLoc.row < 0 || newLoc.row >= world.nRows || newLoc.col < 0 || newLoc.col >= world.nCols) continue;

                double distFromCurrToNew = currDist + costFn(curr, newLoc, world);

                if (!shortestCosts.containsKey(newLoc)) {
                    colorCell(world, newLoc, YELLOW);
                    shortestCosts[newLoc] = distFromCurrToNew;
                    parent[newLoc] = curr;
                    nodesQueue.enqueue(newLoc, shortestCosts[newLoc] + heuristic(newLoc, end, world));
                    storedNodes += newLoc;
                }
                else if(distFromCurrToNew < shortestCosts[newLoc]) {
                    shortestCosts[newLoc] = distFromCurrToNew;
                    parent[newLoc] = curr;
                    if(storedNodes.contains(newLoc))nodesQueue.decreaseKey(newLoc, distFromCurrToNew + heuristic(newLoc, end, world));
                }
            }
        }
    }
    return Vector<Loc>();
}

bool isInBounds(Loc& loc, int nRows, int nCols) {
    if (loc.row < 0 || loc.row >= nRows || loc.col < 0 || loc.col >= nCols) return false;
    return true;
}

TrailblazerPQueue<Edge> implementStructures(Map<Loc, int>& locToClusNum, Map<int, Set<Loc>>& clusNumToSet, int numRows, int numCols) {
    TrailblazerPQueue<Edge> q;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            Loc curr = { i,j };
            clusNumToSet[i * numCols + j] += curr;
            locToClusNum[curr] = i * numRows + j;
            Loc end1 = { i + 1, j };
            Loc end2 = { i, j + 1 };
            if (isInBounds(end1, numRows, numCols)) {
                Edge newEdge = {curr, end1};
                q.enqueue(newEdge, randomReal(0, 1));
            }
            if (isInBounds(end2, numRows, numCols)) {
                Edge newEdge = {curr, end2};
                q.enqueue(newEdge, randomReal(0, 1));
            }
        }
    }
    return q;
}

Set<Edge> createMaze(int numRows, int numCols) {
    Set<Edge> result;
    Map<Loc, int> locToClusNum;
    Map<int, Set<Loc>> clusNumToSet;
    TrailblazerPQueue<Edge> edgeQueue = implementStructures(locToClusNum, clusNumToSet, numRows, numCols);
    while (!edgeQueue.isEmpty()) {
        Edge curr = edgeQueue.dequeueMin();
        Loc start = curr.start;
        Loc end = curr.end;
        
        if (locToClusNum[start] == locToClusNum[end]) continue;

        int startInt = locToClusNum[start];
        int endInt = locToClusNum[end];

        for (Loc loc : clusNumToSet[startInt]) {
            locToClusNum[loc] = endInt;
            clusNumToSet[endInt] += loc;
        }
        clusNumToSet.remove(startInt);
        result += curr;
    }

    return result;
	error("createMaze is not implemented yet.");
    return Set<Edge>();
}
