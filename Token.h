#ifndef TOKENGUARD
#define TOKENGUARD

#include "std_lib_facilities_4.h"


class Token{			
public:
	char kind;        // shows what kind of token it is
	double value;     // if kind is a "number", then the value of that number 
	Token(char ch)   			// if token is an operator
		:kind(ch), value(0) { }	//sets the value to 0, kind is the operator
	Token(char ch, double val) 
		:kind(ch), value(val) { }
};


//------------------------------------------------------------------------------

#endif