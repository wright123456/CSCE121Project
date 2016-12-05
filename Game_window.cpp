#include "Game_window.h"
#include "get_top_score.h"



Game_window::Game_window(Point xy ,int w, int h, const string& title) :
	Window(xy,w,h,title),
	evaluate_but(Point{500,400},90,40,"Evaluate",cb_evaluate)
{
	difficulty= get_scoreboard_number();
	set_tile_values();
	set_tiles();
}

int Game_window::randint(){
	using namespace std::chrono;
	//use the clock for an initial pseudorandom number
	static long x = time_point_cast<microseconds>(system_clock::now())
					.time_since_epoch().count() & 0x7fffffff; //CORRECTED
	//calculate teh next pseudorandom number
	x = (1103515245 * x + 12345) & 0x7fffffff;	//parameters from glibc(?)
	
	x = x % 16;
	return x;
}

void Game_window::set_tile_values()
{
	vector<int> iterator = {0,1,2,3,4,5,6};
	for(auto i:iterator)
	{
		tile_nums.push_back(randint());
	}	
	translate_value();
}

void Game_window::translate_value()
{	
	for(int i = 0; i < tile_nums.size(); ++i)
	{
		switch(tile_nums[i]){
			case 0: case 1: case 2: case 3: case 4:
			case 5: case 6: case 7: case 8: case 9:
			tile_value = to_string(tile_nums[i]);labels.push_back(tile_value); ++num_digits;break;
			case 10: 
				/*if(labels.size() == difficulty)
				{
					string a = to_string(randint()%10);
					labels.push_back(a);
					++num_digits;
				}
				*/if(num_digits < num_ops)
				{
					string a = to_string(randint()%10);
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
				/*if(labels.size() == difficulty)
				{
					string a = to_string(randint()%10);
					labels.push_back(a);
				}*/
				if(num_digits < num_ops)
				{
					string a = to_string(randint()%10);
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
				/*if(labels.size() == difficulty)
				{
					string a = to_string(randint()%10);
					labels.push_back(a);
				}
				*/if(num_digits < num_ops)
				{
					string a = to_string(randint()%10);
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
				/*if(labels.size() == difficulty)
				{
					string a = to_string(randint()%10);
					labels.push_back(a);
				}
				*/if(num_digits < num_ops)
				{
					string a = to_string(randint()%10);
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
				if((labels.size() == difficulty-1) || (difficulty < 5))
				{
					string a = to_string(randint()%10);
					labels.push_back(a);
					++num_digits;
				}
				else
				{
					labels.push_back("(");
					labels.push_back(")");
					++num_ops;
					++i;
				}
				break;
			case 15:
				if(num_digits < num_ops)
				{
					string a = to_string(randint()%10);
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

void Game_window::set_tiles()
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
		attach(tiles[i]);
	}
	redraw();
}


int Game_window::x_move(Button* tile)
{
	int current_x = tile->loc.x;
	int desired_x = clicks*100 + 150;
	int move_x;
	clicks++;
	
	if(clicks > difficulty)
	{
		move_x = 0;
	}
	else if(clicks <= difficulty)
	{
		final_string_vec.push_back(tile->label);
		move_x = desired_x - current_x;
		
		if(clicks == difficulty)
		{
			final_string = final_string_vec[0];
			for(int n = 1; n < final_string_vec.size(); ++n)
			{
				final_string = final_string + final_string_vec[n];
				final_value = 1;
			}
			
			if(final_string_vec[difficulty-1] == "+" || final_string_vec[difficulty-1] == "-" ||
				final_string_vec[difficulty-1] == "*" ||final_string_vec[difficulty-1] == "/"	)
			{
				final_value = 0;
				//set_user_score(0);
			}
			
			attach(evaluate_but);
			final_string = final_string + ";";
		}
	}
	
	return move_x;
	
}

int Game_window::y_move(Button* tile)
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

void Game_window::cb_move1(Address, Address pw)
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
int Game_window::evaluate()
{
	detach(evaluate_but);
	redraw();	
	final_string = "0"+final_string;
	istringstream calc_string(final_string);
	Token_stream ts(&calc_string);
	
	//char start = '0';		//this line and the next 3 lines start the input
	//calc_string.putback(start);		//with a zero. this handles the case that the player
	//double start_val = 0;		//starts with an operator (like "+35") without
	//Token('8', start_val);	//the calculator function failing
	
	while (calc_string) {
		Token t = ts.get();
		if((val == 0.2223) || (invalid_factorial == true)){
			final_val = 0;
			cout<<'='<<final_val<<'\n';
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
				val = expression(&ts);
		}
	}
	cout << "Your score is: " << final_val << endl;
	string fin_str = to_string(final_val);
	Button fin_val(Point{400,300},200,100,fin_str,cb_done);
	attach(fin_val);
	for(int k = 0; k < difficulty; ++k)
	{
		detach(tiles[k]);
	}
	redraw();
	labels.clear();
	tile_nums.clear();
	set_user_score(final_val);
	hide();
	final_window_truth(true);
	Score_Window window2{Point{100,100},1000,700,"" };
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

void Game_window::cb_done(Address, Address pw)
{
	reference_to<Game_window>(pw).done();
}

void Game_window::done()
{
	
}
