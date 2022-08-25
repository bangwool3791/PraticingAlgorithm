#include "CHT.h"

HashTable* CHT_CreateHashTable(int TableSize)
{
	HashTable* HT = malloc(sizeof(HashTable));
	HT->Table = (List*)malloc(sizeof(List) * TableSize);

	memset(HT->Table, 0, sizeof(List) * TableSize);
	
	HT->TableSize = TableSize;

	return HT;
}

Node* CHT_CreateNode(KeyType Key, ValueType Value)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->Key = (char*)malloc(sizeof(char) * (strlen(Key) + 1));
	strcpy_s(NewNode->Key, strlen(Key) + 1, Key);

	NewNode->Value = (char*)malloc(sizeof(char) * strlen(Value) + 1);
	strcpy_s(NewNode->Value, strlen(Value) + 1, Value);
	NewNode->Next = NULL;
	return NewNode;
}

void CHT_Set_(HashTable* HT, KeyType Key, ValueType Value)
{
	int Address = CHT_Hash(Key, strlen(Key), HT->TableSize);
	Node* NewNode = CHT_CreateNode(Key, Value);

	if (HT->Table[Address] == NULL)
	{
		HT->Table[Address] = NewNode;
	}
	else
	{
		List table = HT->Table[Address];
		NewNode->Next = table;
		HT->Table[Address] = NewNode;

		printf("Collision occured : Key(%s), Address(%d) \n", Key, Address);
	}
}

ValueType CHT_Get(HashTable* HT, KeyType Key)
{
	int Address = CHT_Hash(Key, strlen(Key), HT->TableSize);

	List TheList = HT->Table[Address];

	while (TheList != NULL)
	{
		if (!strcmp(TheList->Key, Key))
		{
			return TheList->Value;
		}
		else
		{
			if (TheList->Next != NULL)
			{
				TheList = TheList->Next;
			}
			else
			{
				return NULL;
			}
		}
	}
}

void CHT_DestroyList(List L)
{
	if (L == NULL)
		return;

	if (L->Next != NULL)
		CHT_DestroyList(L->Next);

	CHT_DestroyNode(L);
}

void CHT_DestroyHashTable(HashTable* HT)
{
	int i = 0;
	for (i = 0; i < HT->TableSize; ++i)
	{
		List L = HT->Table[i];
		CHT_DestroyList(L);
	}

	free(HT->Table);
	free(HT);
}

int CHT_Hash(KeyType Key, int KeyLength, int TableSize)
{
	int i = 0;
	int HashValue = 0;

	for (i = 0; i < KeyLength; ++i)
	{
		HashValue = (HashValue << 3) + Key[i];
	}
}