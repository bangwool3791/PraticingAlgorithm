#include "OpenAddressing.h"

HashTable* OAHT_CreateHashTable(int TableSize)
{
	HashTable* HT = (HashTable*)malloc(sizeof(HashTable));
	HT->Table = (ElementType*)malloc(sizeof(ElementType) * TableSize);
	memset(HT->Table, 0, sizeof(ElementType) * TableSize);

	HT->OccupiedCount = 0;
	HT->TableSize = TableSize;

	return HT;
}

void OAHT_Set(HashTable** HT, KeyType Key, ValueType Value)
{
	int KeyLen, Address, StepSize;

	double Usage;

	Usage = (double)(*HT)->OccupiedCount / (*HT)->TableSize;

	if (Usage > 0.5)
	{
		OAHT_Rehash(HT);
	}

	KeyLen = strlen(Key);
	Address = OAHT_Hash(Key, KeyLen, (*HT)->TableSize);
	StepSize = OAHT_Hash2(Key, KeyLen, (*HT)->TableSize);

	while ((*HT)->Table[Address].Status != EMPTY &&
		strcmp((*HT)->Table[Address].Key, Key) != 0)
	{
		printf("Collision occured! : Key(%s), Address(%d), StepSize(%d) \n", Key, Address, StepSize);
		Address = (Address + StepSize) % (*HT)->OccupiedCount;
	}


	(*HT)->Table[Address].Key = (char*)malloc(sizeof(char*) * (strlen(Key) + 1));
	strcpy_s((*HT)->Table[Address].Key, strlen(Key) + 1, Key);

	(*HT)->Table[Address].Value = (char*)malloc(sizeof(char*) * (strlen(Value) + 1));
	strcpy_s((*HT)->Table[Address].Value, strlen(Value) + 1, Value);
	(*HT)->Table[Address].Status = OCCUPIED;

	(*HT)->OccupiedCount++;

	printf("Key(%s) entered at address (%d)\n", Key, Address);
}

ValueType OAHT_Get(HashTable* HT, KeyType Key)
{
	int KeyLen = strlen(Key);

	int Address = OAHT_Hash(Key, KeyLen, HT->TableSize);
	int StepSize = OAHT_Hash2(Key, KeyLen, HT->TableSize);

	while (HT->Table[Address].Status != EMPTY &&
		strcmp(HT->Table[Address].Key, Key) != 0)
	{
		Address = (Address + StepSize) % HT->OccupiedCount;
	}

	return HT->Table[Address].Value;
}

void OAHT_ClearElement(ElementType* Element)
{
	if (Element->Status == EMPTY)
		return;

	free(Element->Value);
	free(Element->Key);

	Element->Value = NULL;
	Element->Key = NULL;
}

void OAHT_DestroyHashTable(HashTable* HT)
{
	for (int i = 0; i < HT->TableSize; ++i)
	{
		OAHT_ClearElement(&HT->Table[i]);
	}

	free(HT->Table);
	free(HT);
}

int OAHT_Hash(KeyType Key, int KeyLength, int TableSize)
{
	int i = 0;
	int HashValue = 0;

	for (i = 0; i < KeyLength; ++i)
	{
		HashValue = (HashValue << 3) + Key[i];
	}

	HashValue = HashValue % TableSize;
	return HashValue;
}

int OAHT_Hash2(KeyType Key, int KeyLength, int TableSize)
{
	int i = 0;
	int HashValue = 0;

	for (i = 0; i < KeyLength; ++i)
	{
		HashValue = (HashValue << 2) + Key[i];
	}

	HashValue = HashValue % (TableSize - 3);

	return HashValue + 1;
}

void OAHT_Rehash(HashTable** HT)
{
	int i = 0;
	
	ElementType* OldHash = (*HT)->Table;
	int TalbeSize = (*HT)->OccupiedCount;

	HashTable* NewHT = OAHT_CreateHashTable((*HT)->TableSize * 2);

	for (i = 0; i < TalbeSize; ++i)
	{
		if(OldHash[i].Status == OCCUPIED)
			OAHT_Set(&NewHT, OldHash[i].Key, OldHash[i].Value);
		(*HT)->OccupiedCount++;
	}

	printf("\nRehashed. New table size is  : %d\n\n", NewHT->TableSize);
	OAHT_DestroyHashTable(*HT);
	*HT = NewHT;
}

