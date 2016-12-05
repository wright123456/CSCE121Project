#ifndef GET_TOP_SCORE_H
#define GET_TOP_SCORE_H
#include "std_lib_facilities_4.h"
#include "Simple_window.h"
#include "GUI.h"
#include "Graph.h"
#include "Point.h"


int get_scoreboard_number();
void set_user_score(float);
void final_window_truth(bool truth_update);

class bad_scoreboard_num{};

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
	string initials_a;
	
private:
	Vector<score> scoreboard;
	Graph_lib::Button next_button;
	Graph_lib::Button quit_button;
	Graph_lib::Button again_button;
	Graph_lib::Button scoreboard_next_button;
	In_box scoreboard_box;
	In_box initials_box;
	void next();
	void quit();
	int again();
	int scoreboard_next();
	void attach_scores();
	Text  initials_text, score_text, score_text_current, initials_text_current;
};



void update_high_score(vector<score>& scoreboard, score& current);
vector<score> scoreboard_output(score current, int scoreboard_num, bool update, vector<score> high_score);
vector<score> scoreboard_input(int scoreboard_num);

Vector<score> update_scoreboard(int scoreboard_num, score current);




#endif