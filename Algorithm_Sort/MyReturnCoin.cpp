#include "MyReturnCoin.h"
#include <vector>

int main()
{
	std::vector<int> CoinUnit = { 10,100, 500, 1000, 5000, 10000 };
	MyReturnCoin Object = MyReturnCoin(12500, CoinUnit);
	Object.Process();
	Object.Print();
	return 0;
}