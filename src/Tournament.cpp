#include "Tournament.h"

unique_ptr<Player> create_player(strategy_type id)
{
	switch (id)
	{
	case strategy_type::altruist: return make_unique<altruist>();
	case strategy_type::drunkard: return make_unique<drunkard>();
	case strategy_type::pirate: return make_unique<pirate>();
	case strategy_type::sly_pirate: return make_unique<sly_pirate>();
	case strategy_type::judge: return make_unique<judge>();
	case strategy_type::sly_judge: return make_unique<sly_judge>();
	case strategy_type::stupid_judge: return make_unique<stupid_judge>();
	case strategy_type::ostap: return make_unique<ostap>();
	case strategy_type::accountant: return make_unique<accountant>();
	case strategy_type::probe: return make_unique<probe>();
	case strategy_type::punisher: return make_unique<punisher>();
	case strategy_type::advocate: return make_unique<advocate>();
	case strategy_type::conformist: return make_unique<conformist>();
	case strategy_type::sly_conformist: return make_unique<sly_conformist>();
	case strategy_type::rebel: return make_unique<rebel>();
	case strategy_type::suspicious: return make_unique<suspicious>();
	case strategy_type::madman: return make_unique<madman>();
	case strategy_type::nervous: return make_unique<nervous>();
	case strategy_type::provocateur: return make_unique<provocateur>();
	case strategy_type::pavlov: return make_unique<pavlov>();
	case strategy_type::Spectrum_Zero: return make_unique<Spectrum_Zero>();
	case strategy_type::Spectrum_Phantom: return make_unique<Spectrum_Phantom>();
	case strategy_type::Spectrum_Lite: return make_unique<Spectrum_Lite>();
	case strategy_type::Spectrum_Aero: return make_unique<Spectrum_Aero>();
	case strategy_type::sentinel: return make_unique<sentinel>();
	case strategy_type::keeper: return make_unique<keeper>();
	case strategy_type::scrapper: return make_unique<scrapper>();
	case strategy_type::zealot: return make_unique<zealot>();
	case strategy_type::inquisitor: return make_unique<inquisitor>();
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
		cout << "...." << endl;
	}
	else
	{
		for (int i = last_number + 1; i < players_cnt - group_size + group.size() + 1; i++)
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
	generate_groups(group, 7, -1);

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

int Tournament::count_s()
{
	vector<bool> s(1000, false);
	for (int i = 0; i < players_cnt; i++)
	{
		s[static_cast<int>(types_vec[i])] = true;
	}
	int count = 0;
	for (int i = 0; i < 1000; i++)
	{
		if (s[i] == true)
		{
			count++;
		}
	}
	return count;
}

void Tournament::start_evo()
{
	vector<int> group;
	int it_cnt = 0;
	while (count_s() != 1 && it_cnt < 1000)
	{
		if (_kbhit())
		{
			char a = _getch();
			if (a == 27)
			{
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
		}
		for (int i = 0; i < players_cnt; i++)
		{
			score[i] = 0;
		}
		//stage 1
		generate_groups(group, 2, -1);
		//stage 2
		generate_groups(group, 3, -1);
		generate_groups(group, 5, -1);
		//stage 3
		generate_groups(group, 7, -1);
		ll Max = 0, Min = 0;
		for (int i = 0; i < players_cnt; i++)
		{
			if (score[Max] < score[i])
			{
				Max = i;
			}
			if (score[Min] > score[i])
			{
				Min = i;
			}
		}
		/*ll m = 0;
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
		cout << "Max " << Max + 1 << ". Min " << Min + 1 << endl;*/
		cout << "Iteration number " << it_cnt + 1 << ". Extinct: " << *create_player(types_vec[Max]) << ". Multiplied: " << *create_player(types_vec[Min]) << ".\n";
		types_vec[Max] = types_vec[Min];
		it_cnt++;
	}
	//
	ll m = 0;
	for (int i = 0; i < players_cnt; i++)
	{
		if (score[i] < score[m])
		{
			m = i;
		}
	}
	cout << "The WINER: " << *create_player(types_vec[m]) << " score:" << score[m] << endl;
}