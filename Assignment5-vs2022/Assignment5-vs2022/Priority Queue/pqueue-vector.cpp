/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
}

int VectorPriorityQueue::size() {
	return vec.size();
}

bool VectorPriorityQueue::isEmpty() {
	return vec.size() == 0;
}

void VectorPriorityQueue::enqueue(string value) {
	vec += value;
}

string VectorPriorityQueue::peek() {
	if (vec.isEmpty()) {
		error("Error");
	}
	string min = vec[0];
	for(string elem : vec){
		if (elem < min) min = elem;
	}	
	return min;
}

string VectorPriorityQueue::dequeueMin() {
	if (vec.isEmpty()) {
		error("Error");
	}
	int minsInd = 0;
	string min = vec[0];
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] < min) {
			minsInd = i;
			min = vec[i];
		}
	}
	vec.remove(minsInd);
	return min;
}

