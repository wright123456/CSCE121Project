#include "std_lib_facilities_4.h"
#include "Simple_window.h"
#include "Graph.h"

struct Splash_window : Graph_lib::Window
{
	Splash_window(Point xy, int w, int h, const string& title);
	
private:
	Button start_button;
	Button play_button;
	Image back;
	Image white;
	Text t0; Text t1; Text t2; Text t3; Text t4;
	Text t5; Text t6; Text t7; Text t8; Text t9;
	Text t10;
	
	void start();
	void play();
	
	static void cb_start(Address, Address window);
	static void cb_play(Address, Address window);
};