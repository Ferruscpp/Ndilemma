#include <iostream>
#include <vector>
#include <random>
#include "Ndilemma_game.h"
#include "all_strategies.h"
#include "Tournament.cpp"
using namespace std;


int main()
{
	int number_of_strategies = 2;
	vector<strategy_type> types_vec;
	for (int i = 0; i < number_of_strategies; i++)
	{
		types_vec.push_back(static_cast<strategy_type>(i));
	}
	types_vec.push_back(static_cast<strategy_type>(0));
	types_vec.push_back(static_cast<strategy_type>(0));
	Tournament tournament(types_vec);
	tournament.start();
	return 0;
}