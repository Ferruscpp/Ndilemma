#include <iostream>
#include <vector>
#include <random>
#include "Ndilemma_game.h"
#include "all_strategies.h"
#include "Tournament.h"
using namespace std;


int main()
{
	int number_of_strategies = 29;
	vector<strategy_type> types_vec;
	for (int i = 0; i < min(number_of_strategies, 20); i++)
	{
		types_vec.push_back(static_cast<strategy_type>(i));
	}
	for (int i = 24; i < number_of_strategies; i++)
	{
		types_vec.push_back(static_cast<strategy_type>(i));
	}
	Tournament tournament(types_vec);
	tournament.start();
	return 0;
}