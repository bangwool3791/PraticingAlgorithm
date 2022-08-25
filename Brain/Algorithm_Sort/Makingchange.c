#include "Makingchange.h"
#include <stdio.h>

void GetChange(int Price, int Pay, int CoinUnits[], int Change[], int Size)
{
	int i = 0;
	int ChangeAmount = Pay - Price;

	for (i = 0; i < Size; i++)
	{
		//코인 유닛 저장
		Change[i] = CountCoins(ChangeAmount, CoinUnits[i]);
		//남은 요금을 계산하는 부분
		ChangeAmount = ChangeAmount - (CoinUnits[i] * Change[i]);
	}
}

//코인 수를 세는 함수
int CountCoins(int Amount, int CoinUnit)
{
	int CoinCount = 0;
	int CurrentAmount = Amount;

	while (CurrentAmount >= CoinUnit)
	{
		CoinCount++;
		CurrentAmount = CurrentAmount - CoinUnit;
	}

	return CoinCount;
}

void PrintChange(int CoinUnits[], int Change[], int Size)
{
	int i = 0;

	for (i = 0; i < Size; i++)
	{
		printf("%dWon : %d Coin\n", CoinUnits[i], Change[i]);
	}
}