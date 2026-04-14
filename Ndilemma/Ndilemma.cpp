#include <iostream>
#include <vector>
#include <random>
#include "Ndilemma_game.h"
#include "all_strategies.h"
using namespace std;

int main()
{
	altruist a;
	drunkard b;
	vector<Player*> vec(0, nullptr);
	vec.push_back(&a);
	vec.push_back(&b);
	Ndilemma game(1000, vec, true);
	game.start();
}