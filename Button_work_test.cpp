#include "Game_window.h"
#include "std_lib_facilities_4.h"
#include "GUI.h"
#include "Graph.h"
#include "Simple_window.h"

int main(){
	Game_window game{Point{0,0},1000,700,"Select Your Difficulty"};
	return gui_main();
}