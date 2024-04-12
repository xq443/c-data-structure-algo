#include "gtest/gtest.h"
#include <stdio.h> 
extern "C" {
    #include "Hashtable_easy.h"
    #include "LinkedList_easy.h"
    #include <string.h>
}
const char* first = "first";
const char* second="second";
const char* third = "third";
const char* fourth = "fourth";

#define MAX_VALUE_LEN 75

TEST(Hashtable, Create) {
  Hashtable ht = CreateHashtable(5);
  EXPECT_FALSE(ht == NULL);
  EXPECT_FALSE(ht->buckets == NULL);
  EXPECT_EQ(NumElemsInHashtable(ht), 0);
  DestroyHashtable(ht);
}

TEST(Hashtable, AddOneRemoveOne) {
    Hashtable ht = CreateHashtable(5);
    
    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // Make KeyValue Pair
    char* key = strdup("test");
    PutInHashtable(ht, key);
    EXPECT_EQ(NumElemsInHashtable(ht), 1);

    printf("Before removal:\n");
    GenerateAnagrams(ht); // Print out the key-value pairs before removal

    EXPECT_EQ(RemoveFromHashtable(ht, key), 0);
    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    printf("\nAfter removal:\n");
    GenerateAnagrams(ht); // Print out the key-value pairs after removal

    DestroyHashtable(ht);
}

TEST(Hashtable, HashKeyToBucketNum) {
    int num_buckets = 10;
    Hashtable ht = CreateHashtable(num_buckets);

    // Test various keys to check if they are hashed into correct buckets
    char* test_key = strdup("test"); // Duplicate the key
    
    char *cpstr = strdup(test_key);
    SortString(cpstr);

    int hash_key = HashKeyToBucketNum(ht, cpstr); // Calculate the hash key
    printf("Hash key for \"%s\" is: %d\n", test_key, hash_key);
    EXPECT_EQ(hash_key, 5); // Adjust the expected value according to your hash function

    // Put the key in the hashtable
    printf("Putting key \"%s\" in the hashtable...\n", cpstr);
    EXPECT_EQ(PutInHashtable(ht, cpstr), 0);
    EXPECT_EQ(NumElemsInHashtable(ht), 1);


    // Check if the bucket at the calculated hash key exists and is not NULL
    if (ht->buckets[hash_key] != NULL && ht->buckets[hash_key]->head != NULL && ht->buckets[hash_key]->head->payload != NULL) {
        printf("Key stored in the map: \"%s\"\n", ht->buckets[hash_key]->head->payload->key);
    } else {
        printf("No key stored in the map at hash key %d\n", hash_key);
    }

    // Remove the key from the hashtable
    if (RemoveFromHashtable(ht, cpstr) == 0) {
        printf("Removal is successful\n");
    } else {
        printf("Removal failed\n");
    }

    DestroyHashtable(ht);
}



TEST(Hashtable, AddOneElemDestroy) {
    Hashtable ht = CreateHashtable(5);

    // Check initial number of elements
    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // Make KeyValue Pair
    char* key = strdup("test");
    PutInHashtable(ht, key);
    EXPECT_EQ(NumElemsInHashtable(ht), 1);
    // Destroy hashtable
    DestroyHashtable(ht);
}

TEST(Hashtable, AddOneElemTwoTimes) {
    Hashtable ht = CreateHashtable(5);
    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // Make KeyValue Pair
    char* key1 = strdup("test");
    char* key2 = strdup("test");
    EXPECT_EQ(PutInHashtable(ht, key1), 0);
    EXPECT_EQ(NumElemsInHashtable(ht), 1);

    // Trying to put it in again should result in an error
    EXPECT_EQ(PutInHashtable(ht, key2), 2);
    EXPECT_EQ(NumElemsInHashtable(ht), 2);

    DestroyHashtable(ht);
}

TEST(Hashtable, AddOneRemoveTwice) {
    Hashtable ht = CreateHashtable(5);

    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // Make KeyValue Pair
    char* key1 = strdup("test");
    // TODO(student): Put something meaningful here
    EXPECT_EQ(PutInHashtable(ht, key1), 0);
    EXPECT_EQ(NumElemsInHashtable(ht), 1);

    // remove successfully
    EXPECT_EQ(RemoveFromHashtable(ht, key1), 0);
    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // remove twice failure
    EXPECT_EQ(RemoveFromHashtable(ht, key1), -1);
    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    DestroyHashtable(ht);
}

TEST(Hashtable, AddMultipleItems) {
    Hashtable ht = CreateHashtable(100);

    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // Make KeyValue Pair
    char *key1 = strdup("test1");
    char *key2 = strdup("test2");
    char *key3 = strdup("test3");

    PutInHashtable(ht, key1);
    ASSERT_EQ(NumElemsInHashtable(ht), 1);

    PutInHashtable(ht, key2);
    ASSERT_EQ(NumElemsInHashtable(ht), 2);

    PutInHashtable(ht, key3);
    ASSERT_EQ(NumElemsInHashtable(ht), 3);
    DestroyHashtable(ht);
}

TEST(Hashtable, LookupInHashtable) {
    Hashtable ht = CreateHashtable(100);

    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    char *key1 = strdup("test1");
    char *key2 = strdup("test2");
    char *key3 = strdup("test3");

    // TODO(student): Put something meaningful here
    PutInHashtable(ht, key1);
    ASSERT_EQ(NumElemsInHashtable(ht), 1);

    // TODO(student): Put something meaningful here
    PutInHashtable(ht, key2);
    ASSERT_EQ(NumElemsInHashtable(ht), 2);


    // TODO(student): Put something meaningful here
    PutInHashtable(ht, key3);
    ASSERT_EQ(NumElemsInHashtable(ht), 3);


    LinkedList lookup_result;
    char *key = strdup("test1");
    // Now, lookup
    int result = LookupInHashtable(ht,
        key,
        &lookup_result);
    // key value pair has been found
    EXPECT_EQ(result, 0);
    EXPECT_EQ(lookup_result->num_elements, 1);
    EXPECT_EQ(strcmp(lookup_result->head->payload->value, "test1"), 0);

    EXPECT_EQ(NumElemsInHashtable(ht), 3);

    // looking up something not in the table
    int result1 = LookupInHashtable(ht,
        strdup("notfound"),
        &lookup_result);
    EXPECT_EQ(result1, -1);

    DestroyHashtable(ht);
}

TEST(Hashtable, TwoElemsOneBucket) {
    Hashtable ht = CreateHashtable(15);

    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    char *key1 = strdup("test");

    ASSERT_EQ(PutInHashtable(ht, key1), 0);
    ASSERT_EQ(NumElemsInHashtable(ht), 1);

    char *key2 = strdup("ttes");
    ASSERT_EQ(PutInHashtable(ht, key2), 2);
    ASSERT_EQ(NumElemsInHashtable(ht), 2);

    LinkedList lookup_result;
    int result = LookupInHashtable(ht,
        key1,
        &lookup_result);
    // key value pair has been found
    EXPECT_EQ(result, 0);
    EXPECT_EQ(ht->num_elements, 2);
    EXPECT_EQ(strcmp(lookup_result->head->payload->value, "test"), 0);
    EXPECT_EQ(strcmp(lookup_result->head->next->payload->value, "ttes"), 0);

    DestroyHashtable(ht);
}

TEST(Hashtable, Resize) {
  Hashtable ht = CreateHashtable(5);

  for (unsigned int i = 0; i < 60; i++) {
    // do the insert
    SomeNumPtr np = static_cast<SomeNumPtr>(malloc(sizeof(someNum)));

    assert(np != NULL);
    np->num = static_cast<int>(i);
    char *key1 = strdup("test");
    ASSERT_EQ(PutInHashtable(ht, key1), 0);
    ASSERT_EQ(NumElemsInHashtable(ht), 1);

    //printf("i = %d\n", i);

    // test double insert
    ASSERT_EQ(PutInHashtable(ht, key1), 2);

    // test lookup
    old.key = 1;
    old.value = NULL;
    ASSERT_EQ(0, LookupInHashtable(ht, i, &old));
    ASSERT_EQ(i, old.key);
    ASSERT_EQ(static_cast<void *>(np), old.value);

    // test bad lookup
    ASSERT_EQ(-1, LookupInHashtable(ht, i+1));

    // test bad remove
    ASSERT_EQ(-1, RemoveFromHashtable(ht, i+1));

    // test good remove and reinsert
    old.key = -100;
    old.value = NULL;
    ASSERT_EQ(0, RemoveFromHashtable(ht, i));
    ASSERT_EQ(i, old.key);
    ASSERT_EQ(static_cast<void *>(np), old.value);
    ASSERT_EQ(i, (unsigned)NumElemsInHashtable(ht));
    ASSERT_EQ(0, PutInHashtable(ht, newkv));
    ASSERT_EQ(2, PutInHashtable(ht, newkv));
    ASSERT_EQ(i+1, (unsigned)NumElemsInHashtable(ht));
  }
    DestroyHashtable(ht);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
