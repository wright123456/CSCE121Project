#include "token_stream.h"
#include "Token.h"
#include "std_lib_facilities_4.h"

Token_stream::Token_stream(istringstream* calc_stringptr):full(false), buffer(0)  // sets buffer to empty
{
	calc_string = calc_stringptr;				//input parameter 
}

void Token_stream::putback(Token t)				//puts token into buffer
{
	if (full) error("putback() into a full buffer");
	buffer = t;
	full = true;
}

Token Token_stream::get()
{
	if (full) {      			//checks if there is a buffer in token
		full = false;			//if so, then
		return buffer;			//get returns that token, and sets buffer to empty.
	}

	char ch;
	*calc_string >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)
	switch (ch) {
	case ';': 		//to end the calculation
	case '(': case ')': case '+': case '-': case '*': case '/': case '!':
		return Token(ch);						//Each operator undergoes no change
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8':case '9':
	{
		calc_string->putback(ch);         //Puts back the digit into input stream
		double val;
		*calc_string >> val; 		//dereferences the input stream pointer, and reads in the value
		return Token('8', val);   // kind 8 represents a digit.
	}
	default:
		return Token('8',0);
	}
}
