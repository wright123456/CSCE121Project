#ifndef GET_TOP_SCORE_H
#define GET_TOP_SCORE_H
#include "std_lib_facilities_4.h"
#include "Simple_window.h"
#include "GUI.h"
#include "Graph.h"
#include "Point.h"
extern bool final_window;

class score
{
public:
	score(string initials, float num_score);
	score();
	~score();
	float get_score_num()
	{
		return score_num;
	}
	string get_initials()
	{
		return initials;
	}

private:
	float score_num;
	string initials;


};

struct Score_Window :Graph_lib::Window
{
	Score_Window(Point xy, int w, int h, const string& title);
	float get_user_score(float score);
	
private:
	Vector<score> scoreboard;
	Graph_lib::Button next_button;
	Graph_lib::Button quit_button;
	In_box scoreboard_box;
	In_box initials_box;
	void next();
	void quit();
	Text  initials_text, score_text;
	string initials_get;

	score user;
};



void update_high_score(vector<score>& scoreboard, score& current);

Vector<score> update_scoreboard(int scoreboard_num, score current);




#endif