#include "Tournament.h"

unique_ptr<Player> create_player(strategy_type id)
{
	switch (id)
	{
	case strategy_type::altruist: return make_unique<altruist>();
	case strategy_type::drunkard: return make_unique<drunkard>();
	}
}

Tournament::Tournament(vector<strategy_type>& _types_vec) : gen((random_device{}())), distrib(1000, 5000), types_vec(_types_vec)
{
	total_moves = distrib(gen);
	players_cnt = types_vec.size();
	score.resize(players_cnt, 0);
}

void Tournament::generate_groups(vector<int>& group, int group_size, int last_number)
{
	if (group.size() == group_size)
	{
		vector<Player*> vec;
		vector<unique_ptr<Player>> storage;
		for (int i = 0; i < players_cnt; i++)
		{
			storage.push_back(create_player(types_vec[i]));
		}
		for (int i = 0; i < group_size; i++)
		{
			vec.push_back(storage[group[i]].get());
		}
		Ndilemma game(total_moves, vec, true);
		vector<ll> _score = game.get_score();
		for (int i = 0; i < group_size; i++)
		{
			score[group[i]] += _score[i];
		}
	}
	else
	{
		for (int i = last_number + 1; i < players_cnt; i++)
		{
			group.push_back(i);
			generate_groups(group, group_size, i);
			group.pop_back();
		}
	}
}

void Tournament::start()
{
	vector<int> group;
	//stage 1
	generate_groups(group, 2, -1);
	//stage 2
	generate_groups(group, 3, -1);
	generate_groups(group, 5, -1);
	//stage 3
	generate_groups(group, 3, -1);

	ll m = 0;
	for (int i = 0; i < players_cnt; i++)
	{
		if (score[i] < score[m])
		{
			m = i;
		}
	}
	vector<unique_ptr<Player>> storage;
	for (int i = 0; i < players_cnt; i++)
	{
		storage.push_back(create_player(types_vec[i]));
	}
	cout << "The WINER: " << *storage[m] << " score:" << score[m] << endl << endl;
	for (int i = 0; i < players_cnt; i++)
	{
		cout << *storage[i] << " score:" << score[i] << endl;
	}
}
