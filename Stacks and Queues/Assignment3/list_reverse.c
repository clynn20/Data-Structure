/*
 * This is the file in which you'll write a function to reverse a linked list.
 * Make sure to add your name and @oregonstate.edu email address below:
 *
 * Name:Chialing Hu
 * Email:huchia@oregonstate.edu
 */

#include <stdio.h>

#include "list_reverse.h"

/*
 * In this function, you will be passed a pointer to the first node of a singly-linked list.
 * You should reverse the linked list and return the new "first" pointer.  The reversal
 * must be done in place, and you may not allocate any new memory in this
 * function.
 *
 * Params:
 *   first - a pointer to the first node of a singly-linked list to be reversed
 *
 * Return:
 *   Should return the new first of the reversed list.  If first is NULL, this
 *   function should return NULL.
 */
struct node* list_reverse(struct node* first) {
  struct node* prev = NULL;
  struct node* curr = first;
  struct node* next = NULL;
  while (curr != NULL){
    next = curr-> next;
    curr -> next = prev;
    prev = curr;
    curr = next;
  }
  first = prev;
  return first;
}
