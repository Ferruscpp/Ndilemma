#include <iostream>
#include <vector>
#include <random>
#include "Ndilemma_game.h"
#include "all_strategies.h"
#include "Tournament.h"
using namespace std;


int main()
{
	//one tour
	vector<Player*> vec;
	vec.push_back(new altruist);
	vec.push_back(new drunkard);
	Ndilemma game(100, vec, true);
	game.start();
	cout << endl;
	//tournament
	int number_of_strategies = 2;
	vector<strategy_type> types_vec;
	for (int i = 0; i < number_of_strategies; i++)
	{
		types_vec.push_back(static_cast<strategy_type>(i));
	}
	Tournament tournament(types_vec);
	tournament.start();
	return 0;
}