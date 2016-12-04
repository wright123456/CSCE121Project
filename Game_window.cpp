#include "Game_window.h"

Game_window::Game_window(Point xy ,int w, int h, const string& title) :
	Window(xy,w,h,title)
{
	difficulty =  7 /*get_scoreborard_number()*/;
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
	for(int i = 0; i < 7; ++i)
	{
		tile_val = randint();
		translate_value();
	}
}

void Game_window::translate_value()
{	
	switch(tile_val){
		case 0: case 1: case 2: case 3: case 4:
		case 5: case 6: case 7: case 8: case 9:
		tile_value = to_string(tile_val);break;
		case 10: tile_value = "+";break;
		case 11: tile_value = "-";break;
		case 12: tile_value = "*";break;
		case 13: tile_value = "/";break;
		case 14: tile_value = "(";break;
		case 15: tile_value = ")";break;
	}
	labels.push_back(tile_value);
}

void Game_window::set_tiles()
{
	tiles.push_back(new Button(Point{0,10},90,90,labels[0],cb_move1));
	tiles.push_back(new Button(Point{100,10},90,90,labels[1],cb_move2));
	tiles.push_back(new Button(Point{200,10},90,90,labels[2],cb_move3));
	tiles.push_back(new Button(Point{300,10},90,90,labels[3],cb_move4));
	tiles.push_back(new Button(Point{400,10},90,90,labels[4],cb_move5));
	tiles.push_back(new Button(Point{500,10},90,90,labels[5],cb_move6));
	tiles.push_back(new Button(Point{600,10},90,90,labels[6],cb_move7));
	
	for(auto i = 0; i < difficulty; ++i)
	{
		attach(tiles[i]);
	}
	redraw();
}


int Game_window::x_move(Button* tile)
{
	int current_x = tile->loc.x;
	int desired_x = clicks*100;
	clicks++;
	
	int move_x = desired_x - current_x;
	
	final_string_vec.push_back(tile->label);
	if(clicks == difficulty)
	{
		final_string = final_string_vec[0];
		
		for(int n = 1; n < final_string_vec.size(); ++n)
		{
			final_string = final_string + final_string_vec[n];
		}
		
		cout << "Final string is: " << final_string << endl;
		
	}		
	return move_x;
}

void Game_window::cb_move1(Address, Address pw)
{  
	reference_to<Game_window>(pw).move1();
}
void Game_window::move1()
{
	int dist = x_move(&tiles[0]);
	tiles[0].move(dist,500);
}
void Game_window::cb_move2(Address, Address pw)
{  
	reference_to<Game_window>(pw).move2();
}
void Game_window::move2()
{
	int dist = x_move(&tiles[1]);
	tiles[1].move(dist,500);
}
void Game_window::cb_move3(Address, Address pw)
{  
	reference_to<Game_window>(pw).move3();
}
void Game_window::move3()
{
	int dist = x_move(&tiles[2]);
	tiles[2].move(dist,500);
}
void Game_window::cb_move4(Address, Address pw)
{  
	reference_to<Game_window>(pw).move4();
}
void Game_window::move4()
{
	int dist = x_move(&tiles[3]);
	tiles[3].move(dist,500);
}
void Game_window::cb_move5(Address, Address pw)
{  
	reference_to<Game_window>(pw).move5();
}
void Game_window::move5()
{
	int dist = x_move(&tiles[4]);
	tiles[4].move(dist,500);
}
void Game_window::cb_move6(Address, Address pw)
{  
	reference_to<Game_window>(pw).move6();
}
void Game_window::move6()
{
	int dist = x_move(&tiles[5]);
	tiles[5].move(dist,500);
}
void Game_window::cb_move7(Address, Address pw)
{  
	reference_to<Game_window>(pw).move7();
}
void Game_window::move7()
{
	int dist = x_move(&tiles[6]);
	tiles[6].move(dist,500);
}






