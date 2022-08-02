#include "KnuthMorrisPratt.h"
#include <stdlib.h>

int KnuthMorrisPratt(char* Text, int TextSize, int Start, char* Pattern, int PatternSize)
{
	int i = Start;
	int j = 0;
	int Position = -1;

	int* Border = malloc(sizeof(int) * (PatternSize + 1));
	Preprocess(Pattern, PatternSize, Border);

	while (i < TextSize)
	{
		while (j >= 0 && Text[i] != Pattern[j])
			j = Border[j];

		i++;
		j++;

		if (j == PatternSize)
		{
			Position = i - j;
			break;
		}
	}
	free(Border);
	return Position;
}

void Preprocess(char* Pattern, int PatternSize, int* Border)
{
	int i = 0;
	int j = -1;

	Border[0] = -1;

	while (i < PatternSize)
	{
		while (j > -1 && Pattern[i] != Pattern[j])
		{
			//이전 일치 접두부의 최대 경계 너비를 가져온다.
			j = Border[j];
		}
		i++;
		j++;
		//일치 접두부의 길이            0
		//일치 접두부의 최대 경계 너비 -1
		//
		Border[i] = j;
	}
}