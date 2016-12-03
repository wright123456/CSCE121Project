#include "std_lib_facilities_4.h"
#include "get_top_score.h"
#include "Simple_window.h"
#include "GUI.h"
#include "Graph.h"
#include "Point.h"
#include "splash_screen.h"


float user_score;
string user_initials = "hello";
int scoreboard_number = 6;
int get_scoreboard_number()
{
	return scoreboard_number;
}

void set_user_score(float score_a)
{
	user_score = score_a;
}

bool final_window = true;
void final_window_truth(bool truth_update)
{
	final_window = truth_update;
}


score::score(string initials, float score_num)
	:initials(initials), score_num(score_num) {}
score::score()
{
	initials = "N/A";
	score_num = 0;
}

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
vector<score> scoreboard_input(int scoreboard_num)
{
	score temp{ "AJW", 15000 };
	float single_score;
	string single_initials;
	vector<float> score_temp;
	vector<string> initials_temp;
	vector<score> high_score;
	vector<string> scoreboard_names = { "scoreboard_3.txt", "scoreboard_4.txt", "scoreboard_5.txt",
		"scoreboard_5.txt","scoreboard_6.txt","scoreboard_7.txt" };
	ifstream ifstr{ scoreboard_names[scoreboard_num - 2] };
	if (ifstr.fail())
		throw bad_scoreboard_num{};
	for (unsigned int i = 0; i <= 4; ++i) // Reading top five scores to a vector
	{
		ifstr >> single_initials >> single_score;
		if (single_initials == "")
			single_initials = "N/A";
		initials_temp.push_back(single_initials);
		score_temp.push_back(single_score);
		temp = score{ initials_temp[i],score_temp[i] };
		high_score.push_back(temp);
	}
	ifstr.close();
	return high_score;
}

vector<score> scoreboard_output(score current, int scoreboard_num, bool update, vector<score> high_score)
{
	vector<string> scoreboard_names = { "scoreboard_3.txt", "scoreboard_4.txt", "scoreboard_5.txt",
	"scoreboard_5.txt","scoreboard_6.txt","scoreboard_7.txt" };
	ofstream ofstr{ scoreboard_names[scoreboard_num - 2] };
	if (update == true)
		update_high_score(high_score, current); // If it is a high score, it is placed in the vector
	for (unsigned int i = 0; i <= high_score.size() - 1; ++i) // Writing to the save file
	{
		ofstr << high_score[i].get_initials() << "      " << high_score[i].get_score_num() << std::endl;
	}
	return high_score;
}

vector<score> update_scoreboard(int scoreboard_num, score current, bool update)
{
	vector<score> high_score = scoreboard_input(scoreboard_num);
	high_score = scoreboard_output(current, scoreboard_num, update, high_score);
	return high_score;
}




Score_Window::Score_Window(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	next_button{ Point{0,0}, 120, 50, "Next",
		[](Address, Address pw) {reference_to<Score_Window>(pw).next(); } },
	quit_button{ Point{0,0 }, 120, 50, "Quit",
		[](Address, Address pw) {reference_to<Score_Window>(pw).quit(); } },
	again_button{ Point{880,0 }, 120, 50, "Play Again",
		[](Address, Address pw) {reference_to<Score_Window>(pw).again(); } },
	scoreboard_next_button{ Point{0,0}, 120, 50, "Next",
		[](Address, Address pw) {reference_to<Score_Window>(pw).scoreboard_next(); } },
	scoreboard_box{ Point{500,350  }, 120, 50, " Difficulty(3-7)" },
	initials_box{ Point{ 500,500 }, 120, 50, "Initials" },
	score_text{ Point{600,50},"Score" },
	initials_text{ Point{400,50},"Initials" },
	initials_text_current{ Point{ 400,400 },user_initials },
	score_text_current{ Point{ 600,400 },to_string(user_score) }



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

void Score_Window::attach_scores()
{
	score John = { user_initials,user_score };
	Vector<Text*> scores_text_vec;
	Vector<Text*> initials_text_vec;
	Vector<score> scoreboard = update_scoreboard(scoreboard_number, John, false);
	for (unsigned int i = 0; i <= 4; ++i)
	{
		scores_text_vec.push_back(new Text{ Point{ 600,50u * i + 100u },to_string(scoreboard[i].get_score_num()) });
		initials_text_vec.push_back(new Text{ Point{400,50u * i + 100u},scoreboard[i].get_initials() });
		attach(*(scores_text_vec[scores_text_vec.size() - 1]));
		attach(*(initials_text_vec[initials_text_vec.size() - 1]));
	}
	redraw();
}

void Score_Window::next()
{
	if (final_window == false)
	{
		scoreboard_number = scoreboard_box.get_int();
		user_initials = initials_box.get_string();
		cout << initials_a;
		attach(*(new Text{ Point{400,400},user_initials }));
		detach(initials_box);
		detach(scoreboard_box);
		detach(next_button);
		attach(scoreboard_next_button);
	}
	else
	{
		attach(again_button);
		attach(quit_button);
		attach(initials_text_current);
		attach(score_text_current);
	}
	attach(score_text);
	attach(initials_text);
	attach_scores();
}
void Score_Window::quit()
{
	score John = { user_initials,user_score };
	Vector<score> scoreboard2 = update_scoreboard(scoreboard_number, John, true);
	hide();

}

int Score_Window::again()
{
	score John = { user_initials,user_score };
	Vector<score> scoreboard2 = update_scoreboard(scoreboard_number, John, true);
	hide();
	//Insert for window to start again
	Splash_window begin{Point{100,100},1000,700,"" };
	return gui_main();
}

void Score_Window::scoreboard_next()
{
	hide();
	//Insert code for next window/to start game
}