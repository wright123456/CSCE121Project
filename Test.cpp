#include "std_lib_facilities_4.h"
#include "get_top_score.h"
#include "Simple_window.h"
#include "GUI.h"
#include "Point.h"
#include "Graph.h"
#include "splash_screen.h"
int main()
{

Splash_window win{ Point{100,100},1000,700,"" };
return gui_main();

}