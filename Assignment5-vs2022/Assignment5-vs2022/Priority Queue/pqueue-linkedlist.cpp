/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = NULL;
	length = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while (head != NULL) {
		Cell* tmp = head;
		head = head->next;
		delete tmp;
	}
}

int LinkedListPriorityQueue::size() {
	return length;
}

bool LinkedListPriorityQueue::isEmpty() {
	return (length == 0);
}

void LinkedListPriorityQueue::enqueue(string value) {
	length++;
	Cell* newCell = new Cell;
	newCell->val = value;
	newCell->next = NULL;
	if (length == 1) {
		head = newCell;
		return;
	}
	string first = peek();
	Cell* curr = head;
	while (curr != NULL) {
		Cell* nextCell = curr->next;
		if (newCell->val < first) {
			newCell->next = head;
			head = newCell;
			return;
		}
		if (nextCell == NULL) {
			curr->next = newCell;
			return;
		}
		if (newCell->val >= curr->val and newCell->val < nextCell->val) {
			newCell->next = nextCell;
			curr->next = newCell;
			return;
		}
		curr = curr->next;
	}
}

string LinkedListPriorityQueue::peek() {
	if (isEmpty()) error("Error");
	return head->val;
}

string LinkedListPriorityQueue::dequeueMin() {
	string min = peek();
	length--;
	Cell* tmp = head;
	head = head->next;
	delete tmp;
	return min;
}

