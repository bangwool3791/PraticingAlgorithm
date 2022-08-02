#include <stdio.h>
#include <stdlib.h>

void MergeSort(int DataSet[], int StartIndex, int EndIndex);
void Merge(int DataSet[], int StartIndex, int middleIndex, int EndIndex);

void MergeSort(int DataSet[], int StartIndex, int EndIndex)
{
	int MiddleIndex;

	// == 0 으로 시험 필요
	if (EndIndex - StartIndex < 1)
		return;

	MiddleIndex = (StartIndex + EndIndex) /2;

	MergeSort(DataSet, StartIndex, MiddleIndex);
	MergeSort(DataSet, MiddleIndex + 1, EndIndex);

	Merge(DataSet, StartIndex, MiddleIndex, EndIndex);
}

void Merge(int DataSet[], int StartIndex, int MiddleIndex, int EndIndex)
{
	int i;
	int LeftIndex = StartIndex;
	int RightIndex = MiddleIndex + 1;
	int DestIndex = 0;

	int* Destination = (int*)malloc(sizeof(int) * (EndIndex - StartIndex + 1));

	while (LeftIndex <= MiddleIndex && RightIndex <= EndIndex)
	{
		if (DataSet[LeftIndex] < DataSet[RightIndex])
		{
			Destination[DestIndex] = DataSet[LeftIndex++];
		}
		else
		{
			Destination[DestIndex] = DataSet[RightIndex++];
		}
		DestIndex++;
	}

	while (LeftIndex < MiddleIndex)
		Destination[DestIndex++] = DataSet[LeftIndex++];

	while (RightIndex < EndIndex)
		Destination[DestIndex++] = DataSet[RightIndex++];

	DestIndex = 0;

	for (i = StartIndex; i <= EndIndex; i++)
	{
		DataSet[i] = Destination[DestIndex++];
	}

	free(Destination);
}