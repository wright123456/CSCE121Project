#include "std_lib_facilities_4.h"
#include "get_top_score.h"
#include "Simple_window.h"
#include "GUI.h"
#include "Point.h"
#include "Graph.h"

int main()
{
	final_window = true;
	Score_Window win{ Point{100,100},1000,700,"stuff" };


	return gui_main();
} 