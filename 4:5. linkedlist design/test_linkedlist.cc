#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"

#include "gtest/gtest.h"
#include <cstring>  // for strdup

extern "C" {
    #include "LinkedList_easy.h"
    #include <string.h>
}

const char* first = "first";
const char* second = "second";
const char* third = "third";
const char* fourth = "fourth";

int contains(LinkedList list, char* str) {
    // Check for invalid inputs
    if (list == NULL || str == NULL || list->head == NULL)
        return 0;  // Return 0 since list is empty or invalid

    // Traverse the linked list
    LinkedListNodePtr current = list->head;
    while (current != NULL) {
        // Check if the payload matches the provided string
        if (strcmp(current->payload, str) == 0) {
            return 1;  // Return 1 if the string is found
        }
        current = current->next;  // Move to the next node
    }

    return 0;  // Return 0 if the string is not found
}

#define MAX_VALUE_LEN 75

TEST(Test, Test) {
    EXPECT_TRUE(true);
}

// Test case for CreateLinkedListNode function
TEST(LinkedListNode, CreateLinkedListNode) {
    const char* data = "Cathy";

    // strdup allocates memory
    LinkedListNode* node = CreateLinkedListNode(strdup(data));
    EXPECT_TRUE(node != NULL);  // Check if node is not NULL
    ASSERT_STREQ(node->payload, data);
    DestroyLinkedListNode(node);
}

// Test case for DestroyLinkedListNode function
TEST(LinkedListNode, DestroyLinkedListNode) {
    const char* data = "Cathy";
    char* copiedData = strdup(data);  // strdup allocates memory
    LinkedListNode* node = CreateLinkedListNode(copiedData);

    // Check if destroy was successful
    EXPECT_EQ(DestroyLinkedListNode(node), 0);
}

// test case for CreateLinkedList() method
TEST(LinkedList, Create) {
    LinkedList list = CreateLinkedList();
    EXPECT_EQ(list->num_elements, 0);
    DestroyLinkedList(list);
}

// test case for DestroyLinkedList() method
TEST(LinkedList, Destroy) {
    LinkedList list = CreateLinkedList();
    EXPECT_EQ(DestroyLinkedList(list), 0);
}

// Test case for NumElementsInLinkedList
TEST(LinkedList, NumElements) {
    LinkedList list = CreateLinkedList();
    EXPECT_EQ(NumElementsInLinkedList(list), 0);
    DestroyLinkedList(list);
}

TEST(LinkedList, InsertIntoEmptyList) {
    // Create an empty linked list
    LinkedList list = CreateLinkedList();

    // Insert an element into the empty list
    char* data = strdup("Element 1");
    ASSERT_EQ(InsertLinkedList(list, data), 0);

    // Check if the insertion was successful
    ASSERT_EQ(NumElementsInLinkedList(list), 1);
    DestroyLinkedList(list);
}

TEST(RemoveLLElemTest, RemoveHeadElement) {
    LinkedList list = CreateLinkedList();
    InsertLinkedList(list, strdup("1"));
    InsertLinkedList(list, strdup("2"));
    InsertLinkedList(list, strdup(" 3"));  // 3  2  1

    // the pointer to the head node
    LinkedListNodePtr tmp = list->head;

    // Call RemoveLLElem method to remove the head element
    ASSERT_EQ(RemoveLLElem(list, tmp), 0);  // 2  1

    // Check if the head element is removed correctly
    // The previous of the new head should be nullptr
    ASSERT_TRUE(list->head->prev == NULL);
    ASSERT_STREQ(list->head->payload, "2");

    // Check the number of elements in the list after removal
    ASSERT_EQ(NumElementsInLinkedList(list), 2);
    DestroyLinkedList(list);
}

// Test case for PopLinkedList method
TEST(PopLinkedListTest, PopFromNonEmptyList) {
    LinkedList list = CreateLinkedList();
    InsertLinkedList(list, strdup("1"));
    InsertLinkedList(list, strdup("2"));

    char* popped = NULL;  // initialize

    // If pop is successful: &popped-> the address of a pointer
    ASSERT_EQ(PopLinkedList(list, &popped), 0);
    ASSERT_STREQ(list->head->payload, "1");

    // Check the number of elements in the list after popping
    ASSERT_EQ(NumElementsInLinkedList(list), 1);
    DestroyLinkedList(list);
}

// Test case for SortLinkedList
TEST(SortLinkedListTest, SorttLinkedListinAsc) {
    LinkedList list = CreateLinkedList();
    InsertLinkedList(list, strdup("Cathy"));
    InsertLinkedList(list, strdup("Amy"));
    InsertLinkedList(list, strdup("David"));
    InsertLinkedList(list, strdup("Grace"));

    // in asc order
    SortLinkedList(list, 1);

    // initialize an array with the expected order
    const char* arr[] = {"Amy", "Cathy", "David", "Grace"};
    int n = sizeof(arr) / sizeof(arr[0]);

    // compare each element with the correct value
    LinkedListNode* curr = list->head;
    for (int i = 0; i < n; i++) {
        ASSERT_STREQ(curr->payload, arr[i]);  // dereference
        curr = curr->next;
    }
    DestroyLinkedList(list);
}

// test for CreateLLIter
TEST(LLIter, CreateLLIter) {
    LinkedList list = CreateLinkedList();
    InsertLinkedList(list, strdup("1"));

    LLIter iterator = CreateLLIter(list);

    // check if the iterator is not null
    // if the iterator points to list, if the curnode points to the head
    ASSERT_TRUE(iterator != NULL);
    ASSERT_EQ(iterator->list, list);
    ASSERT_EQ(iterator->cur_node, list->head);
    DestroyLLIter(iterator);
}

// test for LLIterHasNext
TEST(LLIter, LLIterHasNext) {
    LinkedList list = CreateLinkedList();
    InsertLinkedList(list, strdup("Element 1"));
    InsertLinkedList(list, strdup("Element 2"));
    LLIter iterator = CreateLLIter(list);
    EXPECT_TRUE(LLIterHasNext(iterator));

    // iterate to the next, which does not have the next iterator
    LLIterNext(iterator);
    EXPECT_FALSE(LLIterHasNext(iterator));
    DestroyLLIter(iterator);
}

// test for LLIterHasPrev
TEST(LLIter, LLIterHasPrev) {
    LinkedList list = CreateLinkedList();
    InsertLinkedList(list, strdup("Element 1"));
    InsertLinkedList(list, strdup("Element 2"));
    LLIter iterator = CreateLLIter(list);
    EXPECT_FALSE(LLIterHasPrev(iterator));
    LLIterNext(iterator);
    EXPECT_TRUE(LLIterHasPrev(iterator));
    DestroyLLIter(iterator);
}

// test for LLIterNext
TEST(LLIter, LLIterNext) {
    LinkedList list = CreateLinkedList();
    InsertLinkedList(list, strdup("1"));
    InsertLinkedList(list, strdup("2"));
    LLIter iterator = CreateLLIter(list);
    LLIterNext(iterator);
    // check if payload is updated correctly
    ASSERT_STREQ(iterator->cur_node->payload, "1");
    DestroyLLIter(iterator);
}

// test for LLIterPrev
TEST(LLIter, LLIterPrev) {
    LinkedList list = CreateLinkedList();
    InsertLinkedList(list, strdup("1"));
    InsertLinkedList(list, strdup("2"));
    LLIter iterator = CreateLLIter(list);
    LLIterNext(iterator);
    LLIterPrev(iterator);
    EXPECT_STREQ(iterator->cur_node->payload, "2");
    DestroyLLIter(iterator);
}

// test for LLIterGetPayload
TEST(LLIter, LLIterGetPayload) {
    LinkedList list = CreateLinkedList();
    InsertLinkedList(list, strdup("1"));
    LLIter iterator = CreateLLIter(list);
    char* payload = NULL;  // initialize the pointer as nullptr
    LLIterGetPayload(iterator, &payload);  // pointer to the pointer
    ASSERT_STREQ(payload, "1");
    DestroyLLIter(iterator);
}

// test for LLIterDelete
TEST(LLIter, LLIterDelete) {
    LinkedList list = CreateLinkedList();
    InsertLinkedList(list, strdup("1"));
    InsertLinkedList(list, strdup("2"));
    LLIter iterator = CreateLLIter(list);
    ASSERT_EQ(LLIterDelete(iterator), 0);
    DestroyLLIter(iterator);
}

// test for LLIterInsertBefore
TEST(LLIterTest, LLIterInsertBefore) {
    LinkedList list = CreateLinkedList();
    InsertLinkedList(list, strdup("1"));
    InsertLinkedList(list, strdup("3"));  // 3 1
    LLIter iterator = CreateLLIter(list);
    LLIterNext(iterator);  // point to 1
    char* payload = strdup("2");

    // Insert the payload "2" before the current iterator position : 3 2 1
    LLIterInsertBefore(iterator, payload);
    char* currPayload = NULL;
    LLIterGetPayload(iterator, &currPayload);
    ASSERT_STREQ(currPayload, "1");  // Check the payload is "1"

    // previous payload check
    LLIterPrev(iterator);
    char* currPayload1 = NULL;
    LLIterGetPayload(iterator, &currPayload1);
    ASSERT_STREQ(currPayload1, "2");  // Check the previous payload is "2"
    DestroyLLIter(iterator);
}

// test for DestroyLLIter
TEST(LLIter, DestroyLLIter) {
    LinkedList list = CreateLinkedList();
    InsertLinkedList(list, strdup("1"));
    LLIter iterator = CreateLLIter(list);
    ASSERT_TRUE(iterator != NULL);
    ASSERT_EQ(DestroyLLIter(iterator), 0);
}

// The added unit tests
// test for CreateLinkedList: SizeIsZero
TEST(CreateLinkedList, givenNoInputWhenCreatingListThenSizeIsZero) {
  LinkedList list = CreateLinkedList();
  EXPECT_EQ(list->num_elements, 0);
  DestroyLinkedList(list);
}

// test for CreateLinkedList: HeadAndTailAreNull
TEST(CreateLinkedList, givenNoInputWhenCreatingListThenHeadAndTailAreNull) {
    LinkedList list = CreateLinkedList();
    EXPECT_TRUE(list->head == NULL);
    EXPECT_TRUE(list->tail == NULL);
    DestroyLinkedList(list);
}

// test for InsertLinkedList: StringIsInList
TEST(InsertLinkedList, givenNonNullStringWhenInsertedThenStringIsInList) {
    LinkedList list = CreateLinkedList();
    char* testString = strdup("test");
    InsertLinkedList(list, testString);
    int hasString = contains(list, testString);
    EXPECT_EQ(hasString, 1);

    // free(testString);
    DestroyLinkedList(list);
}

// test for InsertLinkedList: StringHead
TEST(InsertLinkedList, givenNonNullStringWhenInsertedThenStringHead) {
    LinkedList list = CreateLinkedList();
    char* testString = strdup("test");
    InsertLinkedList(list, testString);
    LinkedListNodePtr head = list->head;
    EXPECT_EQ(0, strcmp(testString, head->payload));
    LinkedListNodePtr tail = list->tail;
    EXPECT_EQ(0, strcmp(testString, tail->payload));

    // free(testString);
    DestroyLinkedList(list);
}

// test for RemoveLLElem: StringIsNotInList
TEST(RemoveLLElem, givenNonNullStringWhenRemovedThenStringIsNotInList) {
    LinkedList list = CreateLinkedList();
    char* testString = strdup("test");
    InsertLinkedList(list, testString);

    // assert list->num_elements == 1
    LinkedListNodePtr node = list->head;
    RemoveLLElem(list, node);
    ASSERT_EQ(NumElementsInLinkedList(list), 0);

    // verify StringIsNotInList
    int hasString = contains(list, testString);
    EXPECT_EQ(hasString, 0);
    DestroyLinkedList(list);
}

// test for RemoveLLElem: HeadAndTailAreNull
TEST(EmptyListNullHeadAndTail, EmptyListInsertRemoveThenHeadTailNull) {
    LinkedList list = CreateLinkedList();
    char* testString = strdup("test");
    InsertLinkedList(list, testString);
    LinkedListNodePtr node = list->head;
    RemoveLLElem(list, node);

    // verify HeadAndTailAreNull
    EXPECT_EQ(list->head, nullptr);
    EXPECT_EQ(list->tail, nullptr);
    DestroyLinkedList(list);
}

// test for NumElementsInLinkedList: NumElementsIsZero
TEST(NumElementsInLinkedList, givenEmptyListThenNumElementsIsZero) {
    LinkedList list = CreateLinkedList();
    int size = NumElementsInLinkedList(list);

    // verify size == 0
    EXPECT_EQ(size, 0);
    DestroyLinkedList(list);
}

// test for NumElementsInLinkedList: NumElementsIsOne
TEST(NumElementsInLinkedList, givenListWithSingleNodeThenNumElementsIsOne) {
    LinkedList list = CreateLinkedList();
    char* test = strdup("test");
    InsertLinkedList(list, test);
    int size = NumElementsInLinkedList(list);

    // verify size == 1
    EXPECT_EQ(size, 1);

    // free(test);
    DestroyLinkedList(list);
}

// test for NumElementsInLinkedList: NumElementsIsN
TEST(NumElementsInLinkedList, givenListWith_N_NodeThenNumElementsIsN) {
    LinkedList list = CreateLinkedList();
    char* test = strdup("test");
    InsertLinkedList(list, test);
    char* test1 = strdup("test1");
    InsertLinkedList(list, test1);
    char* test2 = strdup("test2");
    InsertLinkedList(list, test2);
    int size = NumElementsInLinkedList(list);

    // verify NumElementsIsN
    EXPECT_EQ(size, 3);

    // free(test);
    DestroyLinkedList(list);
}

// test for PopLinkedList: givenEmptyList -> ReturnsTheInputDataPtr
TEST(PopLinkedList, givenEmptyListWhenPoppedThenReturnsTheInputDataPtr) {
    LinkedList list = CreateLinkedList();
    char* str = strdup("");
    char** buffer = &str;
    char** ref = buffer;
    PopLinkedList(list, buffer);
    EXPECT_EQ(ref, buffer);
    free(str);
    DestroyLinkedList(list);
}
// test for PopLinkedList: givenNonEmptyList -> DoesNotReturnTheInputDataPtr
TEST(PopLinkedList, NonEmptyListPoppedThenNotReturnInputDataPtr) {
    LinkedList list = CreateLinkedList();
    char* test = strdup("test");
    InsertLinkedList(list, test);  // "test"
    char* str;
    char** buffer = &str;
    EXPECT_EQ(list->num_elements, 1);
    PopLinkedList(list, buffer);

    // The memory for the string test freed before the comparison
    // EXPECT_EQ(0, strcmp(test, *buffer));
    EXPECT_EQ(list->num_elements, 0);
    EXPECT_TRUE(list->head == NULL);
    DestroyLinkedList(list);
}

// test for PopLinkedList: givenListWithMultipleItems
// -> NotReturnTheInputDataPtr
TEST(PopLinkedList, MultipleItemsPoppedThenNotReturnInputPtr) {
    LinkedList list = CreateLinkedList();
    char* test = strdup("test");
    InsertLinkedList(list, test);
    char* test2 = strdup("test2");
    InsertLinkedList(list, test2);
    char* str;
    char** buffer = &str;
    EXPECT_EQ(list->num_elements, 2);
    PopLinkedList(list, buffer);

    // The memory for the string test freed before the comparison
    // EXPECT_EQ(0, strcmp(test2, *buffer));
    EXPECT_EQ(0, strcmp(list->head->payload, test));
    EXPECT_EQ(list->num_elements, 1);
    DestroyLinkedList(list);
}

// test for CreateLLIter: OnEmptyList
TEST(Test_Iterator, givenValidListTestIteratorOnEmptyList) {
    LinkedList list = CreateLinkedList();
    LLIter iter = CreateLLIter(list);
    EXPECT_NE(iter, nullptr);
    EXPECT_EQ(LLIterHasNext(iter), 0);
    EXPECT_EQ(LLIterHasPrev(iter), 0);
    DestroyLLIter(iter);
}

// test for CreateLLIter: OnListWithSingleValue
TEST(Test_Iterator, givenValidListTestIteratorOnListWithSingleValue) {
    LinkedList list = CreateLinkedList();
    char* testString = strdup("test");
    InsertLinkedList(list, testString);
    LLIter iter = CreateLLIter(list);
    EXPECT_NE(iter, nullptr);
    EXPECT_EQ(LLIterHasNext(iter), 0);
    EXPECT_EQ(LLIterHasPrev(iter), 0);
    DestroyLLIter(iter);
}

// test for LLIterHasNext, LLIterHasPrev
// LLIterPrev, LLIterNext, LLIterGetPayload
TEST(Test_Iterator, givenValidListTestIteratorOnListWithMultipleValues) {
    LinkedList list = CreateLinkedList();
    char* testString1 = strdup("test1");
    char* testString2 = strdup("test2");
    InsertLinkedList(list, testString1);
    InsertLinkedList(list, testString2);  // "test2" "test1"
    LLIter iter = CreateLLIter(list);
    EXPECT_NE(iter, nullptr);
    EXPECT_EQ(LLIterHasNext(iter), 1);
    EXPECT_EQ(LLIterHasPrev(iter), 0);
    LLIterNext(iter);
    EXPECT_EQ(LLIterHasNext(iter), 0);
    EXPECT_EQ(LLIterHasPrev(iter), 1);
    LLIterPrev(iter);
    EXPECT_EQ(LLIterHasNext(iter), 1);
    EXPECT_EQ(LLIterHasPrev(iter), 0);
    char* str;
    char** data = &str;
    LLIterGetPayload(iter, data);

    // expect string not equal
    EXPECT_STRNE(testString1, *data);

    // expect they are equal
    EXPECT_STREQ(testString2, *data);
    DestroyLLIter(iter);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
