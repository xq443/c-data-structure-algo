#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "LinkedList_easy.h"
#include "Hashtable.h"
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
void ResizeHashtable(Hashtable ht) {
  int new_size = ht->num_buckets * 2;
  // Allocating memory for the new buckets array
  LinkedList* new_buckets = (LinkedList*)malloc(new_size * sizeof(LinkedList));
  if (new_buckets == NULL) return;

  for (int i = 0; i < new_size; i++) {
    new_buckets[i] = NULL;
  }
  for (int i = 0; i < ht->num_buckets; i++) {
    LinkedList list = ht->buckets[i];
    if(list != NULL) {
      LLIter iterator = CreateLLIter(list);
      char* word;
      while(LLIterHasNext(iterator)) {
        LLIterGetPayload(iterator, &word);
        HTKeyValue kvp;
        kvp.key = FNVHash64((unsigned char *)word, strlen(word)); // Hashing the word to get the key
        kvp.value = list;
        HTKeyValue old_kvp;
        PutInHashtable(ht, kvp, &old_kvp); // Putting the kv in the ht
        LLIterNext(iterator); 
      }
      DestroyLLIter(iterator);
    }
  }
  free(ht->buckets); // Freeing memory allocated for the old buckets array
  ht->buckets = new_buckets; // Updating the buckets array
  ht->num_buckets = new_size; // Updating buckets size
}

int HashKeyToBucketNum(Hashtable ht, uint64_t key) {
  return key % ht->num_buckets;  // Hashing the key to get the bucket number
}

double GetAlpha(Hashtable *hashtable) {
  Hashtable map = *hashtable;  // Dereferencing the pointer
  // Calculating the load factor
  return (double)map->num_elements / (double)map->num_buckets;
}

Hashtable CreateHashtable(int num_buckets) {
  Hashtable map = (Hashtable)malloc(sizeof(struct hashtableInfo));
  if (map == NULL) return NULL;
  map->num_buckets = num_buckets;
  map->num_elements = 0;
  map->buckets = (LinkedList*)malloc(num_buckets * sizeof(LinkedList));
  if (map->buckets == NULL) {
      free(map);
      return NULL;
  }
  for (int i = 0; i < num_buckets; i++) {
    map->buckets[i] = NULL;
  }
  return map;
}

int PutInHashtable(Hashtable ht, HTKeyValue kvp, HTKeyValue *old_kvp) {
  if (ht == NULL) return 1;
  // if the load factor exceeds the threshold resize
  if (GetAlpha(&ht) >= 0.75) {
    ResizeHashtable(ht);
  }
  int bucket_num = HashKeyToBucketNum(ht, kvp.key); // Getting the bucket number for the key
  LinkedList list = ht->buckets[bucket_num]; // Getting the linkedlist in the bucket

  if (list == NULL) { // Checking if the bucket is empty
      list = CreateLinkedList(); // Creating a new linked list
      ht->buckets[bucket_num] = list; // Assigning the linked list to the bucket
  }

  HTKeyValue ret;
  if (LookupInHashtable(ht, kvp.key, &ret) == 0) { // Checking if the key already exists
      if (old_kvp != NULL)
          *old_kvp = ret;
      return 2; // Return 2 if the key already exists
  }
  InsertLinkedList((LinkedList)kvp.value, kvp.value);  // Insert kv pair
  ht->num_elements++;  // Increment the number of elements
  return 0;
}

int LookupInHashtable(Hashtable ht, uint64_t key, HTKeyValue *result) {
  if (ht == NULL) return -1;
  int bucket_num = HashKeyToBucketNum(ht, key);  // Getting the bucket number for the key
  LinkedList list = ht->buckets[bucket_num];  // Getting the linked list in the bucket
  if (list == NULL) return -1;  // if the bucket is empty
  LLIter iter = CreateLLIter(list); // Creating an iterator for the linked list
  char *word;
  while (LLIterHasNext(iter)) { // Looping through each element in the linked list
    LLIterGetPayload(iter, &word); // Getting the payload of the current node
    uint64_t hashed_key = FNVHash64((unsigned char *)word, strlen(word)); // Hashing the payload to check against the provided key
    if (hashed_key == key) { // If the hashed key matches the provided key
        if (result != NULL) { // Checking if the result pointer is valid
            result->key = key; // Setting the key of the result to the provided key
            result->value = list; // Setting the value of the result to the current linked list
        }
        DestroyLLIter(iter); // Destroying the iterator
        return 0; // Return success
    }
    LLIterNext(iter); // Moving to the next element in the linked list
  }
  DestroyLLIter(iter); // Destroying the iterator
  return -1; // Return failure as the key was not found in the hashtable
}


int NumElemsInHashtable(Hashtable ht) {
  if (ht == NULL) return -1;
  return ht->num_elements;
}
int RemoveFromHashtable(Hashtable ht, uint64_t key, HTKeyValue *junk_kvp) {
  if (ht == NULL) return -1; // Return -1 if the hashtable is NULL
  // Calculate the bucket number for the given key
  int bucket_num = HashKeyToBucketNum(ht, key);

  // Get the linked list in the corresponding bucket
  LinkedList list = ht->buckets[bucket_num];

  if (list == NULL)
      return -1; // Return -1 if the bucket is empty

  // Create an iterator for the linked list
  LLIter iter = CreateLLIter(list);
  char *word;

  // Iterate through the linked list
  while (LLIterHasNext(iter)) {
    LLIterGetPayload(iter, &word);
    
    // Compute the hashed key for the current element
    uint64_t hashed_key = FNVHash64((unsigned char *)word, strlen(word));

    // Check if the hashed key matches the given key
    if (hashed_key == key) {
        // Remove the current element from the linkedlist
        RemoveLLElem(list, iter->cur_node);
        ht->num_elements--; // Decrement the number of elements in the hashtable

        // If junk_kvp pointer is provided, set its key and value
        if (junk_kvp != NULL) {
            junk_kvp->key = key;
            junk_kvp->value = word; // Store a pointer to the removed value
        }else {
                free(word); // Free the memory if junk_kvp is not provided
        }

        // Destroy the iterator and return success
        DestroyLLIter(iter);
        return 0;
    }

    // Move to the next element in the linked list
    LLIterNext(iter);
}

  // Destroy the iterator and return failure if the key was not found
  DestroyLLIter(iter);
  return -1;
}

void DestroyHashtable(Hashtable ht) {
if (ht == NULL) return;
for (int i = 0; i < ht->num_buckets; i++) {
    if (ht->buckets[i] != NULL) {
        DestroyLinkedList(ht->buckets[i]);
    }
}
free(ht->buckets);
free(ht);
}