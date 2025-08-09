/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = NULL;
	length = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	while (head != NULL) {
		Cell* tmp = head;
		head = head->next;
		delete tmp;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return length;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return (length == 0);
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	Cell* newCell = new Cell;
	newCell->val = value;
	newCell->next = NULL;
	newCell->prev = NULL;
	if (isEmpty()) {
		head = newCell;
		length++;
		return;
	}
	newCell->next = head;
	head->prev = newCell;
	head = newCell;
	length++;
}

string DoublyLinkedListPriorityQueue::peek() {
	if (isEmpty()) error("Error");
	string min = head->val;
	Cell* curr = head;
	while (curr != NULL) {
		if (curr->val < min) {
			min = curr->val;
		}
		curr = curr->next;
	}
	return min;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if (isEmpty()) error("Error");
	string min = head->val;
	Cell* minCell = head;
	Cell* curr = head;
	while (curr != NULL) {
		if (curr->val < min) {
			min = curr->val;
			minCell = curr;
		}
		curr = curr->next;
	}
	if (minCell->prev == NULL) {
		head = minCell->next;
	}
	else {
		minCell->prev->next = minCell->next;
	}
	if (minCell->next != NULL) {
		minCell->next->prev = minCell->prev;
	}
	delete minCell;
	length--;
	return min;
}

