#pragma once
#include "Ndilemma_game.h"
#include <unordered_map>
#ifdef _MSC_VER
#include <intrin.h>
#endif
#include <bitset>

class pirate : public Player
{
protected:
public:
	bool move(int move_cnt) override
	{
		return false;
	}

	void print(ostream& out) const override
	{
		out << "pirate number " << uid + 1;
	}
};

class sly_pirate : public Player
{
protected:
public:
	bool move(int move_cnt) override
	{
		if (this->get_rand() <= 70)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void print(ostream& out) const override
	{
		out << "sly pirate number " << uid + 1;
	}
};

class judge : public Player
{
protected:
	vector<ll> g, b;
public:
	virtual bool move(int move_cnt) override
	{
		if (g.empty())
		{
			g.resize(number_of_players, 0);
			b.resize(number_of_players, 0);
		}
		//посчитали статистику
		if (move_cnt != 0)
		{
			for (int i = 0; i < number_of_players; i++)
			{
				if (this->get_history(move_cnt - 1, i) == true)
				{
					g[i]++;
				}
				else
				{
					b[i]++;
				}
			}
		}

		if (move_cnt < 10)
		{
			return true;
		}
		else
		{
			//ищем предателей
			int cnt;
			for (int m = 1; m < number_of_players; m++)
			{
				cnt = 0;
				for (int i = 0; i < number_of_players; i++)
				{
					if (2 * (number_of_players - 1) * b[i] >= (number_of_players + 1 - m) * (g[i] + b[i]) && i != match_number)
					{
						cnt++;
					}
				}
				//if (m == 2) cout << "DEBUG: cnt=" << cnt << " m=" << m << " b1=" << b[0] << " g1=" << g[0] << endl;
				if (cnt >= m)
				{
					return false;
				}
			}
			return true;
		}
	}

	virtual void print(ostream& out) const override
	{
		out << "judge number " << uid + 1;
	}
};

class sly_judge : public judge
{
protected:
public:
	bool move(int move_cnt) override
	{
		bool decision = judge::move(move_cnt);
		if (move_cnt < 10)
		{
			return decision;
		}
		bool last_moves = true;
		for (int i = 1; i <= 10; i++)
		{
			last_moves = last_moves || this->get_history(move_cnt - i, match_number);
		}
		if (last_moves)
		{
			return decision;
		}
		else
		{
			return true;
		}
	}

	void print(ostream& out) const override
	{
		out << "sly judge number " << uid + 1;
	}
};

class stupid_judge : public judge
{
protected:
public:
	bool move(int move_cnt) override
	{
		bool decision = judge::move(move_cnt);
		if (this->get_rand() <= 10)
		{
			return !decision;
		}
		else
		{
			return decision;
		}
	}

	void print(ostream& out) const override
	{
		out << "stupid judge number " << uid + 1;
	}
};

class ostap : public Player
{
protected:
	vector<ll> g, b;
public:
	bool move(int move_cnt) override
	{
		if (g.empty())
		{
			g.resize(number_of_players, 0);
			b.resize(number_of_players, 0);
		}
		if (move_cnt != 0)
		{
			for (int i = 0; i < number_of_players; i++)
			{
				if (this->get_history(move_cnt - 1, i) == true)
				{
					g[i]++;
				}
				else
				{
					b[i]++;
				}
			}
		}

		if (move_cnt < 20)
		{
			return true;
		}
		else
		{
			int yes_cnt = 0, no_cnt = 0;
			for (int i = 0; i < number_of_players; i++)
			{
				if (this->get_history(move_cnt - 1, i) == true)
				{
					yes_cnt++;
				}
				else
				{
					no_cnt++;
				}
			}
			if (no_cnt >= number_of_players / 2)
			{
				return false;
			}
			else
			{
				int cnt;
				for (int m = 1; m < number_of_players; m++)
				{
					cnt = 0;
					for (int i = 0; i < number_of_players; i++)
					{
						if (i == match_number)
						{
							if (2 * (number_of_players - 1) * (b[i] + 1) >= (number_of_players + 1 - m) * (g[i] + b[i] + 1))
							{
								cnt++;
							}
						}
						else
						{
							if (this->get_rand(g[i] + b[i]) <= b[i])
							{
								if (2 * (number_of_players - 1) * (b[i] + 1) >= (number_of_players + 1 - m) * (g[i] + b[i] + 1))
								{
									cnt++;
								}
							}
							else
							{
								if (2 * (number_of_players - 1) * b[i] >= (number_of_players + 1 - m) * (g[i] + b[i]))
								{
									cnt++;
								}
							}
						}
					}
					if (cnt >= m)
					{
						return true;
					}
				}
				return false;
			}
		}
	}

	void print(ostream& out) const override
	{
		out << "ostap number " << uid + 1;
	}
};

class accountant : public Player
{
protected:
public:
	bool move(int move_cnt) override
	{
		if (move_cnt == 0)
		{
			return true;
		}
		else
		{
			ll general_score = 0;
			for (int i = 0; i < number_of_players; i++)
			{
				general_score += this->get_score(i);
			}
			if (2 * number_of_players * this->get_score(match_number) <= general_score)
			{
				return false;
			}
			else if (number_of_players * this->get_score(match_number) <= general_score)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	void print(ostream& out) const override
	{
		out << "accountant number " << uid + 1;
	}
};

class probe : public Player
{
protected:
	ll statistic;
public:
	bool move(int move_cnt) override
	{
		if (move_cnt == 0)
		{
			statistic = 0;
		}
		if (move_cnt < 20)
		{
			return true;
		}
		//отсекли старт
		//если ходы от 21 до 100 считаем статистику(эфект +-1)
		if (21 <= move_cnt && move_cnt <= 100)
		{
			int coefficient = (move_cnt - 1) % 5;
			//int coefficient = (move_cnt % 5) - 1;
			if (move_cnt % 5 == 1)
			{
				coefficient = 5;
			}
			int no_cnt = 0;
			for (int i = 0; i < number_of_players; i++)
			{
				if (this->get_history(move_cnt - 1, i) == false)
				{
					no_cnt++;
				}
			}
			statistic += coefficient * no_cnt;
		}
		//ходим
		if (move_cnt < 100)
		{
			if (move_cnt % 5 == 0)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			int no_cnt = 0;
			for (int i = 0; i < number_of_players; i++)
			{
				if (this->get_history(move_cnt - 1, i) == false)
				{
					no_cnt++;
				}
			}
			if (no_cnt >= number_of_players / 2)
			{
				return false;
			}
			else
			{
				if (100 * statistic < 35 * number_of_players * 16 * 15)//спокойная группа
				{
					if (this->get_rand() <= 25)
					{
						return false;
					}
					else
					{
						return true;
					}
				}
				else//нервная группа
				{
					if (this->get_rand() <= 10)
					{
						return false;
					}
					else
					{
						return true;
					}
				}
			}
		}
	}

	void print(ostream& out) const override
	{
		out << "probe number " << uid + 1;
	}
};

class punisher : public Player
{
protected:
	vector<ll> g, b;
	vector<bool> traitors;
public:
	bool move(int move_cnt) override
	{
		if (g.empty())
		{
			g.resize(number_of_players, 0);
			b.resize(number_of_players, 0);
			traitors.resize(15, false);
		}
		if (move_cnt != 0)
		{
			for (int i = 0; i < number_of_players; i++)
			{
				if (this->get_history(move_cnt - 1, i) == true)
				{
					g[i]++;
				}
				else
				{
					b[i]++;
				}
			}
		}
		if (move_cnt == 0)
		{
			return true;
		}
		for (int i = 13; i >= 0; i--)
		{
			traitors[i + 1] = traitors[i];
		}
		traitors[0] = false;
		int cnt;
		for (int m = 1; m < number_of_players; m++)
		{
			cnt = 0;
			for (int i = 0; i < number_of_players; i++)
			{
				if (2 * (number_of_players - 1) * b[i] >= (number_of_players + 1 - m) * (g[i] + b[i]) && i != match_number)
				{
					cnt++;
				}
			}
			if (cnt >= m)
			{
				traitors[0] = true;
			}
		}

		bool last_15days = false;
		for (int i = 0; i < 15; i++)
		{
			last_15days = last_15days || traitors[i];
		}

		if (last_15days == false)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void print(ostream& out) const override
	{
		out << "punisher number " << uid + 1;
	}
};

class advocate : public Player
{
protected:
	vector<ll> g, b;
	vector<bool> traitors;
public:
	bool move(int move_cnt) override
	{
		if (g.empty())
		{
			g.resize(number_of_players, 0);
			b.resize(number_of_players, 0);
			traitors.resize(15, false);
		}
		if (move_cnt != 0)
		{
			for (int i = 0; i < number_of_players; i++)
			{
				if (this->get_history(move_cnt - 1, i) == true)
				{
					g[i]++;
				}
				else
				{
					b[i]++;
				}
			}
		}
		for (int i = 0; i < 14; i++)
		{
			traitors[i + 1] = traitors[i];
		}
		traitors[0] = false;
		int cnt;
		for (int m = 1; m < number_of_players; m++)
		{
			cnt = 0;
			for (int i = 0; i < number_of_players; i++)
			{
				if (2 * (number_of_players - 1) * b[i] >= (number_of_players + 1 - m) * (g[i] + b[i]) && i != match_number)
				{
					cnt++;
				}
			}
			if (cnt >= m)
			{
				traitors[0] = true;
			}
		}

		bool last_15days = true;
		for (int i = 0; i < 15; i++)
		{
			last_15days = last_15days && traitors[i];
		}

		if (last_15days == false)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void print(ostream& out) const override
	{
		out << "advocate number " << uid + 1;
	}
};

class conformist : public Player
{
protected:
public:
	virtual bool move(int move_cnt) override
	{
		if (move_cnt == 0)
		{
			return true;
		}
		else
		{
			int yes_cnt = 0, no_cnt = 0;
			for (int i = 0; i < number_of_players; i++)
			{
				if (this->get_history(move_cnt - 1, i) == true)
				{
					yes_cnt++;
				}
				else
				{
					no_cnt++;
				}
			}
			if (yes_cnt > no_cnt)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	virtual void print(ostream& out) const override
	{
		out << "conformist number " << uid + 1;
	}
};

class sly_conformist : public conformist
{
protected:
public:
	bool move(int move_cnt) override
	{
		bool decision = conformist::move(move_cnt);
		if (this->get_rand() <= 10)
		{
			return !decision;
		}
		else
		{
			return decision;
		}
	}

	void print(ostream& out) const override
	{
		out << "sly conformist number " << uid + 1;
	}
};

class rebel : public conformist
{
protected:
public:
	bool move(int move_cnt) override
	{
		bool decision = conformist::move(move_cnt);
		if (move_cnt == 0)
		{
			if (this->get_rand() <= 50)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return !decision;
		}
	}

	void print(ostream& out) const override
	{
		out << "rebel number " << uid + 1;
	}
};

class suspicious : public Player
{
protected:
public:
	bool move(int move_cnt) override
	{
		if (move_cnt == 0)
		{
			return true;
		}
		else
		{
			bool last_moves = true;
			for (int i = 0; i < number_of_players; i++)
			{
				if (i != match_number)
				{
					last_moves = last_moves && this->get_history(move_cnt - 1, i);
				}
			}
			return last_moves;
		}
	}

	void print(ostream& out) const override
	{
		out << "suspicious number " << uid + 1;
	}
};

class madman : public Player
{
protected:
	ll revenge_timer;
public:
	bool move(int move_cnt) override
	{
		if (move_cnt == 0)
		{
			revenge_timer = 0;
			return true;
		}
		else if (revenge_timer == 0)
		{
			bool last_moves = true;
			for (int i = 0; i < number_of_players; i++)
			{
				if (i != match_number)
				{
					last_moves = last_moves && this->get_history(move_cnt - 1, i);
				}
			}
			if (last_moves == false)
			{
				revenge_timer = 49;
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			revenge_timer--;
			return false;
		}
	}

	void print(ostream& out) const override
	{
		out << "madman number " << uid + 1;
	}
};

class nervous : public Player
{
protected:
	ll revenge_timer;
public:
	bool move(int move_cnt) override
	{
		if (move_cnt == 0)
		{
			return true;
		}
		else if (revenge_timer == 0)
		{
			int yes_cnt = 0, no_cnt = 0;
			for (int i = 0; i < number_of_players; i++)
			{
				if (this->get_history(move_cnt - 1, i) == true && i != match_number)
				{
					yes_cnt++;
				}
				else
				{
					no_cnt++;
				}
			}
			if (yes_cnt > no_cnt)
			{
				return true;
			}
			else
			{
				revenge_timer = 49;
				return false;
			}
		}
		else
		{
			revenge_timer--;
			return false;
		}
	}

	void print(ostream& out) const override
	{
		out << "nervous number " << uid + 1;
	}
};

class provocateur : public Player
{
protected:
public:
	bool move(int move_cnt) override
	{
		if (this->get_rand(number_of_players) <= 1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void print(ostream& out) const override
	{
		out << "provocateur number " << uid + 1;
	}
};

class pavlov : public Player
{
protected:
	ll barrier;
public:
	bool move(int move_cnt) override
	{
		if (move_cnt == 0)
		{
			vector<ll> s;
			for (int m = 0; m < number_of_players; m++)
			{
				s.push_back(this->count_yes(number_of_players - m, m));
				s.push_back(this->count_no(number_of_players - m, m));
			}
			sort(s.begin(), s.end());
			barrier = s[number_of_players];
			return true;
		}
		else
		{
			ll cnt_yes = 0, cnt_no = 0;
			for (int i = 0; i < number_of_players; i++)
			{
				if (this->get_history(move_cnt - 1, i))
				{
					cnt_yes++;
				}
				else
				{
					cnt_no++;
				}
			}
			ll res;
			if (this->get_history(move_cnt - 1, match_number))
			{
				res = this->count_yes(cnt_yes, cnt_no);
			}
			else
			{
				res = this->count_no(cnt_yes, cnt_no);
			}
			if (res < barrier)
			{
				return this->get_history(move_cnt - 1, match_number);
			}
			else
			{
				return !(this->get_history(move_cnt - 1, match_number));
			}
		}
	}

	void print(ostream& out) const override
	{
		out << "Pavlov's dog number " << uid + 1;
	}
};

class Spectrum_Zero : public Player//he is to heavy for me
{
protected:
	vector<int> echo;
	int count(int mask)
	{
		int ans = 0;
		for (int i = 0; i < number_of_players; i++)
		{
			if (mask % 2 == 1)
			{
				ans++;
			}
			mask /= 2;
		}
		return ans;
	}
public:
	bool move(int move_cnt) override
	{
		if (move_cnt == 0)
		{
			echo.resize(1 << number_of_players, -1);
		}
		if (move_cnt < 1 << (number_of_players - 1))
		{
			if (move_cnt >= 2)//count static
			{
				int pos1 = 0, pos2 = 0;
				for (int i = 0; i < number_of_players; i++)
				{
					if (this->get_history(move_cnt - 1, i))
					{
						pos1 = pos1 * 2 + 1;
					}
					else
					{
						pos1 = pos1 * 2;
					}
					if (this->get_history(move_cnt - 2, i))
					{
						pos2 = pos2 * 2 + 1;
					}
					else
					{
						pos2 = pos2 * 2;
					}
				}
				echo[pos2] = pos1;
			}
			return true;
		}
		else if (move_cnt < 1 << number_of_players)
		{
			if (move_cnt >= 2)//count static
			{
				int pos1 = 0, pos2 = 0;
				for (int i = 0; i < number_of_players; i++)
				{
					if (this->get_history(move_cnt - 1, i))
					{
						pos1 = pos1 * 2 + 1;
					}
					else
					{
						pos1 = pos1 * 2;
					}
					if (this->get_history(move_cnt - 2, i))
					{
						pos2 = pos2 * 2 + 1;
					}
					else
					{
						pos2 = pos2 * 2;
					}
				}
				echo[pos2] = pos1;
			}
			return false;
		}
		else
		{
			if (move_cnt >= 2)//count static
			{
				int pos1 = 0, pos2 = 0;
				for (int i = 0; i < number_of_players; i++)
				{
					if (this->get_history(move_cnt - 1, i))
					{
						pos1 = pos1 * 2 + 1;
					}
					else
					{
						pos1 = pos1 * 2;
					}
					if (this->get_history(move_cnt - 2, i))
					{
						pos2 = pos2 * 2 + 1;
					}
					else
					{
						pos2 = pos2 * 2;
					}
				}
				echo[pos2] = pos1;
			}
			int mask, pos;
			ll sum, best_sum = 1e18;
			int best_v = 0;
			for (int _mask = 0; _mask < 1023; _mask++)// check all variants
			{
				mask = _mask;
				int pos1 = 0;
				for (int i = 0; i < number_of_players; i++)//count last position
				{
					if (this->get_history(move_cnt - 1, i))
					{
						pos1 = pos1 * 2 + 1;
					}
					else
					{
						pos1 = pos1 * 2;
					}
				}
				sum = 0;
				for (int i = 0; i < 10; i++)// count sum
				{
					int cnt_yes = 0, cnt_no = 0;
					pos = echo[pos1];
					if (pos == -1)// find the clothiest variant
					{
						int dif = number_of_players;
						for (int _pos = 0; _pos < 1 << number_of_players; _pos++)
						{
							if (echo[_pos] != -1 && abs((count(pos1) - count(_pos))) < dif)
							{
								pos = echo[_pos];
							}
						}
					}
					for (int i = number_of_players - 1; i >= 0; i--)//count yes and no
					{
						if (i != match_number)
						{
							if (pos % 2 == 1)
							{
								cnt_yes++;
							}
							else
							{
								cnt_no++;
							}
						}
						else
						{
							if (mask % 2 == 1)
							{
								cnt_yes++;
							}
							else
							{
								cnt_no++;
							}
						}
					}
					//count sum
					if (mask % 2 == 1)
					{
						sum += this->count_yes(cnt_yes, cnt_no);
					}
					else
					{
						sum += this->count_no(cnt_yes, cnt_no);
					}
					mask /= 2;
					pos1 = pos;
				}
				if (best_sum > sum)//update best variant
				{
					best_v = _mask;
				}
			}
			//finaly make decision
			if (best_v % 2 == 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	void print(ostream& out) const override
	{
		out << "Spectrum Zero number " << uid + 1;
	}
};

class Spectrum_Phantom : public Player//he is to heavy for me
{
protected:
	unordered_map<int, int> echo;
public:
	bool move(int move_cnt) override
	{
		if (move_cnt < 1 << (number_of_players - 1))
		{
			if (move_cnt >= 2)//count static
			{
				int pos1 = 0, pos2 = 0;
				for (int i = 0; i < number_of_players; i++)
				{
					if (this->get_history(move_cnt - 1, i))
					{
						pos1 = pos1 * 2 + 1;
					}
					else
					{
						pos1 = pos1 * 2;
					}
					if (this->get_history(move_cnt - 2, i))
					{
						pos2 = pos2 * 2 + 1;
					}
					else
					{
						pos2 = pos2 * 2;
					}
				}
				echo[pos2] = pos1;
			}
			return true;
		}
		else if (move_cnt < 1 << number_of_players)
		{
			if (move_cnt >= 2)//count static
			{
				int pos1 = 0, pos2 = 0;
				for (int i = 0; i < number_of_players; i++)
				{
					if (this->get_history(move_cnt - 1, i))
					{
						pos1 = pos1 * 2 + 1;
					}
					else
					{
						pos1 = pos1 * 2;
					}
					if (this->get_history(move_cnt - 2, i))
					{
						pos2 = pos2 * 2 + 1;
					}
					else
					{
						pos2 = pos2 * 2;
					}
				}
				echo[pos2] = pos1;
			}
			return false;
		}
		else
		{
			if (move_cnt >= 2)//count static
			{
				int pos1 = 0, pos2 = 0;
				for (int i = 0; i < number_of_players; i++)
				{
					if (this->get_history(move_cnt - 1, i))
					{
						pos1 = pos1 * 2 + 1;
					}
					else
					{
						pos1 = pos1 * 2;
					}
					if (this->get_history(move_cnt - 2, i))
					{
						pos2 = pos2 * 2 + 1;
					}
					else
					{
						pos2 = pos2 * 2;
					}
				}
				echo[pos2] = pos1;
			}
			int mask, pos;
			ll sum, best_sum = 1e18;
			int best_v = 0;
			for (int _mask = 0; _mask < 1023; _mask++)// check all variants
			{
				mask = _mask;
				int pos1 = 0;
				for (int i = 0; i < number_of_players; i++)//count last position
				{
					if (this->get_history(move_cnt - 1, i))
					{
						pos1 = pos1 * 2 + 1;
					}
					else
					{
						pos1 = pos1 * 2;
					}
				}
				sum = 0;
				for (int i = 0; i < 10; i++)// count sum
				{
					int cnt_yes = 0, cnt_no = 0, cnt1 = __popcnt(pos1);
					if (echo.count(pos1) == 0)// find the clothiest variant
					{
						int dif = number_of_players;
						for (auto iter : echo)
						{
							if (abs((cnt1 - int(__popcnt(iter.first)))) < dif)
							{
								pos = iter.second;
							}
						}
					}
					else
					{
						pos = echo[pos1];
					}
					for (int i = number_of_players - 1; i >= 0; i--)//count yes and no
					{
						if (i != match_number)
						{
							if (pos % 2 == 1)
							{
								cnt_yes++;
							}
							else
							{
								cnt_no++;
							}
						}
						else
						{
							if (mask % 2 == 1)
							{
								cnt_yes++;
							}
							else
							{
								cnt_no++;
							}
						}
					}
					//count sum
					if (mask % 2 == 1)
					{
						sum += this->count_yes(cnt_yes, cnt_no);
					}
					else
					{
						sum += this->count_no(cnt_yes, cnt_no);
					}
					mask /= 2;
					pos1 = pos;
				}
				if (best_sum > sum)//update best variant
				{
					best_v = _mask;
				}
			}
			//finaly make decision
			if (best_v % 2 == 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	void print(ostream& out) const override
	{
		out << "Spectrum Phantom number " << uid + 1;
	}
};

class Spectrum_Lite : public Player//he is to heavy for me
{
protected:
	unordered_map<bitset<7>, bitset<7>> echo;
public:
	bool move(int move_cnt) override
	{
		if (move_cnt >= 2)//count static
		{
			bitset<7> pos1 = 0, pos2 = 0;
			for (int i = 0; i < number_of_players; i++)
			{
				pos1 <<= 1;
				pos2 <<= 1;
				if (this->get_history(move_cnt - 1, i))
				{
					pos1[0] = 1;
				}
				if (this->get_history(move_cnt - 2, i))
				{
					pos2[0] = 1;
				}
			}
			echo[pos2] = pos1;
		}
		if (move_cnt < 1 << (number_of_players - 1))
		{
			return true;
		}
		else if (move_cnt < 1 << number_of_players)
		{
			return false;
		}
		else
		{
			bitset<4> mask;
			bitset<7> pos;
			ll sum, best_sum = 1e18;
			bool best_v = false;
			for (bitset<4>  _mask = 0; _mask.to_ulong() < (1 << 4); _mask = _mask.to_ulong() + 1)// check all variants
			{
				mask = _mask;
				bitset<7> pos1 = 0;
				for (int i = 0; i < number_of_players; i++)//count last position
				{
					if (this->get_history(move_cnt - 1, i))
					{
						pos1 <<= 1;
						pos1[0] = 1;
					}
					else
					{
						pos1 <<= 1;
					}
				}
				sum = 0;
				for (int j = 0; j < 4; j++)// count sum
				{
					int cnt_yes = 0, cnt_no = 0, cnt1 = pos1.count();
					if (echo.find(pos1) == echo.end())// find the clothiest variant
					{
						int dif = number_of_players;
						for (auto iter : echo)
						{
							if (abs((cnt1 - int(iter.first.count()))) < dif)
							{
								pos = iter.second;
							}
						}
					}
					else
					{
						pos = echo[pos1];
					}
					for (int i = number_of_players - 1; i >= 0; i--)//count yes and no
					{
						if (i != match_number)
						{
							if (pos[i] == 1)
							{
								cnt_yes++;
							}
							else
							{
								cnt_no++;
							}
						}
						else
						{
							if (mask[j] == 1)
							{
								cnt_yes++;
							}
							else
							{
								cnt_no++;
							}
						}
					}
					//count sum
					if (mask[j] == 1)
					{
						sum += this->count_yes(cnt_yes, cnt_no);
					}
					else
					{
						sum += this->count_no(cnt_yes, cnt_no);
					}
					pos1 = pos;
				}
				if (best_sum > sum)//update best variant
				{
					best_sum = sum;
					best_v = _mask[0];
				}
			}
			//finaly make decision
			return best_v;
		}
	}

	void print(ostream& out) const override
	{
		out << "Spectrum Lite number " << uid + 1;
	}
};

class Spectrum_Aero : public Player//he is to heavy for me
{
protected:
	vector<bitset<7>> echo;
public:
	bool move(int move_cnt) override
	{
		if (move_cnt == 0)
		{
			echo.resize(1 << number_of_players, -1);
		}
		if (move_cnt >= 2)//count static
		{
			bitset<7> pos1 = 0, pos2 = 0;
			for (int i = 0; i < number_of_players; i++)
			{
				pos1 <<= 1;
				pos2 <<= 1;
				if (this->get_history(move_cnt - 1, i))
				{
					pos1[0] = 1;
				}
				if (this->get_history(move_cnt - 2, i))
				{
					pos2[0] = 1;
				}
			}
			echo[pos2.to_ulong()] = pos1;
		}
		if (move_cnt < 1 << (number_of_players - 1))
		{
			return true;
		}
		else if (move_cnt < 1 << number_of_players)
		{
			return false;
		}
		else
		{
			bitset<4> mask;
			bitset<7> pos;
			ll sum, best_sum = 1e18;
			bool best_v = false;
			for (bitset<4> _mask = 0; _mask.to_ulong() < (1 << 4); _mask = _mask.to_ulong() + 1)// check all variants
			{
				mask = _mask;
				bitset<7> pos1 = 0;
				for (int i = 0; i < number_of_players; i++)//count last position
				{
					if (this->get_history(move_cnt - 1, i))
					{
						pos1 <<= 1;
						pos1[0] = 1;
					}
					else
					{
						pos1 <<= 1;
					}
				}
				sum = 0;
				for (int j = 0; j < 4; j++)// count sum
				{
					int cnt_yes = 0, cnt_no = 0, cnt1 = pos1.count();
					if (echo[pos1.to_ulong()] == -1)// find the clothiest variant
					{
						int dif = number_of_players;
						for (int _pos = 0; _pos < 1 << number_of_players; _pos++)
						{
							if (echo[_pos] != -1 && abs((cnt1 - int(__popcnt(_pos)))) < dif)
							{
								pos = echo[_pos];
							}
						}
					}
					else
					{
						pos = echo[pos1.to_ulong()];
					}
					for (int i = number_of_players - 1; i >= 0; i--)//count yes and no
					{
						if (i != match_number)
						{
							if (pos[i] == 1)
							{
								cnt_yes++;
							}
							else
							{
								cnt_no++;
							}
						}
						else
						{
							if (mask[j] == 1)
							{
								cnt_yes++;
							}
							else
							{
								cnt_no++;
							}
						}
					}
					//count sum
					if (mask[j] == 1)
					{
						sum += this->count_yes(cnt_yes, cnt_no);
					}
					else
					{
						sum += this->count_no(cnt_yes, cnt_no);
					}
					pos1 = pos;
				}
				if (best_sum > sum)//update best variant
				{
					best_sum = sum;
					best_v = _mask[0];
				}
			}
			//finaly make decision
			return best_v;
		}
	}

	void print(ostream& out) const override
	{
		out << "Spectrum Aero number " << uid + 1;
	}
};

class zealot : public Player
{
protected:
public:
	bool move(int move_cnt) override
	{
		if (move_cnt == 0)
		{
			
			return false;
		}
		else
		{
			int cnt_yes = 0, cnt_no = 0;
			for (int i = 0; i < number_of_players; i++)
			{
				if (this->get_history(move_cnt - 1, i) == true)
				{
					cnt_yes++;
				}
				else
				{
					cnt_no++;
				}
			}
			if (cnt_no * 2 >= number_of_players)
			{
				return false;
			}
			else if (cnt_yes % 2 == 1 && this->get_rand() <= 1)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}

	void print(ostream& out) const override
	{
		out << "zealot number " << uid + 1;
	}
};
