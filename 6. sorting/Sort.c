#include <stdio.h>
#include "LinkedList_easy.h"
#include <stdlib.h>

void SortInsertion(LinkedList* list) {
    if (list == NULL || (*list) == NULL || (*list)->head == NULL) {
        return;
    }

    LinkedListNode* l = NULL;  // Initialize sorted list
    LinkedListNode* curr = (*list)->head;

    while (curr != NULL) {
        LinkedListNode* next = curr->next;
        if (l == NULL || *(l->payload) >= *(curr->payload)) {
            // If the sorted list is empty
            // the curr's payload < the first payload
            curr->next = l;  // Insert curr at the beginning
            if (l != NULL) {
                l->prev = curr;
            }
            l = curr;
            l->prev = NULL;
        } else {
            // Traverse to find the correct position to insert
            LinkedListNode* temp = l;
            while (temp->next != NULL &&
                *(temp->next->payload) < *(curr->payload)) {
                temp = temp->next;
            }
            // Insert curr node after temp
            curr->next = temp->next;
            if (temp->next != NULL) {
                temp->next->prev = curr;  // Update the prev of the next node
            }
            temp->next = curr;
            curr->prev = temp;
        }
        curr = next;
    }

    // Update the newhead
    (*list)->head = l;

    // Update the newtail
    LinkedListNode* tail = l;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    (*list)->tail = tail;
}

void SwapPayloads(uint64_t *x, uint64_t *y) {
    uint64_t temp = *x;
    *x = *y;
    *y = temp;
}

void SortSelection(LinkedList* list) {
    LinkedList l = *list;
    if (l == NULL || l->head == NULL || l->head->next == NULL) {
        return;
    }
    LinkedListNode* curr = l->head;

    while (curr != NULL) {
        // Find the minimum element in the unsorted list.
        LinkedListNode* min = curr;

        // Iterate over the remaining nodes to find the minimum element
        LinkedListNode* j = curr->next;
        while (j != NULL) {
            if (*(j->payload) < *(min->payload)) {
                min = j;
            }
            j = j->next;
        }

        // Swap the payloads of the min with the curr
        SwapPayloads(curr->payload, min->payload);
        curr = curr->next;
    }
    // Update the tail of the list
    LinkedListNode* tail = l->head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    l->tail = tail;

    // Update the original list pointer
    *list = l;
}

// Function to find the middle node of a linked list
LinkedListNode* FindMiddle(LinkedListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;  // Return head if the list has 0 or 1 nodes
    }
    LinkedListNode* slow = head;
    LinkedListNode* fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Merges two sorted sublists pointed to by 'left' and 'right'
// Return a pointer to the head of the merged list.
LinkedListNode* Merge(LinkedListNode* left, LinkedListNode* right) {
     // Dummy node to simplify merging
    LinkedListNode dummy;
    LinkedListNode* curr = &dummy;
    while (left && right) {
        if (*(left->payload) <= *(right->payload)) {
            curr->next = left;
            left->prev = curr;
            left = left->next;
        } else {
            curr->next = right;
            right->prev = curr;
            right = right->next;
        }
        curr->next->prev = curr;
        curr = curr->next;
    }
    curr->next = (left != NULL) ? left : right;
    curr->next->prev = curr;
    return dummy.next;
}

// Sorts a linked list by the head node
LinkedListNode* SortMergeByNode(LinkedListNode* head) {
    if (head == NULL || head->next == NULL) {
        // if empty or has one element, already sorted
        return head;
    }

    // Find the middle point of the list
    LinkedListNode* mid = FindMiddle(head);
    LinkedListNode* left = head;
    LinkedListNode* right = mid->next;
    mid->next = NULL;

    // Recursively sort the two halves
    left = SortMergeByNode(left);
    right = SortMergeByNode(right);

    // Merge the sorted halves
    return Merge(left, right);
}

void SortMerge(LinkedList* list) {
    LinkedList retList = *list;
    if (retList == NULL || retList->head == NULL) {
        printf("Empty list.\n");
        return;
    }
    retList->head = SortMergeByNode(retList->head);

    // Update the tail pointer
    retList->tail = retList->head;
    while (retList->tail->next != NULL) {
        retList->tail = retList->tail->next;
    }
}

// Prints the elements of the linked list
void PrintLinkedList(LinkedList list) {
    if (list == NULL || list->head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }
    LinkedListNode* curr = list->head;
    while (curr != NULL) {
        printf("%lu ", *(curr->payload));
        curr = curr->next;
    }
    printf("\n");
}
