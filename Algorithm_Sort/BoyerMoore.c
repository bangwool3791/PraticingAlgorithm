#include "BoyerMoore.h"

int BoyerMoore(char* Text, int TextSize, int Start, char* Pattern, int PatternSize)
{

}

void BuildBCT(char* Pattern, int PatternSize, int * BCT)
{
	int i;
	int j;
	for (i = 0; i < 128; i++)
		BCT[i] = -1;

	for (j = 0; j < PatternSize; ++j)
		BCT[Pattern[j]] = j;
}

void BuildGST(char* Pattern, int PatternSize, int* Suffix, int* GST)
{
	int i = PatternSize;
	int j = PatternSize + 1;

	//착한 접미사 위치
	Suffix[i] = j;

	while (i > 0)
	{
		while (j <= PatternSize && Pattern[i - 1] != Pattern[j - 1])
		{

		}
	}
}

int Max(int A, int B)
{

}