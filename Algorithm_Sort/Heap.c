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
	//힙 한개의 노드 크기 스택 저장
	int CopySize = sizeof(HeapNode);
	//힙 노드 동적 포인터 할당
	HeapNode* Temp = (HeapNode*)malloc(CopySize);
	//인덱스1번 노드 임시 메모리 저장
	memcpy(Temp, &H->Nodes[Index1], CopySize);
	//인덱스2번 노드를 1번 노드에 복사한다.
	memcpy(&H->Nodes[Index1], &H->Nodes[Index2], CopySize);
	//인덱스 2번 노드에 임시 메모리에 저장한 인덱스 1번 노드를 저장한다.
	memcpy(&H->Nodes[Index2], Temp, CopySize);

	free(Temp);
}

//힙 삭제 함수
void HEAP_DeleteMin(Heap* H, HeapNode* Root)
{
	//부모 위치
	int ParentPosition = 0;
	//왼쪽 위치
	int LeftPosition = 0;
	//오른쪽 위치
	int RightPosition = 0;

	//Root 노드에 힙의 0번째 노드를 복사한다.
	memcpy(Root, &H->Nodes[0], sizeof(HeapNode));
	//힙의 0번째 노드를 0으로 초기화한다.
	memset(&H->Nodes[0], 0, sizeof(HeapNode));
	//힙의 크기를 1줄인다.
	H->UsedSize--;
	//0번 노드와 마지막 노드를 교환한다.
	HEAP_SwapNodes(H, 0, H->UsedSize);
	//0번 노드의 왼쪽 위치를 가져온다.
	LeftPosition = HEAP_GetLeftChild(0);
	//오른쪽 위치를 가져온다.
	RightPosition = LeftPosition + 1;

	while (1)
	{
		//선택 노드 0
		int SelectedChild = 0;
		//왼쪽 위치가 힙의 크기보다 크거나 같다면
		//break
		if (LeftPosition >= H->UsedSize)
		{
			break;
		}
		//오른쪽 위치가 힙 사이즈와 같거나 크다면
		if (RightPosition >= H->UsedSize)
		{
			//왼쪽 위치가 선택 위치가 된다.
			SelectedChild = LeftPosition;
		}
		//오른쪽 위치가 힙 사이즈보다 작다면
		else
		{
			//왼쪽 노드, 오른쪽 노드 데이터 비교
			//오른쪽 노드가 작다면
			if (H->Nodes[LeftPosition].Data > H->Nodes[RightPosition].Data)
			{
				//오른쪽 노드 선택
				SelectedChild = RightPosition;
			}
			else
			{
				//왼쪽 노드 선택
				SelectedChild = LeftPosition;
			}
		}
		//선택 노드가 부모 노드보다 작다면
		if (H->Nodes[SelectedChild].Data < H->Nodes[ParentPosition].Data)
		{
			HEAP_SwapNodes(H, ParentPosition, SelectedChild);
			ParentPosition = SelectedChild;
		}
		else
		{
			break;
		}
		//스왑 된 노드의 부모의 왼쪽 위치를 가져온다.
		LeftPosition = HEAP_GetLeftChild(ParentPosition);
		RightPosition = LeftPosition + 1;
	}

	//이건 뭐하는 거지 ?
	//힙 동적 할당 영역이 실제 사용하는 값보다
	//넘게 할당 되었을 때 메모리를 줄이는 코드
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