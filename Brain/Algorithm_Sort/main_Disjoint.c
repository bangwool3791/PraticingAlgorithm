#include "DisjointSet.h"

int main()
{
	int a = 1, b = 2, c = 3, d = 4;

	DisjointSet* Set1 = DS_MakeSet(&a);
	DisjointSet* Set2 = DS_MakeSet(&b);
	DisjointSet* Set3 = DS_MakeSet(&c);
	DisjointSet* Set4 = DS_MakeSet(&d);

	

	return 0;
}