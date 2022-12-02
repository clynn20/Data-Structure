/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Chialing Hu
 * Email: huchia@oregonstate.edu
 */

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "dynarray.h"
#include "pq.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 * in addition, you want to define an element struct with both data and priority, 
 * corresponding to the elements of the priority queue. 
 */
struct pq{
	struct dynarray* heap;
};

struct element{
	int priority;
	void* data;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	struct pq* pq = malloc(sizeof(struct pq));
	pq->heap = dynarray_create();
  return pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	assert(pq);
	dynarray_free(pq->heap);
	free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	assert(pq);	
  return dynarray_length(pq->heap)==0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, higher priority
 * values are given precedent, and higher place in the queue.  In other words, the
 * element in the priority queue with the highest priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   data - the data value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, higher priority values
 *     should correspond to the first elements.  In other words,
 *     the element in the priority queue with the highest priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* data, int priority) {
	assert(pq);
	struct element* ele = malloc(sizeof(struct element));
	ele->data=data;
	ele->priority=priority;
	dynarray_insert(pq->heap,-1,ele);
	int curr_index = dynarray_length(pq->heap)-1;
	int par_index = curr_index/2;
	int par_priority=((struct element*)dynarray_get(pq->heap,par_index))->priority;
	while(priority>par_priority){
	//swap the element and heapify
		swap_value(pq->heap,curr_index,par_index);
		curr_index = par_index;
		par_index = curr_index/2;
		par_priority = ((struct element*)dynarray_get(pq->heap,par_index))->priority;
	}
}
void swap_value(struct dynarray* arr,int indexone, int indextwo){
	struct element *eleone = dynarray_get(arr,indexone);
	struct element *eletwo = dynarray_get(arr,indextwo);
	dynarray_set(arr,indexone,eletwo);
	dynarray_set(arr,indextwo,eleone);
}

/*
 * This function should return the data of the first element in a priority
 * queue, i.e. the data associated with the element with highest priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the data of the first item in pq, i.e. the item with
 *   max priority value.
 */
void* pq_max(struct pq* pq) {
	assert(pq);
	struct element* max_ele = dynarray_get(pq->heap,0);	
  return max_ele->data;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with highest priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with highest priority value.
 */
int pq_max_priority(struct pq* pq) {
	assert(pq);
	struct element* max_ele = dynarray_get(pq->heap,0);
  return max_ele->priority;
}

bool isvalid(int index,struct pq* pq){
	return dynarray_length(pq->heap)>index;
}
/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with highest priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   highest priority value.
 */
void* pq_max_dequeue(struct pq* pq) {
	assert(pq);
	void *max_data = ((struct element*)dynarray_get(pq->heap,0))->data;
	//swap the highest priority element with the last element
	swap_value(pq->heap,0,dynarray_length(pq->heap)-1);
	// remove the highest priority element after sawping,which is placing on the last of array 
	dynarray_remove(pq->heap,dynarray_length(pq->heap)-1);
	int curr_index=0, left_prior=0, right_prior=0, curr_prior=0;
	int left_index=2*curr_index+1;
	int right_index=2*curr_index+2;
	if(isvalid(curr_index,pq)){
		curr_prior=((struct element*)dynarray_get(pq->heap,curr_index))->priority;
	}
	else{
		curr_prior=-1;//curr index is not valid
	}
	if(isvalid(left_index,pq)){
		left_prior=((struct element*)dynarray_get(pq->heap,left_index))->priority;
	}
	else{
		left_prior=-1;//left index out of bound, left does not exist
	}
	if(isvalid(right_index,pq)){//right_index<dynarray_length(pq->heap)){
		right_prior=((struct element*)dynarray_get(pq->heap,right_index))->priority;
	}
	else{
		right_prior=-1;//right index out of bound, right does not exist
	}
	while(left_prior>curr_prior||right_prior>curr_prior){
		if(left_prior>=right_prior){
			swap_value(pq->heap,curr_index,left_index);
			curr_index=left_index;
		}
		else{
			swap_value(pq->heap,curr_index,right_index);
			curr_index=right_index;
		}
		curr_prior=((struct element*)dynarray_get(pq->heap,curr_index))->priority;
		left_index=2*curr_index+1;
		right_index=2*curr_index+2;
		if(isvalid(left_index,pq)){
			left_prior=((struct element*)dynarray_get(pq->heap,left_index))->priority;
		}
		else{
			left_prior=-1;
		}
		if(isvalid(right_index,pq)){
			right_prior=((struct element*)dynarray_get(pq->heap,right_index))->priority;
		}
		else{
			right_prior=-1;
		}
	}
			
  return max_data;
}
