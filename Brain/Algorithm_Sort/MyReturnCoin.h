#pragma once
#include <vector>
#include <map>
#include <iostream>
//돈, 코인 단위 배열, 개수 배열, 

class MyReturnCoin
{
public :
	MyReturnCoin(int _InitMoney, const std::vector<int>& _VectorCoinUnit)
	{
		Money = _InitMoney;
		VectorCoinUnit = _VectorCoinUnit;
		MaxCoinUnitCount = _VectorCoinUnit.size();
	}

	~MyReturnCoin()
	{

	}

	void Process()
	{
		int CoinCout = MaxCoinUnitCount - 1;

		while (CoinCout > -1)
		{
			if (Money >= VectorCoinUnit[CoinCout] * (MapCoinCount[VectorCoinUnit[CoinCout]] + 1))
			{
				while (Money >= VectorCoinUnit[CoinCout] * (MapCoinCount[VectorCoinUnit[CoinCout]]))
				{
					MapCoinCount[VectorCoinUnit[CoinCout]]++;
					Money -= VectorCoinUnit[CoinCout];
				}
			}
			CoinCout--;
		}
	}

	void Print()
	{
		for (auto elem : MapCoinCount)
		{
			std::cout << "Elem " << elem.first << " " << elem.second << std::endl;
		}
	}
private :
	int Money = 0;
	int MaxCoinUnitCount = 0;
	std::vector<int> VectorCoinUnit;
	std::map<int, int> MapCoinCount;
	
};