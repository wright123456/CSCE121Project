#include "splash_screen.h"

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

class Token_stream {
public:
	Token_stream();   // make a Token_stream that reads from cin
	Token get();      // get a Token (get() is defined elsewhere)
	void putback(Token t);    // put a Token back
private:
	bool full;        // is there a Token in the buffer?
	Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
	:full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
	if (full) error("putback() into a full buffer");
	buffer = t;       // copy t to buffer
	full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
	if (full) {       // do we already have a Token ready?
					  // remove token from buffer
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch) {
	case ';':    // for "print"
	case 'q':    // for "quit"
	case '(': case ')': case '+': case '-': case '*': case '/': case '!':
		return Token(ch);// let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8':case '9':
	{
		cin.putback(ch);         // put digit back into the input stream
		double val;
		cin >> val; 		// read a floating-point number
		return Token('8', val);   // let '8' represent "a number"
	}
	default:
		error("Bad token");
	}
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback() 

						//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

						//------------------------------------------------------------------------------

						// deal with numbers and parentheses
double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':    // handle '(' expression ')'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') //error("')' expected");
			return 0.2223;
	}
	case '8':            // we use '8' to represent a number
		return t.value; 		// return the number's value	
	default:
		//error("primary expected");
		return 0.2223;
	}
}

//------------------------------------------------------------------------------

// deal with *, /, %, and !
double term()
{
	double left = primary();
	if (left == 0.2223) 
		return 0.2223;
	Token t = ts.get();        // get the next token from token stream

	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) return 0.2223;//error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		case '!':
		{
			int factorial = left;	//convert to int for switch case
			if(left >= 10) return 0.2223;//error("can only perform factorial for values less than 10");
			switch(factorial){
				case 9:
					left = left * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1;
					break;
				case 8:
					left = left * 7 * 6 * 5 * 4 * 3 * 2;
					break;
				case 7:
					left = left * 6 * 5 * 4 * 3 * 2;
					break;
				case 6:
					left = left * 5 * 4 * 3 * 2;		//tried to do a for loop to handle
					break;								//the factorial calculator, switched
				case 5:									//to a switch case because the for
					left = left * 4 * 3 * 2;			//loop would output "-inf" on every
					break;								//factorial and I could not 
				case 4: 								//find out why. decided it would
					left = left * 3 * 2;				//be easier to hard code the switch
					break;								//case instead of finding the issue
				case 3:									//with the for loop.
					left = left * 2 * 1;
					break;
				case 2:
					left = left;
					break;
				case 1:
					left = left;
					break;
			}
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);     // put t back into the token stream
			return left;
		}
	}
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
	double left = term();      // read and evaluate a Term
							   //closed parenthese on term
	if(left == 0.2223)
		return 0.2223;
	Token t = ts.get();        // get the next token from token stream

	while (true) {
		switch (t.kind) {
		case '+':
			left += term();    // evaluate Term and add
			t = ts.get();
			break;
		case '-':
			left -= term();    // evaluate Term and subtract
			t = ts.get();	// this subtraction case was the same as addition case
			break;	
		default:
			ts.putback(t);     // put t back into the token stream
			return left;       // finally: no more + or -: return the answer
		}
	}
}

//------------------------------------------------------------------------------

int main()
try
{
	double val;	//defined "val"
	double final_val; //value that will be added to scoreboard
	char start = '0';		//this line and the next 3 lines start the input
	cin.putback(start);		//with a zero. this handles the case that the player
	double start_val;		//starts with an operator (like "+35") without
	Token('8', start_val);	//the calculator function failing
	while (cin) {
		Token t = ts.get();

		if(val == 0.2223){
			final_val = 0;
			cout<<'='<<final_val<<'\n';
		}
		else{
			if (t.kind == 'q') break; // 'q' for quit
			if (t.kind == ';'){        // ';' for "print now"
				final_val = val;
				cout << "=" << final_val << '\n';
			}
			else
				ts.putback(t);
			val = expression();
		}
	}
	keep_window_open();
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}