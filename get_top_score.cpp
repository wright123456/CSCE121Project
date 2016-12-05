#include "std_lib_facilities_4.h"
#include "get_top_score.h"
#include "Simple_window.h"
#include "GUI.h"
#include "Graph.h"
#include "Point.h"
#include "splash_screen.h"
#include "Game_window.h"


float user_score;
string user_initials = "hello";
int scoreboard_number = 6;
int get_scoreboard_number() //Used for tiles window to get difficulty
{
	return scoreboard_number;
}

void set_user_score(float score_a) // Used to set score after game
{
	user_score = score_a;
}

bool final_window = true; // If this is true it will only display the last window
void final_window_truth(bool truth_update) 
{
	final_window = truth_update;
}


score::score(string initials, float score_num) // Used to hold scores for scoreboard
	:initials(initials), score_num(score_num) {}
score::score()
{
	initials = "N/A"; // Sets default initials and score
	score_num = 0;
}

score::~score() {}


void update_high_score(vector<score>& scoreboard, score& current) // Compares scores to user score and updates scoreboard
{
	for (unsigned int i = 0; i <= 4; ++i)
	{
		if (current.get_score_num() > scoreboard[i].get_score_num())
		{

			scoreboard.insert(scoreboard.begin() + i, current); // Inserts user score if applicable
			return;

		}
	}
}
vector<score> scoreboard_input(int scoreboard_num)
{
	score temp{ "AJW", 15000 }; // Used to 
	float single_score;
	string single_initials;
	vector<float> score_temp;
	vector<string> initials_temp;
	vector<score> high_score;
	vector<string> scoreboard_names = { "scoreboard_3.txt", "scoreboard_4.txt", "scoreboard_5.txt",
		"scoreboard_5.txt","scoreboard_6.txt","scoreboard_7.txt" };
	fstream f;
	ifstream ifstr{ scoreboard_names[scoreboard_num - 3] };
	if(ifstr.fail() && scoreboard_num>=3 && scoreboard_num<=7  )
		{
		f.open(scoreboard_names[scoreboard_num-3],ios::out);
		for( int i=0; i<=4;++i)
			f<<single_initials<<" "<<fixed<<setprecision(2)<< 0;
		}
	else
	f.close();
	for (unsigned int i = 0; i <= 4; ++i) // Reading top five scores to a vector
	{
		ifstr >> single_initials >> single_score;
		if (single_initials == "" )
			single_initials = "N/A";
		initials_temp.push_back(single_initials);
		score_temp.push_back(single_score);
		temp = score{ initials_temp[i],score_temp[i] };
		high_score.push_back(temp);
	}
	ifstr.close();
	return high_score;
}

vector<score> scoreboard_output(score current, int scoreboard_num, bool update, vector<score> high_score)//This is used to read from scoreboard
{
	vector<string> scoreboard_names = { "scoreboard_3.txt", "scoreboard_4.txt", "scoreboard_5.txt",
	"scoreboard_5.txt","scoreboard_6.txt","scoreboard_7.txt" };
	ofstream ofstr{ scoreboard_names[scoreboard_num - 3] };
	if (update == true)
		update_high_score(high_score, current); // If it is a high score, it is placed in the vector
	for (unsigned int i = 0; i <= high_score.size() - 1; ++i) // Writing to the save file
	{
		ofstr<< high_score[i].get_initials() << "      " <<fixed<<setprecision(2)<< high_score[i].get_score_num() << std::endl;
	}
	return high_score;
}

vector<score> update_scoreboard(int scoreboard_num, score current, bool update)// Uses above two functions to see if scoreboard needs to be updated
{
	vector<score> high_score = scoreboard_input(scoreboard_num);
	high_score = scoreboard_output(current, scoreboard_num, update, high_score);
	return high_score;// TO update scoreboard
}




Score_Window::Score_Window(Point xy, int w, int h, const string& title)// One window for scoreboard and to enter difficulty/initials
	:Window{ xy,w,h,title },
	next_button{ Point{0,0}, 120, 50, "Next",// After they type in initials/difficulty
		[](Address, Address pw) {reference_to<Score_Window>(pw).next(); } },
	quit_button{ Point{0,0 }, 120, 50, "Quit",// Quits game
		[](Address, Address pw) {reference_to<Score_Window>(pw).quit(); } },
	again_button{ Point{880,0 }, 120, 50, "Play Again",// Play the game again
		[](Address, Address pw) {reference_to<Score_Window>(pw).again(); } },
	scoreboard_next_button{ Point{0,0}, 120, 50, "Next",//Next button after score has been displayed
		[](Address, Address pw) {reference_to<Score_Window>(pw).scoreboard_next(); } },
	scoreboard_box{ Point{500,350  }, 120, 50, " Difficulty(3-7)" },
	initials_box{ Point{ 500,500 }, 120, 50, "Initials" },// Box to enter initials
	score_text{ Point{600,50},"Score" },
	initials_text{ Point{400,50},"Initials" },
	initials_text_current{ Point{ 400,400 },user_initials },
	score_text_current{ Point{ 600,400 },to_string(user_score) }



{
	if (final_window == false)//If it is the first window then show difficulty screen
	{
		attach(next_button);
		attach(scoreboard_box);
		attach(initials_box);
	}
	else // if finals screen  then move on to next screen
	{
		Score_Window::next();
	}
}

void Score_Window::attach_scores()//Used to attach the scoreboard
{
	score John = { user_initials,user_score };// Not used if no scoreboard update
	Vector<Text*> scores_text_vec;
	Vector<Text*> initials_text_vec;
	Vector<score> scoreboard = update_scoreboard(scoreboard_number, John, false);// Doesn't update score til later/gets current scores
	for (unsigned int i = 0; i <= 4; ++i)// Drawing scorebaord
	{
		scores_text_vec.push_back(new Text{ Point{ 600,50u * i + 100u },to_string(scoreboard[i].get_score_num()) });
		initials_text_vec.push_back(new Text{ Point{400,50u * i + 100u},scoreboard[i].get_initials() });
		attach(*(scores_text_vec[scores_text_vec.size() - 1]));
		attach(*(initials_text_vec[initials_text_vec.size() - 1]));
	}
	redraw();
}

void Score_Window::next()// Goes to  scoreboard screen 
{
	if (final_window == false) // if not final window it attaches user's name
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
	else // If it is final window it attaches score and initials
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
void Score_Window::quit()// Quits program and updates scoreboard
{
	score John = { user_initials,user_score };
	Vector<score> scoreboard2 = update_scoreboard(scoreboard_number, John, true);
	hide();

}

int Score_Window::again()// Updates scorebaord and allows player to play again
{
	score John = { user_initials,user_score };
	Vector<score> scoreboard2 = update_scoreboard(scoreboard_number, John, true);
	hide();
	//Insert for window to start again
	Splash_window begin{Point{100,100},1000,700,"" };
	return gui_main();
}

int Score_Window::scoreboard_next()// Used to play the game
{
	hide();
	//Insert code for next window/to start actual game
	Game_window win2{Point{100,100},1000,700,"" };
	return gui_main();
}
