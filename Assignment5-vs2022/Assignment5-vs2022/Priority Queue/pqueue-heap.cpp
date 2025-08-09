/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	allocLength = 4;
	logLength = 0;
	arr = new string[allocLength];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] arr;
}

int HeapPriorityQueue::size() {
	return logLength;
}

bool HeapPriorityQueue::isEmpty() {
	return (logLength == 0); 
}

void HeapPriorityQueue::enqueue(string value) {
	if (allocLength == logLength) grow();
	arr[logLength] = value;
	logLength += 1;
	bubbleUp(logLength - 1);
}

string HeapPriorityQueue::peek() {
	if (isEmpty()) {
		error("Error");
	}
	return arr[0];
}

string HeapPriorityQueue::dequeueMin() {
	string min = peek();
	arr[0] = arr[logLength - 1];
	arr[logLength-1] = min;
	logLength -= 1;
	bubbleDown(0);
	return min;
}

void HeapPriorityQueue::grow() {
	allocLength *= 2;
	string* bigArr = new string[allocLength];
	for (int i = 0; i < logLength; i++) {
		bigArr[i] = arr[i];
	}
	delete[] arr;
	arr = bigArr;
}

void HeapPriorityQueue::bubbleUp(int index) {
	if (index == 0) return;
	int parent = detectParent(index);
	if (arr[index] < arr[parent]) {
		string tmp = arr[index];
		arr[index] = arr[parent];
		arr[parent] = tmp;
		bubbleUp(parent);
	}
}

void HeapPriorityQueue::bubbleDown(int index) {
	int minChildIndex = detectMinChild(index);
	if (minChildIndex == -1) return;
	if (arr[index] > arr[minChildIndex]) {
		string tmp = arr[index];
		arr[index] = arr[minChildIndex];
		arr[minChildIndex] = tmp;
		bubbleDown(minChildIndex);
	}
}

int HeapPriorityQueue::detectParent(int index) {
	int parent = 0;
	if (index % 2 == 0) {
		parent = index / 2 - 1;
	}
	else {
		parent = (index - 1) / 2;
	}
	return parent;
}

int HeapPriorityQueue::detectMinChild(int index) {
	int firstChild = (index + 1) * 2 - 1;
	int secondChild = (index + 1) * 2;
	if (firstChild >= logLength) return -1;
	int minChildIndex = 0;
	if (secondChild >= logLength) {
		minChildIndex = firstChild;
	}
	else {
		if (arr[firstChild] < arr[secondChild]) {
			minChildIndex = firstChild;
		}
		else {
			minChildIndex = secondChild;
		}
	}
	return minChildIndex;
}
