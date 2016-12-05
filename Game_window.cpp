#include "Game_window.h"
#include "get_top_score.h"

unsigned int rseed = 1;		//assigns initial seed value for the random number generator

Game_window::Game_window(Point xy ,int w, int h, const string& title) :
	Window(xy,w,h,title),
	evaluate_but(Point{500,400},90,40,"Evaluate",cb_evaluate)
{
	difficulty = get_scoreboard_number();				//Gets the user assigned difficulty value
	set_tile_values();									//Gets the labels (operators/operands) for the tiles
	set_tiles();										//Creates the tiles.
}

void Game_window::set_tile_values()						//Generates the values to be translated to the tile labels.
{
	
	vector<int> iterator = {0,1,2,3,4,5,6};
	int k = rand();
	srand(rseed);										//Sets the seed for rand to use.
	rseed = rseed * k;									//Changes the value of seed for the rand num generator
	for(auto i:iterator)
	{
		int a = rand() % 16;
		tile_nums.push_back(a);
	}	
	translate_value();			
}

void Game_window::translate_value()						//Translates a value to the label of a button
{														//Longer than 24 lines, because I couldn't find a
	for(int i = 0; i < tile_nums.size(); ++i)			//simpler way to do the various checks to make sure
	{													//the expressions would be valid.
		switch(tile_nums[i]){
			case 0: case 1: case 2: case 3: case 4:		//If its a num 1-9, convert to string
			case 5: case 6: case 7: case 8: case 9:
			tile_value = to_string(tile_nums[i]);labels.push_back(tile_value); ++num_digits;break;
			case 10: 									
				if(num_digits < num_ops)				//Checks if there are more operators than digits
				{										//If so, then pushback a number between 0-10 instead.
					string a = to_string(rand()%10);
					labels.push_back(a);
					++num_digits;
				}
				else
				{
					tile_value = "+";
					labels.push_back(tile_value);
					++num_ops;
				}
				break;
			case 11: 
				if(num_digits < num_ops)
				{
					string a = to_string(rand()%10);
					labels.push_back(a);
					++num_digits;
				}
				else
				{
					tile_value = "-";
					labels.push_back(tile_value);
					++num_ops;
				}
				break;
			case 12: 
				if(num_digits < num_ops)
				{
					string a = to_string(rand()%10);
					labels.push_back(a);
					++num_digits;
				}
				else
				{
					tile_value = "*";
					labels.push_back(tile_value);
					++num_ops;
				}
				break;
			case 13: 
				if(num_digits < num_ops)
				{
					string a = to_string(rand()%10);
					labels.push_back(a);
					++num_digits;
				}
				else
				{
					tile_value = "/";
					labels.push_back(tile_value);
					++num_ops;
				}
				break;
			case 14: 
				if((labels.size() == difficulty-1) || (difficulty < 5))	//Check if the last tile displayed is a '('
				{														//if so, then put a number 0-10 instead
					string a = to_string(rand()%10);
					labels.push_back(a);
					++num_digits;
				}
				else
				{
					labels.push_back("(");					//If given '('
					labels.push_back(")");					//Make sure next one is ')'
					++num_ops;
					++i;
				}
				break;
			case 15:
				if(num_digits < num_ops)
				{
					string a = to_string(rand()%10);
					labels.push_back(a);
					++num_digits;
				}
				else
				{
					tile_value = "!";
					labels.push_back(tile_value);
					++num_ops;
				}
				break;
		}
	}
}

void Game_window::set_tiles()								//Creates the buttons with the appropriate labels.
{
	tiles.push_back(new Button(Point{150,10},90,90,labels[0],cb_move1));
	tiles.push_back(new Button(Point{250,10},90,90,labels[1],cb_move2));
	tiles.push_back(new Button(Point{350,10},90,90,labels[2],cb_move3));
	tiles.push_back(new Button(Point{450,10},90,90,labels[3],cb_move4));
	tiles.push_back(new Button(Point{550,10},90,90,labels[4],cb_move5));
	tiles.push_back(new Button(Point{650,10},90,90,labels[5],cb_move6));
	tiles.push_back(new Button(Point{750,10},90,90,labels[6],cb_move7));
	
	for(auto i = 0; i < difficulty; ++i)
	{
		attach(tiles[i]);									//Attaches up to (difficulty) many buttons.
	}
	redraw();
}


int Game_window::x_move(Button* tile)						//Find how much to move x button in x direction to formula line in
{
	int current_x = tile->loc.x;							//Get current x position
	int desired_x = clicks*100 + 150;
	int move_x;
	++clicks;
	if((clicks > difficulty)||(tile->loc.y > 200))									//If all tiles have been moved, don't move again
	{
		move_x =0;
		--clicks;
	}
	else if(clicks <= difficulty)
	{
		final_string_vec.push_back(tile->label);			//Pushback the label of the button
		move_x = desired_x - current_x;						//Value of how much button needs to move in x-direction
		
		if(clicks == difficulty)								//If it is the last tile clicked
		{														//concatenate the strings to make one final one.
			final_string = final_string_vec[0];
			for(int n = 1; n < final_string_vec.size(); ++n)	
			{
				final_string = final_string + final_string_vec[n];	
				final_value = 1;
			}
			
			if(final_string_vec[difficulty-1] == "+" || final_string_vec[difficulty-1] == "-" ||	//Check if the last tile is an operand
				final_string_vec[difficulty-1] == "*" ||final_string_vec[difficulty-1] == "/"	)	//If so, the final value = 0
			{
				final_value = 0;
			}
			
			attach(evaluate_but);						//Attach the button to evaluate the expression from the formula line.
			final_string = final_string + ";";			//Add semi-colon to end of the string for the calculator.
		}		
	}
	return move_x;
	
}

int Game_window::y_move(Button* tile)				//Find how much to move button in y direction to formula line
{
	int current_y = tile->loc.y;
	if(current_y < 50)
	{
		return 500;
	}
	else
	{
		return 0;
	}
}

void Game_window::cb_move1(Address, Address pw)			//Callback and move functions for each tile
{  
	reference_to<Game_window>(pw).move1();
}
void Game_window::move1()
{
	int dist_x = x_move(&tiles[0]);
	int dist_y = y_move(&tiles[0]);
	tiles[0].move(dist_x,dist_y);
}
void Game_window::cb_move2(Address, Address pw)
{  
	reference_to<Game_window>(pw).move2();
}
void Game_window::move2()
{
	int dist_x = x_move(&tiles[1]);
	int dist_y = y_move(&tiles[1]);
	tiles[1].move(dist_x,dist_y);
}
void Game_window::cb_move3(Address, Address pw)
{  
	reference_to<Game_window>(pw).move3();
}
void Game_window::move3()
{
	int dist_x = x_move(&tiles[2]);
	int dist_y = y_move(&tiles[2]);
	tiles[2].move(dist_x,dist_y);
}
void Game_window::cb_move4(Address, Address pw)
{  
	reference_to<Game_window>(pw).move4();
}
void Game_window::move4()
{
	int dist_x = x_move(&tiles[3]);
	int dist_y = y_move(&tiles[3]);
	tiles[3].move(dist_x,dist_y);
}
void Game_window::cb_move5(Address, Address pw)
{  
	reference_to<Game_window>(pw).move5();
}
void Game_window::move5()
{
	int dist_x = x_move(&tiles[4]);
	int dist_y = y_move(&tiles[4]);
	tiles[4].move(dist_x,dist_y);
}
void Game_window::cb_move6(Address, Address pw)
{  
	reference_to<Game_window>(pw).move6();
}
void Game_window::move6()
{
	int dist_x = x_move(&tiles[5]);
	int dist_y = y_move(&tiles[5]);
	tiles[5].move(dist_x,dist_y);
}
void Game_window::cb_move7(Address, Address pw)
{  
	reference_to<Game_window>(pw).move7();
}
void Game_window::move7()
{
	int dist_x = x_move(&tiles[6]);
	int dist_y = y_move(&tiles[6]);
	tiles[6].move(dist_x,dist_y);
}


void Game_window::cb_evaluate(Address,Address pw)
{
	reference_to<Game_window>(pw).evaluate();
}


int Game_window::evaluate()							//Evaluate the expression from the formula line
{
	detach(evaluate_but);
	redraw();	
	final_string = "0"+final_string;				//Adds "0" to beginning of string to account for '+35' input
	istringstream calc_string(final_string);		//Converts the final string to an input stream for the calculator
	Token_stream ts(&calc_string);					//Create a Token_stream of calc_string
	
	while (calc_string) {
		Token t = ts.get();
		if((val == 0.2223) || (invalid_factorial == true)){			//Checks if there were any errors during the calculations
			final_val = 0;											//If so, the final value = 0
			break;
		}
		else{
			if (t.kind == 'q') break; // 'q' for quit
			if (t.kind == ';'){        // ';' for "print now"
				final_val = val;
				break;
			}
			else
				ts.putback(t);
				val = expression(&ts);				//Pass the address of a Token_stream into the calculations
		}
	}
	
	labels.clear();										//Clear vectors labels and tile_nums
	tile_nums.clear();
	
	set_user_score(final_val);							//Outputs user score for the scoreboard
	
	hide();												//Hides current window
	final_window_truth(true);
	Score_Window window2{Point{100,100},1000,700,"" };	//Creates new window for the scoreboard
	return gui_main();
}


double Game_window::primary(Token_stream* ts_ptr)
{
	Token t = ts_ptr->get();
	switch (t.kind) {
	case '(':    // handle '(' expression ')'
	{
		double d = expression(ts_ptr);
		t = ts_ptr->get();
		return d;
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
double Game_window::term(Token_stream* ts_ptr)
{
	double left = primary(ts_ptr);
	if (left == 0.2223) 
		return 0.2223;
	Token t = ts_ptr->get();        // get the next token from token stream

	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary(ts_ptr);
			t = ts_ptr->get();
			break;
		case '/':
		{
			double d = primary(ts_ptr);
			if (d == 0) return 0.2223;//error("divide by zero");
			left /= d;
			t = ts_ptr->get();
			break;
		}
		case '!':
		{
			int factorial = left;	//convert to int for switch case
			if(left >= 10){invalid_factorial == true; return 0.2223;}//error("can only perform factorial for values less than 10");
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
			t = ts_ptr->get();
			break;
		}
		default:
			ts_ptr->putback(t);     // put t back into the token stream
			return left;
		}
	}
}

//------------------------------------------------------------------------------

// deal with + and -
double Game_window::expression(Token_stream* ts_ptr)
{
	double left = term(ts_ptr);      // read and evaluate a Term
							   //closed parenthese on term
	if(left == 0.2223)
		return 0.2223;
	Token t = ts_ptr->get();        // get the next token from token stream

	while (true) {
		switch (t.kind) {
		case '+':
			left += term(ts_ptr);    // evaluate Term and add
			t = ts_ptr->get();
			break;
		case '-':
			left -= term(ts_ptr);    // evaluate Term and subtract
			t = ts_ptr->get();	// this subtraction case was the same as addition case
			break;	
		default:
			ts_ptr->putback(t);     // put t back into the token stream
			return left;       // finally: no more + or -: return the answer
		}
	}
}

//------------------------------------------------------------------------------

