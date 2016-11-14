//Matt Whitman
//CSCE 121-506
//Due: September 22, 2016
//hw3pr3.cpp

#include "std_lib_facilities_4.h"

using namespace std::chrono;
//linear congruential pseudorandom number generator
int randint(){
        //use the clock for an initial pseudorandom number
        static long x = time_point_cast<microseconds>(system_clock::now())
			.time_since_epoch().count() & 0x7fffffff; //CORRECTED
        //calculate the next pseudorandom number
        x = (1103515245 * x + 12345) & 0x7fffffff;    //parameters from glibc(?)
        return x;
}

int main()
{
	int i;
	int zeros{0};
	int ones{0};
	int twos{0};
	int threes{0};
	int fours{0};
	int fives{0};
	int sixes{0};
	int sevens{0};
	int eights{0};
	int nines{0};
	for (i=0;i<1000000;++i){	//Run this loop 1 million times
		int x;
		int y;
		x = randint();			//Generate and store random int
		y = x % 10;				//Find ones place of int using remainder when divided by 10
		/*cout<<x<<'\n';
		cout<<y;*/
		switch (y){							//Record the number of each digit in ones place
			case 0: zeros = zeros + 1;
				break;
			case 1: ones = ones + 1;
				break;
			case 2: twos = twos + 1;
				break;
			case 3: threes = threes + 1;
				break;
			case 4: fours = fours + 1;
				break;
			case 5: fives = fives + 1;
				break;
			case 6: sixes = sixes + 1;
				break;
			case 7: sevens = sevens + 1;
				break;
			case 8: eights = eights + 1;
				break;
			case 9: nines = nines + 1;
				break;
		}
	}
	cout<<"There were "<<zeros<<" 0's.\n";	//Display the number of each digit in the ones place
	cout<<"There were "<<ones<<" 1's.\n";
	cout<<"There were "<<twos<<" 2's.\n";
	cout<<"There were "<<threes<<" 3's.\n";
	cout<<"There were "<<fours<<" 4's.\n";
	cout<<"There were "<<fives<<" 5's.\n";
	cout<<"There were "<<sixes<<" 6's.\n";
	cout<<"There were "<<sevens<<" 7's.\n";
	cout<<"There were "<<eights<<" 8's.\n";
	cout<<"There were "<<nines<<" 9's.\n";
	
	return 0;
}