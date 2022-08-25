#include "NQueens.h"

void PrintSolution(int Columns[], int NumberofQueens)
{
	for (int i = 0; i < NumberofQueens; i++)
	{
		for (int j = 0; j < NumberofQueens; j++)
		{
			if (Columns[i] == j)
			{
				printf("Q");
			}
			else
			{
				printf(".");
			}
		}
		printf("\n");
	}

	printf("\n");
}

int IsThreatened(int Columns[], int NewRow)
{
	int CurrentRow = 0;
	int Threatened = 0;

	while (CurrentRow < NewRow)
	{
		if (Columns[CurrentRow] == Columns[NewRow]
			|| (abs(Columns[CurrentRow] - Columns[NewRow]) == abs(NewRow - CurrentRow))) {
			Threatened = 1;
			break;
		}
		CurrentRow++;
	}

	return Threatened;
}

void FindSolutionForQueen(int Columns[], int Row, int NumberofQueens, int* SolutionCount)
{
	if (IsThreatened(Columns, Row))
		return;

	if (Row == NumberofQueens - 1)
	{
		printf("Solution #%d : \n", ++(*SolutionCount));
		PrintSolution(Columns, NumberofQueens);
	}
	else
	{
		int i = 0;

		for (i = 0; i < NumberofQueens; i++)
		{
			Columns[Row + 1] = i;
			FindSolutionForQueen(Columns, Row + 1, NumberofQueens, SolutionCount);
		}
	}
}

