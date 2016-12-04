#ifndef GAME_GUARD
#define	GAME_GUARD

#include "std_lib_facilities_4.h"
#include "GUI.h"
#include "Graph.h"
#include "Simple_window.h"

struct Game_window : Graph_lib::Window{
	
	Game_window(Point xy ,int w, int h, const string& title);

	vector<string> labels;
	
	private:
	
		void set_tiles();
		void set_tile_values();
	
		string tile_value;
	
		Vector_ref<Button> tiles;
		int difficulty;
		
		int randint();
		int tile_val;
		
		int clicks = 0;

		int x_move(Button* tile);
		
		vector<string> final_string_vec;
		string final_string;
		
		
		void translate_value();
		
		static void cb_move1(Address, Address pw);
		void move1();
		static void cb_move2(Address, Address pw);
		void move2();
		static void cb_move3(Address, Address pw);
		void move3();
		static void cb_move4(Address, Address pw);
		void move4();
		static void cb_move5(Address, Address pw);
		void move5();
		static void cb_move6(Address, Address pw);
		void move6();
		static void cb_move7(Address, Address pw);
		void move7();
};

#endif