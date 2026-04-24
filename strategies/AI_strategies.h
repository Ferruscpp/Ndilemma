#pragma once
#include "Ndilemma_game.h"

class sentinel : public Player
{
protected:
    int total_defectors_seen = 0;
public:
    bool move(int move_cnt) override
    {
        if (move_cnt == 0)
        {
            return true;
        }
        else
        {
            int last_m = 0;
            for (int i = 0; i < number_of_players; ++i)
            {
                if (i != match_number && !get_history(move_cnt - 1, i))
                {
                    last_m++;
                }
            }
            total_defectors_seen += last_m;
            if (last_m <= 1)
            {
                return true;
            }
            else
            {
                if (total_defectors_seen * 10 > (move_cnt * (number_of_players - 1) * 3))
                {
                    return false;
                }
                else
                {
                    if (last_m > (number_of_players / 4))
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
        out << "sentinel number " << match_number + 1;
    }
};

class keeper : public Player
{
protected:
    int mood = 0;
public:
    bool move(int move_cnt) override
    {
        if (move_cnt == 0)
        {
            return true;
        }
        else
        {
            int last_m = 0;
            for (int i = 0; i < number_of_players; ++i)
            {
                if (i != match_number && !get_history(move_cnt - 1, i))
                {
                    last_m++;
                }
            }

            // Если предателей много (больше 1/3), портим себе настроение сразу
            if (last_m * 3 > number_of_players / 3)
            {
                mood -= 2;
            }
            else if (last_m <= 1)
            {
                // Если все тихо, потихоньку успокаиваемся
                if (mood < 0)
                {
                    mood++;
                }
            }

            // Если "настроение" упало ниже критической отметки — бьем в ответ
            if (mood < -1 || last_m * 2 > number_of_players)
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
        out << "keeper number " << match_number + 1;
    }
};

class scrapper : public Player
{
protected:
    int revenge_counter = 0;

public:
    bool move(int move_cnt) override
    {
        if (move_cnt == 0)
        {
            revenge_counter = 0;
            return true;
        }

        // Если мы уже в режиме серийной мести
        if (revenge_counter > 0)
        {
            revenge_counter--;
            return false;
        }

        // Проверяем только того, с кем играем в данный момент (через match_number?)
        // Если в 1v1, то оппонент всегда один. 
        // Но в группе нам нужно понять, кто именно нас ударил.

        bool someone_betrayed = false;
        for (int i = 0; i < number_of_players; ++i)
        {
            if (i != match_number && !get_history(move_cnt - 1, i))
            {
                someone_betrayed = true;
                break;
            }
        }

        if (someone_betrayed)
        {
            // Если нас предали дважды подряд (проверяем историю)
            bool double_strike = false;
            if (move_cnt >= 2)
            {
                for (int i = 0; i < number_of_players; ++i)
                {
                    if (i != match_number && !get_history(move_cnt - 1, i) && !get_history(move_cnt - 2, i))
                    {
                        double_strike = true;
                        break;
                    }
                }
            }

            if (double_strike)
            {
                revenge_counter = 3; // Запускаем серию
                return false;
            }

            // Обычная месть с шансом прощения
            if (this->get_rand() < 20)
            {
                return true; // Простили (анти-шум)
            }
            return false;
        }
        return true;
    }

    void print(ostream& out) const override
    {
        out << "scrapper number " << match_number + 1;
    }
};

class inquisitor : public Player
{
protected: long long total_avg_score = 0;
public:
    bool move(int move_cnt) override
    {
        if (move_cnt == 0)
        {
            return true;
        }
        // 1. Считаем средний срок по палате
        long long sum = 0;
        for (int i = 0; i < number_of_players; ++i)
        {
            sum += get_score(i);
        }
        total_avg_score = sum / number_of_players;
        // 2. Ищем, есть ли в текущей группе слишком успешные игроки (лидеры)
        // Если кто-то набрал срок на 15% меньше среднего — он цель.
        bool exists_dangerous_leader = false;
        for (int i = 0; i < number_of_players; ++i)
        {
            if (i != match_number)
            {
                if (get_score(i) * 100 < total_avg_score * 85)
                {
                    exists_dangerous_leader = true;
                    break;
                }
            }
        }
        // 3. Проверка на предательство в прошлом раунде
        bool betrayal_last_round = false;
        for (int i = 0; i < number_of_players; ++i)
        {
            if (i != match_number && !get_history(move_cnt - 1, i))
            {
                betrayal_last_round = true;
                break;
            }
        }
        // --- ЛОГИКА ПРИНЯТИЯ РЕШЕНИЯ ---
        // Если в группе есть лидер, мы его "тормозим"
        if (exists_dangerous_leader)
        {
            // Небольшой шанс простить (10%), чтобы не тонуть в вечной войне
            if (this->get_rand() > 90)
            {
                return true;
            }
            return false;
        }
        // Если нас предали, отвечаем местью
        if (betrayal_last_round)
        {
            // Шанс 20% на прощение (защита от шума)
            if (this->get_rand() > 80)
            {
                return true;
            }
            return false;
        }
        // Если всё спокойно — сотрудничаем
        return true;
    }
    void print(ostream& out) const override
    {
        out << "inquisitor number " << match_number + 1;
    }
};