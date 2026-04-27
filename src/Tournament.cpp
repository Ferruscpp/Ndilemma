#include "Tournament.h"

unique_ptr<Player> create_player(strategy_type id, int _uid)
{
	switch (id)
	{
	case strategy_type::altruist: return make_unique<altruist>(_uid);
	case strategy_type::drunkard: return make_unique<drunkard>(_uid);
	case strategy_type::pirate: return make_unique<pirate>(_uid);
	case strategy_type::sly_pirate: return make_unique<sly_pirate>(_uid);
	case strategy_type::judge: return make_unique<judge>(_uid);
	case strategy_type::sly_judge: return make_unique<sly_judge>(_uid);
	case strategy_type::stupid_judge: return make_unique<stupid_judge>(_uid);
	case strategy_type::ostap: return make_unique<ostap>(_uid);
	case strategy_type::accountant: return make_unique<accountant>(_uid);
	case strategy_type::probe: return make_unique<probe>(_uid);
	case strategy_type::punisher: return make_unique<punisher>(_uid);
	case strategy_type::advocate: return make_unique<advocate>(_uid);
	case strategy_type::conformist: return make_unique<conformist>(_uid);
	case strategy_type::sly_conformist: return make_unique<sly_conformist>(_uid);
	case strategy_type::rebel: return make_unique<rebel>(_uid);
	case strategy_type::suspicious: return make_unique<suspicious>(_uid);
	case strategy_type::madman: return make_unique<madman>(_uid);
	case strategy_type::nervous: return make_unique<nervous>(_uid);
	case strategy_type::provocateur: return make_unique<provocateur>(_uid);
	case strategy_type::pavlov: return make_unique<pavlov>(_uid);
	case strategy_type::zealot: return make_unique<zealot>(_uid);
	case strategy_type::Spectrum_Zero: return make_unique<Spectrum_Zero>(_uid);
	case strategy_type::Spectrum_Phantom: return make_unique<Spectrum_Phantom>(_uid);
	case strategy_type::Spectrum_Lite: return make_unique<Spectrum_Lite>(_uid);
	case strategy_type::Spectrum_Aero: return make_unique<Spectrum_Aero>(_uid);
	case strategy_type::sentinel: return make_unique<sentinel>(_uid);
	case strategy_type::keeper: return make_unique<keeper>(_uid);
	case strategy_type::scrapper: return make_unique<scrapper>(_uid);
	case strategy_type::inquisitor: return make_unique<inquisitor>(_uid);
	}
}

unique_ptr<Player> create_player(strategy_type id)
{
	return create_player(id, Player::get_total_players());
}

Tournament::Tournament(vector<strategy_type>& _types_vec) : gen((random_device{}())), distrib(1000, 5000), types_vec(_types_vec)
{
	total_moves = distrib(gen);
	players_cnt = types_vec.size();
	score.resize(players_cnt, 0);
	prefix_uid = Player::get_total_players();
	for (int i = 0; i < players_cnt; i++)
	{
		storage.push_back(create_player(types_vec[i]));
	}
}

void Tournament::generate_groups(vector<int>& group, int group_size, int last_number)
{
	if (group.size() == group_size)
	{
		vector<Player*> vec;
		for (int i = 0; i < group_size; i++)
		{
			storage[group[i]] = create_player(types_vec[group[i]], prefix_uid + group[i]);
			vec.push_back((storage[group[i]].get()));
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

bool Tournament::comp(int a, int b)
{
	return score[a] <= score[b];
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

	vector<int> result(players_cnt);
	for (int i = 0; i < players_cnt; i++)
	{
		result[i] = i;
	}
	sort(result.begin(), result.end(), [this](int a, int b) {return score[a] <= score[b];});
	cout << "The WINNER : " << *storage[result[0]] << " score : " << score[result[0]] << endl << endl;
	for (int i = 0; i < players_cnt; i++)
	{
		if (i == 0)
		{
			cout << "The WINNER: ";
		}
		else if (i == 1)
		{
			cout << "2nd place: ";
		}
		else if (i == 2)
		{
			cout << "3rd place: ";
		}
		cout << *storage[result[i]] << " score: " << score[result[i]] << endl;
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
				storage.clear();
				for (int i = 0; i < players_cnt; i++)
				{
					storage.push_back(create_player(types_vec[i]));
				}
				vector<int> result(players_cnt);
				for (int i = 0; i < players_cnt; i++)
				{
					result[i] = i;
				}
				sort(result.begin(), result.end(), [this](int a, int b) {return score[a] <= score[b]; });
				cout << "The WINNER : " << *storage[result[0]] << " score : " << score[result[0]] << endl << endl;
				for (int i = 0; i < players_cnt; i++)
				{
					if (i == 0)
					{
						cout << "The WINNER: ";
					}
					else if (i == 1)
					{
						cout << "2nd place: ";
					}
					else if (i == 2)
					{
						cout << "3rd place: ";
					}
					cout << *storage[result[i]] << " score: " << score[result[i]] << endl;
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
		cout << "Iteration number " << it_cnt + 1 << ". Extinct: " << *storage[Max] << ". Multiplied: " << *storage[Min] << ".\n";
		types_vec[Max] = types_vec[Min];
		it_cnt++;
	}
	//
	vector<int> result(players_cnt);
	for (int i = 0; i < players_cnt; i++)
	{
		result[i] = i;
	}
	sort(result.begin(), result.end(), [this](int a, int b) {return score[a] <= score[b]; });
	cout << "The WINNER : " << *storage[result[0]] << " score : " << score[result[0]] << endl << endl;
	for (int i = 0; i < players_cnt; i++)
	{
		if (i == 0)
		{
			cout << "The WINNER: ";
		}
		else if (i == 1)
		{
			cout << "2nd place: ";
		}
		else if (i == 2)
		{
			cout << "3rd place: ";
		}
		cout << *storage[result[i]] << " score: " << score[result[i]] << endl;
	}
}