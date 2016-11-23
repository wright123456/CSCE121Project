#include "std_lib_facilities_4.h"
#include "get_top_score.h"
#include "Simple_window.h"
#include "GUI.h"
#include "Graph.h"
#include "Point.h"



bool final_window=true;


score::score(string initials, float score_num)
	:initials(initials), score_num(score_num) {}
score::score()
	:initials("N/A"), score_num(0) {}

score::~score() {}


void update_high_score(vector<score>& scoreboard, score& current)
{
	for (unsigned int i = 0; i <= 4; ++i)
	{
		if (current.get_score_num() > scoreboard[i].get_score_num())
		{

			scoreboard.insert(scoreboard.begin() + i, current);
			return;

		}
	}
}



vector<score> update_scoreboard(int scoreboard_num, score current, bool update)
{
	score temp{ "AJW", 15000 };
	float single_score;
	string single_initials;
	vector<float> score_temp;
	vector<string> initials_temp;
	vector<score> high_score;
	vector<string> scoreboard_names = { "scoreboard_3.txt", "scoreboard_4.txt", "scoreboard_5.txt",
		"scoreboard_5.txt","scoreboard_6.txt","scoreboard_7.txt" }; // Scoreboards for different difficulties
	ifstream ifstr{ scoreboard_names[scoreboard_num - 3] };
	for (unsigned int i = 0; i <= 4; ++i) // Reading top five scores to a vector
	{
		ifstr >> single_initials >> single_score;
		initials_temp.push_back(single_initials);
		score_temp.push_back(single_score);
		temp = score{ initials_temp[i],score_temp[i] };
		high_score.push_back(temp);
	}
	ifstr.close();
	ofstream ofstr{ scoreboard_names[scoreboard_num - 3] };
	if (update == true)
		update_high_score(high_score, current); // If it is a high score, it is placed in the vector
	for (unsigned int i = 0; i <= high_score.size() - 1; ++i) // Writing to the save file
	{
		ofstr << high_score[i].get_initials() << "      " << high_score[i].get_score_num() << std::endl;
	}
	return high_score;
}




Score_Window::Score_Window(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	next_button{ Point{0,0}, 120, 50, "Next",
		[](Address, Address pw) {reference_to<Score_Window>(pw).next(); } },
	quit_button{ Point{0,0 }, 120, 50, "Quit",
		[](Address, Address pw) {reference_to<Score_Window>(pw).quit(); } },
	scoreboard_box{ Point{500,350  }, 120, 50, "Scoreboard Number(3-7)" },
	initials_box{ Point{ 500,500 }, 120, 50, "Initials" },
	score_text{ Point{600,50},"Score" },
	initials_text{ Point{400,50},"Initials" }
	



{
	if (final_window == false)
	{
		attach(next_button);
		attach(scoreboard_box);
		attach(initials_box);
	}
	else
	{
		Score_Window::next();
	}
}



void Score_Window::next()
{
	if (final_window == false)
	{
		int scoreboard_number = scoreboard_box.get_int();
		string initials_get{ initials_box.get_string() };
		attach(*(new Text{ Point{400,400},initials_get }));
		detach(initials_box);
		detach(scoreboard_box);
		detach(next_button);
	}
	attach(quit_button);
	attach(score_text);
	attach(initials_text);
	score John = { "ast",55 };
	Vector<Text*> scores_text;
	Vector<Text*> initials_text;
	Vector<score> scoreboard = update_scoreboard(3, John, false);
	for (unsigned int i = 0; i <= 4; ++i)
	{
		scores_text.push_back(new Text{ Point{600,50 * i + 100},to_string(scoreboard[i].get_score_num()) });
		initials_text.push_back(new Text{ Point{400,50 * i + 100},scoreboard[i].get_initials() });
		attach(*(scores_text[scores_text.size() - 1]));
		attach(*(initials_text[initials_text.size() - 1]));
	}
	redraw();
}
void Score_Window::quit()
{
	hide();
}

