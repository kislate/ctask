#include "myString.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct MyString {
    char* str;
};

MyString* MyString_create(const char* str) {
    MyString* myString = (MyString*)malloc(sizeof(MyString));
    if (myString) {
        myString->str = strdup(str);
    }
    return myString;
}

void MyString_destroy(MyString* myString) {
    if (myString) {
        free(myString->str);
        free(myString);
    }
}

const char* MyString_getString(const MyString* myString) {
    return myString ? myString->str : NULL;
}

void MyString_setString(MyString* myString, const char* str) {
    if (myString) {
        free(myString->str);
        myString->str = strdup(str);
    }
}

char* MyString_toUpperCase(const MyString* myString) {
    if (!myString || !myString->str) return NULL;
    char* upperStr = strdup(myString->str);
    for (char* p = upperStr; *p; ++p) {
        *p = toupper(*p);
    }
    return upperStr;
}

char* MyString_toLowerCase(const MyString* myString) {
    if (!myString || !myString->str) return NULL;
    char* lowerStr = strdup(myString->str);
    for (char* p = lowerStr; *p; ++p) {
        *p = tolower(*p);
    }
    return lowerStr;
}