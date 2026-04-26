#pragma once

#include <iostream>
#include <vector>
#include <random>
using namespace std;

typedef long long ll;

class Ndilemma;

class Player
{
protected:
	//Global
	static int total_players;//Global number_of_players
	const int uid;//Unique ID
	//Local
	int number_of_players;//local number_of_players
	int match_number;//Match number
	Ndilemma* game;
	
	bool get_history(int round, int target_number) const;

	int get_rand();

	int get_rand(int request);

	ll get_score(int target_number) const;

	ll count_yes(int cnt_yes, int cnt_no) const;

	ll count_no(int cnt_yes, int cnt_no) const;

public:
	Player();

	Player(int _uid);

	virtual ~Player();

	void set_match(Ndilemma* _game, int _match_number, int _number_of_players);

	static int get_total_players();

	virtual bool move(int move_cnt) = 0;

	virtual void print(ostream& out) const;

	friend ostream& operator<<(ostream& out, const Player& player);
};

class Ndilemma
{
private:
	friend class Player;
	const int totalRounds;
	const int n;//totalPlayers
	vector<Player*> player;
	vector<vector<bool>> history;
	vector<ll> score;
	int move_cnt;
	bool noise;
	int noise_chance;
	mt19937 gen;
	uniform_int_distribution<> distrib;

	void go();

	void print_static() const;

	void print_all_moves() const;

	bool get_history(int round, int target_number, int client_number) const;

	int get_rand(int client_number);

	int get_rand(int request, int client_number);

	ll get_score(int number, int client_number) const;

	ll count_yes(int cnt_yes, int cnt_no, int client_number) const;

	ll count_no(int cnt_yes, int cnt_no, int client_number) const;

public:

	Ndilemma(int _totalRounds, vector<Player*> _player, bool _noise);

	Ndilemma(int _totalRounds, vector<Player*> _player, bool _noise, int _noise_chance);

	~Ndilemma();

	void start();

	vector<ll>& get_score();
};