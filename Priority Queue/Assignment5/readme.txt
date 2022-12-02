Assignment 5 readme:

struct pq* pq_creat():allocate memory and create empty priority queue
void pq_free():free the memory allocated to priority queue
int pq_isempty():return 1 if priority queue is empty
void pq_insert():insert the element into the last of heap array and maintain the max heap priority(compre the current index's priority to parent index's priority).
		 if the current's priority is greater than parent's priority then swap the value between two.
void swap_value():swap the value between two element
void pq_max():return the data of element with the highest priority, which is the first element in heap
int pq_max_priority():return the max priority of element in heap, which is the first elemnet in heap
bool isvalid():return 1 if any given index is less than total element's size in the heap
void pq_max_dequeue():get the first element's data in heap and return it. swap the first element with the last element in the heap, and then remove the last element(remove element with highest priority)
		      maintain the max heap priority(check if the index is valid,compare the current index's priority with left element's priority and right element's priority)
		      if the current priority is less than left priority or right priority, switch the current's value to the smallest priority between right and left. 
		

