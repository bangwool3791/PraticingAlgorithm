#pragma once
#include <vector>

template<typename T>
class CConqure
{
public :
	CConqure()
	{
	}
private :

public :
	void MERGE(std::vector<T> A, size_t p, size_t q, size_t r)
	{
		std::vector<T> L;
		std::vector<T> R;

		size_t LN{ q - p + 1 };
		size_t RN{ r - q };

		size_t i = 0, j = 0;
		for (i = 0; i < LN - 1; ++i)
			L.push_back(A[p + i]);

		for (j = 0; j < RN - 1; ++j)
			R.push_back(A[q + j + 1]);

		i = 0;
		j = 0;

		size_t k = p;

		while (i < LN && j < RN)
		{
			if (L[i] <= R[j])
			{
				A[k] = L[i];
				i = i + 1;
			}
			else
			{
				A[k] = R[j];
				j = j + 1;
			}
			k = k + 1;
		}

		while (i < LN)
		{
			A[k] = L[i];
			i = i + 1;
			k = k + 1;
		}

		while (j < RN)
		{
			A[k] = R[j];
			j = j + 1;
			k = k + 1;
		}
	}
};

