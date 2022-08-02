#include "Heap.h"

Heap* HEAP_Create(int InitialSize)
{
	Heap* NewHeap = (Heap*)malloc(sizeof(Heap));
	NewHeap->Capacity = InitialSize;
	NewHeap->UsedSize = 0;
	NewHeap->Nodes = (HeapNode*)malloc(sizeof(HeapNode) * NewHeap->Capacity);

	printf("size : %zd \n", sizeof(HeapNode));
	return NewHeap;
}

void HEAP_Desytoy(Heap* H)
{
	free(H->Nodes);
	free(H);
}

void HEAP_Insert(Heap* H, ElementType NewData)
{
	int CurrentPosition = H->UsedSize;
	int ParentPosition = HEAP_GetParent(CurrentPosition);

	if (H->UsedSize == H->Capacity)
	{
		H->Capacity *= 2;
		H->Nodes = (HeapNode*)realloc(H->Nodes, sizeof(HeapNode) * H->Capacity);
	}

	H->Nodes[CurrentPosition].Data = NewData;

	while (CurrentPosition > 0 && H->Nodes[CurrentPosition].Data < H->Nodes[ParentPosition].Data)
	{
		HEAP_SwapNodes(H, CurrentPosition, ParentPosition);

		CurrentPosition = ParentPosition;
		ParentPosition = HEAP_GetParent(CurrentPosition);
	}
	H->UsedSize++;
}

void HEAP_SwapNodes(Heap* H, int Index1, int Index2)
{
	//�� �Ѱ��� ��� ũ�� ���� ����
	int CopySize = sizeof(HeapNode);
	//�� ��� ���� ������ �Ҵ�
	HeapNode* Temp = (HeapNode*)malloc(CopySize);
	//�ε���1�� ��� �ӽ� �޸� ����
	memcpy(Temp, &H->Nodes[Index1], CopySize);
	//�ε���2�� ��带 1�� ��忡 �����Ѵ�.
	memcpy(&H->Nodes[Index1], &H->Nodes[Index2], CopySize);
	//�ε��� 2�� ��忡 �ӽ� �޸𸮿� ������ �ε��� 1�� ��带 �����Ѵ�.
	memcpy(&H->Nodes[Index2], Temp, CopySize);

	free(Temp);
}

//�� ���� �Լ�
void HEAP_DeleteMin(Heap* H, HeapNode* Root)
{
	//�θ� ��ġ
	int ParentPosition = 0;
	//���� ��ġ
	int LeftPosition = 0;
	//������ ��ġ
	int RightPosition = 0;

	//Root ��忡 ���� 0��° ��带 �����Ѵ�.
	memcpy(Root, &H->Nodes[0], sizeof(HeapNode));
	//���� 0��° ��带 0���� �ʱ�ȭ�Ѵ�.
	memset(&H->Nodes[0], 0, sizeof(HeapNode));
	//���� ũ�⸦ 1���δ�.
	H->UsedSize--;
	//0�� ���� ������ ��带 ��ȯ�Ѵ�.
	HEAP_SwapNodes(H, 0, H->UsedSize);
	//0�� ����� ���� ��ġ�� �����´�.
	LeftPosition = HEAP_GetLeftChild(0);
	//������ ��ġ�� �����´�.
	RightPosition = LeftPosition + 1;

	while (1)
	{
		//���� ��� 0
		int SelectedChild = 0;
		//���� ��ġ�� ���� ũ�⺸�� ũ�ų� ���ٸ�
		//break
		if (LeftPosition >= H->UsedSize)
		{
			break;
		}
		//������ ��ġ�� �� ������� ���ų� ũ�ٸ�
		if (RightPosition >= H->UsedSize)
		{
			//���� ��ġ�� ���� ��ġ�� �ȴ�.
			SelectedChild = LeftPosition;
		}
		//������ ��ġ�� �� ������� �۴ٸ�
		else
		{
			//���� ���, ������ ��� ������ ��
			//������ ��尡 �۴ٸ�
			if (H->Nodes[LeftPosition].Data > H->Nodes[RightPosition].Data)
			{
				//������ ��� ����
				SelectedChild = RightPosition;
			}
			else
			{
				//���� ��� ����
				SelectedChild = LeftPosition;
			}
		}
		//���� ��尡 �θ� ��庸�� �۴ٸ�
		if (H->Nodes[SelectedChild].Data < H->Nodes[ParentPosition].Data)
		{
			HEAP_SwapNodes(H, ParentPosition, SelectedChild);
			ParentPosition = SelectedChild;
		}
		else
		{
			break;
		}
		//���� �� ����� �θ��� ���� ��ġ�� �����´�.
		LeftPosition = HEAP_GetLeftChild(ParentPosition);
		RightPosition = LeftPosition + 1;
	}

	//�̰� ���ϴ� ���� ?
	//�� ���� �Ҵ� ������ ���� ����ϴ� ������
	//�Ѱ� �Ҵ� �Ǿ��� �� �޸𸮸� ���̴� �ڵ�
	if (H->UsedSize < (H->Capacity / 2))
	{
		H->Capacity /= 2;
		H->Nodes = (HeapNode*)realloc(H->Nodes, sizeof(HeapNode) * H->Capacity);
	}
}

int HEAP_GetParent(int Index)
{
	return (int)((Index - 1) / 2);
}

int HEAP_GetLeftChild(int Index)
{
	return (2 * Index) + 1;
}

void HEAP_PrintNodes(Heap* H)
{
	int i = 0;
	for (i = 0; i < H->UsedSize; ++i)
	{
		printf("%d ", H->Nodes[i].Data);
	}
	printf("\n");
}