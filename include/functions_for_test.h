#ifndef FUNCTIONS_FOR_TEST_H
#define FUNCTIONS_FOR_TEST_H

#include "work_string.h"

void TestString( const String *data, const char *result_text, const size_t _item_count, const size_t length, const char *function_test);
void TestNumber(const long long numbber, const long long result, const char *function_name);
void TestText(const char *text, const char *result, const char *function_name);
int ComparisonString(const char *text, const char *result);
void __PrintOk(const char *test_name);
void __PrintError(const char *test_name);
void __StandartText();
void __RedText();
void __GreenText();

#endif // FUNCTIONS_FOR_TEST_H
