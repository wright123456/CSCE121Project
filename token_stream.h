#include "std_lib_facilities_4.h"
#include "Token.h"
class Token_stream {
public:
	Token_stream(istringstream* calc_stringptr);   // make a Token_stream that reads from calc_string 
	Token get();      // get a token
	void putback(Token t);    // put a token back into buffer
	istringstream* calc_string;		//calc_string is a pointer to an input stream
	
private:
	bool full;        // Checks if a token is in the buffer
	Token buffer;     // stores a token.=
};