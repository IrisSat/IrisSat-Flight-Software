//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// MBSATS 2019-2020
//
// Repository:
//  ManitobaSat-Flight-Software
//
// File Description:
//  Priority queue for any payload.
//
// History
// 2019-10-01 Eric Kapilik
// - Created. See https://www.geeksforgeeks.org/priority-queue-using-linked-list/.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "priority_queue.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// ENUMS AND ENUM TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// STRUCTS AND STRUCT TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct node {
	unsigned long priority; // Lower values indicate higher priority
	struct node* next;
	void* data;
} Node;
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Create new node for linked list with given data pointer and given priority.
//
// Parameters:
//	data - the data (stored as pointer)
//  priority - the priority of the node, lower number is higher priority. (i.e., 0 is highest priority)
// Returns:
//  Pointer to a new node structure
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
Node* newNode(void* data, unsigned long priority);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Return the highest priority value without removing it from the queue.
//
// Parameters:
//	head - a pointer to a pointer containing head
// Returns:
//  The data value of the highest priority node without removing it from the queue.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void* peek(Node** head);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Removes the node with highest priority from the queue.
//
// Parameters:
//	head - a pointer to a pointer containing head
// Returns:
//  VOID
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void pop(Node** head);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Checks if the list is empty. 1 if empty, 0 otherwise.
//
// Parameters:
//	head - a pointer to a pointer containing head
// Returns:
//  int - 1 if empty, 0 otherwise
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int isEmpty(Node** head);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Pushes a node with data [d] and priority [p] onto priority queue [head].
//
// Parameters:
//	head - a pointer to a pointer containing head
//	d	 - a pointer to the data to store
//	p	 - priority of node (lower priority value will be higher in queue, i.e. 0 is highest priority)
// Returns:
//  The data value of the highest priority node without removing it from the queue.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void push(Node** head, void* d, unsigned long p);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void* peek(Node** head){
	return (*head)->data;
}

void pop(Node** head){
	Node* temp = *head;
	(*head) = (*head)->next;
	free(temp);
}

void push(Node** head, void* d, unsigned long p){
	Node* start = (*head);

	// Create new node
	Node* temp = newNode(d, p);

	// Special case: The head of the list has lesser priority
	// than the new node. So insert new node before head node
	// and change head node.
	if ((*head)->priority > p){
		//Insert new Node before head
		temp->next = *head;
		(*head) = temp;
	}
	else { // The head of the list is higher priority. (i.e. lower priority number - e.g. 0 is highest priority)
		// Traverse the list and find a position to insert new node
		while(start->next != NULL &&
			  start->next->priority < p){
			start = start->next; // traverse list
		}

		// Either we are at the end of the list or at required position
		temp->next = start->next;
		start->next = temp;
	}
}

int isEmpty(Node** head){
	return (*head) == NULL;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

Node* newNode(void* data, unsigned long priority){
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->priority = priority;
	temp->next = NULL;

	return temp;
}

void vTaskTest_Priority_Queue(void *pvParameters){
	// Step through this task with a debugger and observe variable values to verify function.
	int data1=123, data2=123, data3=123, data4=123;  // data values
	int* data1p = &data1;// pointers to data values
	int* data2p = &data2;
	int* data3p = &data3;
	int* data4p = &data4;
	void* temp; // temp variable to observe data value

	// Order should be (HEAD)->1,2,3,4
	Node* pq = newNode(data2p, 2);
	push(&pq, data3p, 3);
	push(&pq, data4p, 4);
	push(&pq, data1p, 1);

	while(!isEmpty(&pq)){
		temp = peek(&pq);
		pop(&pq);
	}

	vTaskDelete( NULL ); // End testing task
}
