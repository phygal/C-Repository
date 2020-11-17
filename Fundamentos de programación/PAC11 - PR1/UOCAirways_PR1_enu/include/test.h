/* Run all the test set */
#include "data.h"
#include "api.h"

/* Runs the applications tests */
void runTests();

/* Runs the applications tests corresponding to PR1 */
void runTestsPR1(int* totalTest, int* passedTest);

/* Test the serialization of passengers */
void test_serialization(int* totalTest, int* passedTest);

/* Test the copy and comparison of passengers */
void test_cpycmp(int* totalTest, int* passedTest);

/* Test the passenger data persistence */
void test_persistence(int* totalTest, int* passedTest);

/* Test the passenger search */
void test_search(int* totalTest, int* passedTest);

/* Test the passenger statistics */
void test_count(int* totalTest, int* passedTest);

/* Test the passenger sorting */
void test_sort(int* totalTest, int* passedTest);

/* Test the api calls */
void test_api(int* totalTest, int* passedTest);


