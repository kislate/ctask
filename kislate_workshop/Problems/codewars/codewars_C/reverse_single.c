/*
Complete the function that accepts a string parameter, and reverses each word in the string. All spaces in the string should be retained.

Examples
"This is an example!" ==> "sihT si na !elpmaxe"
"double  spaces"      ==> "elbuod  secaps"
*/
#include <stdlib.h>

char* reverseWords(const char* text) {

    char *result = (char*)malloc(strlen(text) + 1);
    char *p = result;
    const char *q = text;
    while(*q) {
        if(*q == ' '){
            *p++ = *q++;
        }
        else{
            const char *r = q;
            while(*r && *r != ' ') r++;
            const char *s = r;
            while(r > q) *p++ = *--r;
            q = s;
        }
    }
    *p = '\0';
    return result;
}