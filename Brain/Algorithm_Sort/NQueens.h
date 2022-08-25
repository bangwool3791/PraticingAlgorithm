#pragma once

void PrintSolution(int Columns[], int NumberofQueens);
int IsThreatened(int Columns[], int NewRow);
void FindSolutionForQueen(int Columns[], int Row, int NumberofQueens, int* SolutionCount);

