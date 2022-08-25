#include "DisjointSet.h"

void DS_UnionSet(DisjointSet* Set1, DisjointSet* Set2)
{
	Set2 = DS_FindSet(Set2);
	Set2->Parent = Set1;
}

DisjointSet* DS_FindSet(DisjointSet* Set)
{
	while (Set->Parent != NULL)
	{
		Set = Set->Parent;
	}

	return Set;
}

DisjointSet* DS_MakeSet(void* NewData)
{
	DisjointSet* NewSet = (DisjointSet*)malloc(sizeof(DisjointSet));
	NewSet->Data = NewData;
	NewSet->Parent = NULL;

	return NewSet;
}

void DS_DestroySet(DisjointSet* Set)
{
	free(Set);
}