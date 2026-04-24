#pragma once
#include "Ndilemma_game.h"
#include "all_strategies.h"
#include <memory>
#include <conio.h>
using namespace std;

enum class strategy_type
{
	altruist,
	drunkard,
	pirate,
	sly_pirate,
	judge,
	sly_judge,
	stupid_judge,
	ostap,
	accountant,
	probe,
	punisher,
	advocate,
	conformist,
	sly_conformist,
	rebel,
	suspicious,
	madman,
	nervous,
	provocateur,
	pavlov,
	Spectrum_Zero,
	Spectrum_Phantom,
	Spectrum_Lite,
	Spectrum_Aero,
	sentinel,
	keeper,
	scrapper,
	zealot,
	inquisitor
};

unique_ptr<Player> create_player(strategy_type id);

struct Tournament
{
	mt19937 gen;
	uniform_int_distribution<> distrib;
	int total_moves;
	int players_cnt;
	vector<ll> score;
	vector<strategy_type> types_vec;
	Tournament(vector<strategy_type>& _types_vec);
	void generate_groups(vector<int>& group, int group_size, int last_number);
	void start();
	int count_s();
	void start_evo();
};
