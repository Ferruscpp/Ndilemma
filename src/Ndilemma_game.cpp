#include "Ndilemma_game.h"

bool Player::get_history(int round, int number) const
{
	return game->get_history(round, number, this->number);
}

int Player::get_rand()
{
	return game->get_rand(number);
}

int Player::get_rand(int request)
{
	return game->get_rand(request, number);
}

ll Player::get_score(int target_number) const
{
	return game->get_score(target_number, number);
}

ll Player::count_yes(int cnt_yes, int cnt_no) const
{
	return game->count_yes(cnt_yes, cnt_no, number);
}

ll Player::count_no(int cnt_yes, int cnt_no) const
{
	return game->count_no(cnt_yes, cnt_no, number);
}

Player::Player() : number(number_of_players), game(nullptr)
{
	number_of_players++;
}

Player::Player(Ndilemma* _game) : number(number_of_players), game(_game)
{
	number_of_players++;
}

Player::~Player()
{

}

void Player::add_game(Ndilemma* _game)
{
	if (game == nullptr)
	{
		game = _game;
	}
	else
	{
		cerr << "!!! ERROR !!!" << endl;
		cerr << "!!! CHANGING SETTINGS !!!" << endl;
		cerr << "!!! Player number " << number << " want to change the game!!!" << endl;
		cerr << "!!!BAN BAN BAN BAN BAN BAN!!!!" << endl;
		exit(0);
	}
}

void Player::print(ostream& out) const
{
	//вывод информации об игроке
	out << "Player number " << number + 1 << " score:" << this->get_score(number);
}

ostream& operator<<(ostream& out, const Player& player)
{
	player.print(out);
	return out;
}

int Player::number_of_players = 0;


void Ndilemma::go()
{
	int cnt_yes, cnt_no;
	for (int currentRound = 0; currentRound < totalRounds; currentRound++)
	{
		cnt_yes = 0, cnt_no = 0;
		for (int i = 0; i < n; i++)
		{
			history[currentRound][i] = player[i]->move(move_cnt);
			if (noise && distrib(gen) <= noise_chance)
			{
				history[currentRound][i] = !history[currentRound][i];
			}
			if (history[currentRound][i] == false)
			{
				cnt_no++;
			}
			else
			{
				cnt_yes++;
			}
		}
		int s_yes = count_yes(cnt_yes, cnt_no, -1), s_no = count_no(cnt_yes, cnt_no, -1);
		for (int i = 0; i < n; i++)
		{
			if (history[currentRound][i] == false)
			{
				score[i] += s_no;
			}
			else
			{
				score[i] += s_yes;
			}
		}
		move_cnt++;
	}
}

void Ndilemma::print_static() const
{
	ll m = 0;
	for (int i = 0; i < n; i++)
	{
		if (m == -1)
		{
			m = i;
		}
		else
		{
			if (score[i] < score[m])
			{
				m = i;
			}
		}
	}
	cout << "The WINER: " << *player[m] << endl << endl;
	for (int i = 0; i < n; i++)
	{
		cout << *player[i] << endl;
	}
}

void Ndilemma::print_all_moves() const
{
	int cnt_yes, cnt_no;
	for (int currentRound = 0; currentRound < totalRounds; currentRound++)
	{
		cout << currentRound + 1 << " ";
		cnt_yes = 0;
		cnt_no = 0;
		for (int i = 0; i < n; i++)
		{
			if (history[currentRound][i] == false)
			{
				cout << "No  ";
				cnt_no++;
			}
			else
			{
				cout << "Yes ";
				cnt_yes++;
			}
		}
		cout << "|||||||| Yes: " << this->count_yes(cnt_yes, cnt_no, -1) << " No: " << this->count_no(cnt_yes, cnt_no, -1);
		cout << endl;
	}
}

bool Ndilemma::get_history(int round, int target_number, int client_number) const
{
	if (round < 0 || totalRounds <= round)
	{
		cerr << "!!! ERROR !!!" << endl;
		cerr << "!!! GOING BEYOND THE ARRAY !!!" << endl;
		cerr << "!!! Player number " << client_number << " want to get non-existent history!!!" << endl;
		cerr << "!!!BAN BAN BAN BAN BAN BAN!!!!" << endl;
		exit(0);
	}
	if (round < move_cnt)
	{
		return history[round][target_number];
	}
	else
	{
		cerr << "!!! ERROR !!!" << endl;
		cerr << "!!! IT'S FUTURE !!!" << endl;
		cerr << "!!! Player number " << client_number << " want to see the future!!!" << endl;
		cerr << "!!!BAN BAN BAN BAN BAN BAN!!!!" << endl;
		exit(0);
	}
}

int Ndilemma::get_rand(int client_number)
{
	return distrib(gen);
}

int Ndilemma::get_rand(int request, int client_number)
{
	if (request < 1)
	{
		cerr << "!!! ERROR !!!" << endl;
		cerr << "!!! DOING SOMETHING STRANGE !!!" << endl;
		cerr << "!!! Player number " << client_number << " want to get random!!!" << endl;
		cerr << "!!!BAN BAN BAN BAN BAN BAN!!!!" << endl;
		exit(0);
	}
	else
	{
		return uniform_int_distribution<int>(1, request)(gen);
	}
}

ll Ndilemma::get_score(int target_number, int client_number) const
{
	if (target_number < 0 || n <= target_number)
	{
		cerr << "!!! ERROR !!!" << endl;
		cerr << "!!! GOING BEYOND THE ARRAY !!!" << endl;
		cerr << "!!! Player number " << client_number << " want to get non-existent score!!!" << endl;
		cerr << "!!!BAN BAN BAN BAN BAN BAN!!!!" << endl;
		exit(0);
	}
	else
	{
		return score[target_number];
	}
}

ll Ndilemma::count_yes(int cnt_yes, int cnt_no, int client_number) const
{
	return cnt_no * cnt_no + cnt_no * n + 1;
}

ll Ndilemma::count_no(int cnt_yes, int cnt_no, int client_number) const
{
	return (cnt_no - 1) * cnt_no;
}

Ndilemma::Ndilemma(int _totalRounds, vector<Player*> _player, bool _noise) : totalRounds(_totalRounds), n(_player.size()), player(_player), noise(_noise), gen(std::random_device{}()), distrib(1, 100), move_cnt(0)
{
	history.resize(totalRounds, vector<bool>(n));
	score.resize(n, 0);
}

Ndilemma::Ndilemma(int _totalRounds, vector<Player*> _player, bool _noise, int _noise_chance) : totalRounds(_totalRounds), n(_player.size()), player(_player), noise(_noise), noise_chance(_noise_chance), gen(std::random_device{}()), distrib(1, 100), move_cnt(0)
{
	history.resize(totalRounds, vector<bool>(n));
	score.resize(n, 0);
}

Ndilemma::~Ndilemma()
{

}

void Ndilemma::start()
{
	for (int i = 0; i < n; i++)
	{
		player[i]->add_game(this);
	}
	this->go();
	this->print_static();
	this->print_all_moves();
}