#ifndef _tools_h
#define _tools_h

// Takes an array of chars and moves then into an array of uInt16s
// returns after handling numChars of chars. numChars must be an
// even number
void Chars2uInts(char* cArray, uInt16 *uiArray, int numChars);

// Takes an array of chars and moves then into an array of ints
// returns after handling numChars of chars. numChars must be an
// even number
void Chars2Ints(char* cArray, int *uiArray, int numChars);

// Takes an array of chars and moves then into an array of floats
// returns after handling numChars of chars. numChars must be an
// even number
void Chars2Ints(char* cArray, int *floats, int numChars);

// Takes an array of chars and moves then into an array of fractionals
// returns after handling numChars of chars. numChars must be an
// even number
void Chars2Ints(char* cArray,  *uiArray, int numChars);


#endif
