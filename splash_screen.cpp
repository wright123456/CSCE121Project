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
	
	void start();
	void play();
	
	static void cb_start(Address, Address window);
	static void cb_play(Address, Address window);
};

Splash_window::Splash_window(Point xy, int w, int h, const string& title)
	:Window(xy, w, h, title),
	
	start_button(Point(440,650), 120, 50, "Start", cb_start),
	play_button(Point(440,650), 120, 50, "Play", cb_play),
	back(Point(0,0),"background.jpg"),
	white(Point(300,100),"white.jpg"),
	t0(Point(350,200),"The Super Adder"),
	t1(Point(310, 300),"Matt Whitman"),
	t2(Point(450,300),"Lane Wright"),
	t3(Point(575,300),"Alex Westby"),
	t4(Point(420,250),"Team #16"),
	t5(Point(410,100),"Objective:"),
	t6(Point(120,130),"You will be given 3-7 tiles, each labeled with a number or an operator."),
	t7(Point(120,150),"to yield the highest arithmetic value. For example, the three tiles '3', '5' and '+' could be rearranged to"),
	t8(Point(120,170),"'3+5=8', '5+3=8', +35=35', or +53=53. Since +53 has the highest value, that is the best move. If '35+' or 53+"),
	t9(Point(120,190),"is chosen, the score is zero since that is not a 'well-formed formula' in arithmetic (illegal move).")
{
	t0.set_font_size(40);
	t1.set_font_size(20);
	t2.set_font_size(20);
	t3.set_font_size(20);
	t4.set_font_size(20);
	t5.set_font_size(40);
	t6.set_font_size(20);
	t7.set_font_size(20);
	t8.set_font_size(20);
	t9.set_font_size(20);
	back.set_mask(Point(0,0),1100,650);
	white.set_mask(Point(40,40),400,250);
	attach(back);
	attach(white);
	attach(t0);
	attach(t1);
	attach(t2);
	attach(t3);
	attach(t4);
	attach(start_button);
}

void Splash_window::cb_start(Address, Address pw)
{
	reference_to<Splash_window>(pw).start();
}

void Splash_window::cb_play(Address, Address pw)
{
	reference_to<Splash_window>(pw).play();
}

void Splash_window::start()
{
	detach(back);
	detach(white);
	detach(t0);
	detach(t1);
	detach(t2);
	detach(t3);
	detach(t4);
	detach(start_button);
	
	attach(play_button);
	attach(t5);
	attach(t6);
	attach(t7);
	attach(t8);
	attach(t9);
	
	redraw();
}

void Splash_window::play()
{
	
	redraw();
}

int main()
{
	Splash_window win(Point(100,100), 1000, 700, "Super Adder Group #16");
	return gui_main();
}