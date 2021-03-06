// number_baseball_game_computer.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

////////////////////////////////////////////////////////////////////////
// 일반적인 유틸리티 함수
////////////////////////////////////////////////////////////////////////

bool is_correct_num(int n);
int make_random_num();
void make_ball_count(int player_num, int computer_num, int &strike, int &ball);

////////////////////////////////////////////////////////////////////////
// CNumberBaseball
////////////////////////////////////////////////////////////////////////

class CNumberBaseball
{
private:
	bool cases[1000];

public:
	CNumberBaseball();
	~CNumberBaseball();
	void InitCases();
	int getRemainCaseCount();
	void UpdateCases(int num, int strike, int ball);
	int getRandomTrueNum();
};

CNumberBaseball::CNumberBaseball()
{
	InitCases();
}

CNumberBaseball::~CNumberBaseball()
{

}

void CNumberBaseball::InitCases()
{
	for (int i = 0; i < 1000; i++)
		cases[i] = is_correct_num(i);
}

int CNumberBaseball::getRemainCaseCount()
{
	int counting = 0;
	for (int i = 0; i < 1000; i++)
	{
		if (cases[i] == true)
		{
			counting++;
		}
	}
	return counting;
}

void CNumberBaseball::UpdateCases(int num, int strike, int ball)
{
	for (int h = 0; h < 1000; h++)
	{
		int us = 0;
		int  ub = 0;

		if (cases[h] == true)
		{
			int user_number[3] = { (h / 100), (h / 10) % 10, h % 10 };
			int com_num[3] = { (num / 100), (num / 10) % 10, num % 10 };

			for (int i = 0; i < 3; i++)
			{
				for (int k = 0; k < 3; k++)
				{
					if (user_number[i] == com_num[k])
					{
						if (i == k)
						{
							us++;
						}
						else
						{
							ub++;
						}
					}
				}
			}
			if (us != strike || ub != ball)
			{
				cases[h] = false;
			}
		}
	}
}

int CNumberBaseball::getRandomTrueNum()
{
	while (1)
	{
		int guess_num = rand() % 1000;
		if (is_correct_num(guess_num))
		{
			if (cases[guess_num] == true)
			{
				return guess_num;
			}
		}
	}
}

/*
int cs = 0, us = 0;
int cb = 0, ub = 0;
int computer_num;
int computer_number[3];
int user_num;
bool cases[1000];
*/

bool is_correct_num(int n)
{
	int n1 = (n / 100), n2 = (n / 10) % 10, n3 = n % 10;
	if (n1 != n2 && n2 != n3 && n3 != n1)
	{
		return true;
	}
	return false;
}

///////////////////////////////////////////

void init_cases(bool cases[])
{
	for (int i = 0; i < 1000; i++)
		cases[i] = is_correct_num(i);
}

int get_count_true_case(bool cases[])
{
	int counting = 0;
	for (int i = 0; i < 1000; i++)
	{
		if (cases[i] == true)
		{
			counting++;
		}
	}
	return counting;
}

int change_type(int number[])
{
	int changed_num = 0;
	changed_num += number[0] * 100 + number[1] * 10 + number[2];
	return changed_num;
}

int make_random_num()
{
	while (1)
	{
		int random_num = rand() % 1000;
		if (is_correct_num(random_num))
		{
			return random_num;
		}
	}

}

void make_ball_count(int player_num, int computer_num, int &strike, int &ball)
{
	int user_number[3] = { (player_num / 100), (player_num / 10) % 10, player_num % 10 };
	int computer_number[3] = { (computer_num / 100), (computer_num / 10) % 10, computer_num % 10 };

	strike = ball = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			if (user_number[i] == computer_number[k])
			{
				if (i == k)
				{
					strike++;
				}
				else
				{
					ball++;
				}
			}
		}
	}
}

int get_random_true_num(bool cases[])
{
	while (1)
	{
		int guess_num = rand() % 1000;
		if (is_correct_num(guess_num))
		{
			if (cases[guess_num] == true)
			{
				return guess_num;
			}
		}
	}
}

// 컴퓨터 숫자와 true 값을 볼카운트해서 입력받은 볼카운트와 같은 cases의 인덱스를 제외하고 false로 만든다.
void update_cases_with_ballcount(bool cases[], int computer_num, int strike, int ball)
{
	for (int h = 0; h < 1000; h++)
	{
		int us = 0;
		int  ub = 0;

		if (cases[h] == true)
		{
			int user_number[3] = { (h / 100), (h / 10) % 10, h % 10 };
			int com_num[3] = { (computer_num / 100), (computer_num / 10) % 10, computer_num % 10 };

			for (int i = 0; i < 3; i++)
			{
				for (int k = 0; k < 3; k++)
				{
					if (user_number[i] == com_num[k])
					{
						if (i == k)
						{
							us++;
						}
						else
						{
							ub++;
						}
					}
				}
			}
			if (us != strike || ub != ball)
			{
				cases[h] = false;
			}
		}
	}
}

void game_start(bool cases[])
{
	init_cases(cases);
	while (1)
	{
		int com_guess_num = get_random_true_num(cases);
		cout << com_guess_num << endl;
		int ball, strike;
		cin >> strike >> ball;
		update_cases_with_ballcount(cases, com_guess_num, strike, ball);
		if (strike == 3)
		{
			cout << com_guess_num << endl;
			break;
		}
	}
}

void game_start_class()
{
	CNumberBaseball game;

	while (1)
	{
		int com_guess_num = game.getRandomTrueNum();
		cout << com_guess_num << endl;
		int ball, strike;
		cin >> strike >> ball;
		game.UpdateCases(com_guess_num, strike, ball);
		if (strike == 3)
		{
			cout << com_guess_num << endl;
			break;
		}
	}
}

int simulation_start(bool cases[])
{
	init_cases(cases);
	int player_num = make_random_num();
	int counting = 0;
	//cout << setfill('0') << setw(3) << player_num << endl;
	while (1)
	{
		int com_guess_num = get_random_true_num(cases);
		//cout << setfill('0') << setw(3) << com_guess_num;// << endl;
		int strike = 0, ball = 0;
		make_ball_count(player_num, com_guess_num, strike, ball);
		update_cases_with_ballcount(cases, com_guess_num, strike, ball);
		//cout << " : " << strike << " " << ball << endl;
		counting++;
		if (strike == 3)
		{
			//cout << setfill('0') << setw(3) << com_guess_num << endl;
			//cout << counting << "번만에 맞춤" << endl;
			return counting;
		}
	}
}

void clear_cases(bool cases[])
{
	for (int i = 0; i < 1000; i++)
	{
		cases[i] = false;
	}
}

int main()
{
	srand(time(NULL));
	//bool cases[1000];

	//game_start(cases);
	game_start_class();
	/*
	double statistic = 0;

	for (int i = 0; i < 10000; i++)
	{
		clear_cases(cases);
		statistic += simulation_start(cases);
	}
	cout << "평균적으로" << statistic / 10000 << "번만에 맞춤" << endl;
	*/
	return 0;
}
