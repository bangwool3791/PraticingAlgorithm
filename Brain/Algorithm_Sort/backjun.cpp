
#include <iostream>

using namespace std;

int main()
{
	int H = -1, W = -1, N = -1;
	int Sum = 0;

	while (true)
	{
		cin >> H;
		cin >> W;
		cin >> N;

		if (H == -1 || W == -1 || N == -1)
		{
			continue;
		}

		if (N >= H * W)
			continue;

		Sum = (N % H) * 100 + ((N / H) + 1);

		cout << Sum << endl;
		
	}
	return 0;
}