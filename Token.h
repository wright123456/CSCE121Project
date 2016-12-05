#ifndef TOKENGUARD
#define TOKENGUARD

#include "std_lib_facilities_4.h"


class Token{			
public:
	char kind;        // what kind of token
	double value;     // for numbers: a value 
	Token(char ch)    // make a Token from a char
		:kind(ch), value(0) { }
	Token(char ch, double val)     // make a Token from a char and a double
		:kind(ch), value(val) { }
};


//------------------------------------------------------------------------------

#endif