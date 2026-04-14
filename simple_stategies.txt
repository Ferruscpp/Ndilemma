#pragma once
#include "Ndilemma_game.h"

//simple strategies 4 your tests

class altruist : public Player
{
protected:
	//you can save some information
public:
	bool move(int move_cnt) override
	{
		//do your choise
		//make your move
		// return false if you to say no or "betray"
		// return true if you want to say yes or "keep silent"
		return true;
	}

	void print(ostream& out) const override
	{
		//pls wright your name, because it's look wonderful
		out << "altruist number " << number + 1 << " score:" << this->get_score(number);
	}
};

class drunkard : public Player
{
protected:
public:
	bool move(int move_cnt) override
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

	void print(ostream& out) const override
	{
		out << "drunkard number " << number + 1 << " score:" << this->get_score(number);
	}
};