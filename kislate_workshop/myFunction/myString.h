#ifndef MYSTRING_H // if not define, go to next line
#define MYSTRING_H // define

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MyString MyString;

MyString* MyString_create(const char* str);
void MyString_destroy(MyString* myString);
const char* MyString_getString(const MyString* myString);
void MyString_setString(MyString* myString, const char* str);
char* MyString_toUpperCase(const MyString* myString);
char* MyString_toLowerCase(const MyString* myString);

#ifdef __cplusplus
}
#endif

#endif // MYSTRING_H