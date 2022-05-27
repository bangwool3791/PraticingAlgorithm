#include <stdio.h>
#include <Windows.h>

BOOL IsSort(int DataSet[], int Length)
{
	for (int i = 0; i < Length - 1; ++i)
	{
		if (DataSet[i] < DataSet[i + 1])
		{

		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
}

void BublleSort(int DataSet[], int Length)
{
	static int sort_count = 0;

	for (int i = 0; i < Length -1 ; ++i)
	{
		for (int j = 0; j < Length - (i + 1); ++j)
		{
			if (DataSet[j] > DataSet[j + 1])
			{
				int Temp = DataSet[j + 1];
				DataSet[j + 1] = DataSet[j];
				DataSet[j] = Temp;	

				if (IsSort(DataSet, Length))
					return;
			}
		}
	}
}

int main(void)
{
	int DataSet[] = { 6, 4, 2, 3, 1,5 };
	int Length = sizeof(DataSet) / sizeof(DataSet[0]);
	int i = 0;

	BublleSort(DataSet, Length);

	for (i = 0; i < Length; ++i)
	{
		printf("%d ", DataSet[i]);
	}
	printf("\n");
	return 0;
}