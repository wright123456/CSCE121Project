#include "std_lib_facilities_4.h"
#include "Token.h"
class Token_stream {
public:
	Token_stream(istringstream* calc_stringptr);   // make a Token_stream that reads from cin
	Token get();      // get a Token (get() is defined elsewhere)
	void putback(Token t);    // put a Token back
	istringstream* calc_string;
	
private:
	bool full;        // is there a Token in the buffer?
	Token buffer;     // here is where we keep a Token put back using putback()
};