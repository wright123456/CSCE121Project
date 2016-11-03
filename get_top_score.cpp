#include "std_lib_facilities_4.h"


class score
{
public:
	int get_score_num()
	{
		return score_num;
	}
	string get_initials() 
	{
		return initials;
	}
private:
	float score_num;
	std::string initials;
	int position;

};



void is_high_score(vector<score> scoreboard, score current)
{
	for (unsigned int i = 1; i <= 5; ++i)
	{
		if (current.get_score_num() > scoreboard[i - 1].get_score_num())
		{
			scoreboard.insert(scoreboard.begin() + (i - 1), current);
			break;
		}
	}
}

void update_scoreboard(int scoreboard_num, vector<score> high_score, score current)
{
	v
		vector<string> scoreboard_names = { "scoreboard_3.txt", "scoreboard_4.txt", "scoreboard_5.txt","scoreboard_5.txt","scoreboard_6.txt","scoreboard_7.txt" }; // Scoreboards for different difficulties
	fstream fstr{ scoreboard_names[scoreboard_num - 3],ofstream::trunc };
	for (int i = 0; i <= 4; ++i) // Reading top five scores to a vector
	{
		fstr >> high_score[i].initials >> high_score[i].get_score_num();
	}
	is_high_score(high_score, current); // If it is a high score, it is placed in the vector
	for (int i = 0; i <= 4; ++i) // Writing to the save file
	{
		fstr << high_score[i].initials << "      " << high_score[i].get_score_num();
	}

}