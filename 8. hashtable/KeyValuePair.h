#include <stdint.h>

#ifndef KEYVALUEPAIR_H
#define KEYVALUEPAIR_H

typedef struct {
  char   *key;    // the key in the key/value pair
  char   *value;  // the value in the key/value pair
} HTKeyValue, *HTKeyValuePtr;

#endif