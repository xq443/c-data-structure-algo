#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "LinkedList_easy.h"
#include "Hashtable_easy.h"
/*
 *  Contains implmentation of FNV Hash function. 
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  See <http://www.gnu.org/licenses/>.
 */
#include<stdint.h>
typedef void (*ValueFreeFnPtr)(char*);

uint64_t FNVHash64(unsigned char *buffer, unsigned int len) {
  // This code is adapted from code by Landon Curt Noll
  // and Bonelli Nicola:
  //
  // http://code.google.com/p/nicola-bonelli-repo/
  static const uint64_t FNV1_64_INIT = 0xcbf29ce484222325ULL;
  static const uint64_t FNV_64_PRIME = 0x100000001b3ULL;
  unsigned char *bp = (unsigned char *) buffer;
  unsigned char *be = bp + len;
  uint64_t hval = FNV1_64_INIT;
  /*
   * FNV-1a hash each octet of the buffer
   */
  while (bp < be) {
    /* xor the bottom with the current octet */
    hval ^= (uint64_t) * bp++;
    /* multiply by the 64 bit FNV magic prime mod 2^64 */
    hval *= FNV_64_PRIME;
  }
  /* return our new hash value */
  return hval;
}


uint64_t FNVHashInt64(uint64_t makehash) {
  unsigned char buf[8];
  int i;
  for (i = 0; i < 8; i++) {
    buf[i] = (unsigned char) (makehash & 0x00000000000000FFULL);
    makehash >>= 8;
  }
  return FNVHash64(buf, 8);
}


int HashKeyToBucketNum(Hashtable ht, char* key) {
    uint64_t hashedKey = FNVHash64((unsigned char *)key, strlen(key));
    return hashedKey % ht->num_buckets;  // Hashing the key to get the bucket number
}

double GetAlpha(Hashtable *hashtable) {
  Hashtable map = *hashtable;  // Dereferencing the pointer
  // Calculating the load factor
  return (double)map->num_elements / (double)map->num_buckets;
}

void ResizeHashtable(Hashtable ht) {
    if (ht == NULL) return;
    int new_size = ht->num_buckets * 2;

    // Allocating memory for the new buckets array
    LinkedList *new_buckets = (LinkedList*)malloc(new_size * sizeof(LinkedList));
    if (new_buckets == NULL) return;
    for (int i = 0; i < new_size; i++) {
        new_buckets[i] = CreateLinkedList();
    }

    // Iterate through each bucket in the old hashtable
    for (int i = 0; i < ht->num_buckets; i++) {
        LinkedListNodePtr curr = ht->buckets[i]->head;
        while (curr != NULL) {
            HTKeyValue *kvp = curr->payload;
            char *sorted_key = strdup(kvp->key);
            SortString(sorted_key);
            int new_hash = HashKeyToBucketNum(ht, sorted_key);

            // Insert into the new bucket
            if (InsertLinkedList(new_buckets[new_hash], kvp) == -1) {

                // Insertion failed, clean up and return
                for (int j = 0; j < new_size; j++) {
                    DestroyLinkedList(new_buckets[j]);
                }
                free(new_buckets);
                return;
            }
            free(sorted_key);
            curr = curr->next;
        }
    }

    // Free the memory occupied by the old buckets
    for (int i = 0; i < ht->num_buckets; i++) {
        DestroyLinkedList(ht->buckets[i]);
    }
    free(ht->buckets); // Freeing memory allocated for the old buckets array
    ht->buckets = new_buckets; // Updating the buckets array
    ht->num_buckets = new_size; // Updating buckets size
}


Hashtable CreateHashtable(int num_buckets) {
  Hashtable map = (Hashtable)malloc(sizeof(struct hashtableInfo));
  map->num_buckets = num_buckets;
  map->num_elements = 0;
  map->buckets = (LinkedList*)malloc(num_buckets * sizeof(LinkedList));
  for (int i = 0; i < num_buckets; i++) {
    map->buckets[i] = CreateLinkedList();
  }
  return map;
}

int PutInHashtable(Hashtable ht, char * key) {
    if (ht == NULL || ht->buckets == NULL) {
        return 1; // Hashtable is not initialized
    }
    char *sorted_key = strdup(key);
    SortString(sorted_key);
    int bucketIndex = HashKeyToBucketNum(ht, sorted_key);
    LinkedList bucket = ht->buckets[bucketIndex];
    LinkedListNode *curr = bucket->head;
    while (curr != NULL) {
      if (strcmp(curr->payload->key, sorted_key) == 0) {
        // Key already exists, add the value to the values linked list
        char* new_value = strdup(key);
        if (new_value == NULL) {
            free(sorted_key);
            return 1; // Memory allocation failed
        }
        // Create a new node for the value
        LinkedListNode *new_node = (LinkedListNode *)malloc(sizeof(LinkedListNode));
        if (new_node == NULL) {
            free(new_value);
            free(sorted_key);
            return 1; // Memory allocation failed
        }
        // Set the payload of the new node
        new_node->payload = (HTKeyValue *)malloc(sizeof(HTKeyValue));
        if (new_node->payload == NULL) {
            free(new_value);
            free(new_node);
            free(sorted_key);
            return 1; // Memory allocation failed
        }
        new_node->payload->key = sorted_key;
        new_node->payload->value = new_value;
        new_node->next = NULL; // Ensure new node is the last in the list

        // Append the new node to the tail
        LinkedListNode *tail = bucket->head;
        if (tail == NULL) {
            bucket->head = new_node; // Empty list
        } else {
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = new_node;
        }
        bucket->num_elements++;
        // Update the number of elements in the hashtable
        ht->num_elements++;
        // Check if resize is needed after updating the number of elements
        if (GetAlpha(&ht) > 0.75) {
            ResizeHashtable(ht);
        }
        return 2; // Key already exists and value updated
      }
      curr = curr->next;
    }
    // No collision, insert the new key-value pair into the bucket
    HTKeyValue *kvp = (HTKeyValue *)malloc(sizeof(HTKeyValue));
    if (kvp == NULL) {
        free(sorted_key);
        return 1; // Memory allocation failed
    }
    kvp->key = sorted_key;
    kvp->value = strdup(key); // Duplicate the value string
    if (kvp->value == NULL) {
        free(kvp->key);
        free(kvp);
        return 1; // Memory allocation failed
    }
    if (InsertLinkedList(bucket, kvp) == -1) {
        free(kvp->key);
        free(kvp->value);
        free(kvp);
        return 1; // Insertion failed
    }
    // Update the number of elements in the hashtable
    ht->num_elements++;
    return 0; // Successful insertion
}




int LookupInHashtable(Hashtable ht, char* key, LinkedList* ret) {
  char *cpstr = strdup(key);
  SortString(cpstr);
  int bucket = HashKeyToBucketNum(ht, cpstr);
  LinkedList list = ht->buckets[bucket];
  if (list == NULL) return -1;
  if (list->num_elements > 0) {
    *ret = list;
    return 0;
  }
  return -1;
}


int NumElemsInHashtable(Hashtable ht) {
  if (ht == NULL) return -1;
  return ht->num_elements;
}

int RemoveFromHashtable(Hashtable ht, char* key) {
    if (ht == NULL || key == NULL) return -1; // Check for NULL hashtable or key

    char *cpstr = strdup(key);
    SortString(cpstr);
    
    // Calculate the bucket number for the given key
    int bucket_num = HashKeyToBucketNum(ht, cpstr);
    
    // Get the linked list in the corresponding bucket
    LinkedListNodePtr curr = ht->buckets[bucket_num]->head;
    
    // Traverse the linked list to find the node with the matching key
    while (curr != NULL) {
        printf("Current key: %s\n", curr->payload->key); // Print current key for debugging
        printf("Comparing keys: \"%s\" and \"%s\"\n", curr->payload->key, key);
        if (strcmp(curr->payload->key, cpstr) == 0) { // Use strcmp for string comparison
            RemoveLLElem(ht->buckets[bucket_num], curr);
            ht->num_elements--;
            return 0; // successful removal
        }
        curr = curr->next; // Move to the next node
    }
    return -1; // if key not found in the hashtable
}




void DestroyHashtable(Hashtable ht) {
  for (int i = 0; i < ht->num_buckets; i++) {
    DestroyLinkedList(ht->buckets[i]);
  }
  free(ht->buckets); // Free the array of linked lists
  free(ht);
}

// compare characters for qsort
int CompareChars(const void *a, const void *b) {
    // Cast a and b to char pointers and dereference them to get characters
    // Then subtract one from the other to determine the comparison result
    return (*(const char*)a - *(const char*)b);
}

// sort a string in ascending order
void SortString(char *str) {
    int length = strlen(str);
    
    // Use qsort to sort the string in place
    // Parameters:
    // - str: Pointer to the first element of the array to be sorted
    // - length: Number of elements in the array
    // - sizeof(char): Size of each element in bytes (in this case, a character)
    // - compareChars: Pointer to the comparison function
    qsort(str, length, sizeof(char), CompareChars);
}

// generate anagrams
void GenerateAnagrams(Hashtable ht) {
  printf("====== Anagram Report ======\n");
  for(int i = 0; i < ht->num_buckets; i++) {
    LinkedList bucket = ht->buckets[i];
    if(bucket->num_elements == 0) continue;
    LinkedListNodePtr curr = ht->buckets[i]->head;
    printf("%s -> [ ", curr->payload->key);
    while (curr != NULL) {
      printf("%s ", curr->payload->value);
      curr = curr->next;
    }
    printf("]\n");
  }
}
