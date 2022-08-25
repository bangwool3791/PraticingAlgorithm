#include "PriorityQueue.h"

//우선순위 큐를 생성하는 함수
//매개 변수로 초기 우선순위큐 사이즈를 받는다.
PriorityQueue* PQ_Create(int InitialSize)
{
	//동적할당
	PriorityQueue* NewPQ = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	//초기 사이즈를 Capacity 변수 대입
	NewPQ->Capacity = InitialSize;
	//UsedSize 초기 값 0
	NewPQ->UsedSize = 0;
	//노드를 Capacity만큼 동적 할당
	NewPQ->Nodes = (PQNode*)malloc(sizeof(PQNode) * NewPQ->Capacity);
	return NewPQ;
}

//PriorityQueue 삭제 함수
void PQ_Destroy(PriorityQueue* PQ)
{
	//PriorityQueue 안에 Node를 먼저 삭제 후
	free(PQ->Nodes);
	//PriorityQueue 삭제
	free(PQ);
}
//PriorityQueue안에 새 노드 삽입 함수
void PQ_Enqueue(PriorityQueue* PQ, PQNode NewNode)
{
	//현재 큐에 삽입 된 데이터 위치
	int CurrentPosition = PQ->UsedSize;
	//현재 위치의 부모 위치
	int ParentPosition = PQ_GetParent(CurrentPosition);
	//현재 사이즈와 큐 할당량이 같다면
	if (PQ->UsedSize == PQ->Capacity)
	{
		//아예 할당이 안된 경우
		if (PQ->Capacity == 0)
		{
			//할당량을 1로 만든다.
			PQ->Capacity = 1;
		}
		//할당량을 두배로 한뒤
		PQ->Capacity *= 2;
		//노드에 동적 할당을 다시한다.
		PQ->Nodes = (PQNode*)realloc(PQ->Nodes, sizeof(PQNode) * PQ->Capacity);
	}
	//새 노드를 우선순위 큐 현재 위치에 대입
	PQ->Nodes[CurrentPosition] = NewNode;
	//현재 위치가 0보다 크고 현재 위치 노드가 부모 노드보다 우선순위가 낮다면
	while (CurrentPosition > 0 && PQ->Nodes[CurrentPosition].Priority < PQ->Nodes[ParentPosition].Priority)
	{
		//스왑
		PQ_SwapNodes(PQ, CurrentPosition, ParentPosition);
		//우선순위가 낮은 순서대로 정렬한다.
		//부모위치를 현재 위치에 넣어주고
		CurrentPosition = ParentPosition;
		//부모 위치를 바뀐 현재위치의 부모로 변경한다.
		ParentPosition = PQ_GetParent(CurrentPosition);
	}
	//안에 들어간 데이터 크기를 증가시킨다.
	PQ->UsedSize++;
}

void PQ_SwapNodes(PriorityQueue* PQ, int Index1, int Index2)
{
	int CopySize = sizeof(PQNode);
	PQNode* Temp = (PQNode*)malloc(CopySize);

	memcpy(Temp, &PQ->Nodes[Index1], CopySize);
	memcpy(&PQ->Nodes[Index1], &PQ->Nodes[Index2], CopySize);
	memcpy(&PQ->Nodes[Index2], Temp, CopySize);

	free(Temp);
}

//우선순위 큐 안에서 데이터를 꺼내는 함수
void PQ_Dequeue(PriorityQueue* PQ, PQNode* Root)
{
	int ParentPosition = 0;
	int LeftPosition = 0;
	int RightPosition = 0;

	//루트 노드의 데이터를 임시 위치에 이동
	memcpy(Root, &PQ->Nodes[0], sizeof(PQNode));
	//루트 노드 데이터 초기화
	memset(&PQ->Nodes[0], 0, sizeof(PQNode));
	//마지막 노드를 루트 노드에 대입
	PQ->UsedSize--;
	PQ_SwapNodes(PQ, 0, PQ->UsedSize);
	//왼쪽 위치 Get
	LeftPosition = PQ_GetLeftChild(0);
	RightPosition = LeftPosition + 1;

	while (1)
	{
		int SelectedChild = 0;

		//마지막 노드 위치가
		//왼쪽 위치인 경우
		if (LeftPosition >= PQ->UsedSize)
		{
			//브레이크
			//왜 ? 브레이크 ?
			break;
		}
		//오른쪽 위치인 경우
		if (RightPosition >= PQ->UsedSize)
		{
			SelectedChild = LeftPosition;
		}
		else
		{
			//왼쪽 노드위 위치 우선순위가 오른쪽 노드 위치 우선 순위보다 낮다면
			if (PQ->Nodes[LeftPosition].Priority < PQ->Nodes[RightPosition].Priority)
			{
				//우선순위가 높은 오른쪽 위치를 저장
				SelectedChild = RightPosition;
			}
			else
			{
				//우선순위가 높은 왼쪽 위치를 저장
				SelectedChild = LeftPosition;
			}
		}

		//선택 노드 우선순위가 부모 노드 우선순위보다 작다면 
		if (PQ->Nodes[SelectedChild].Priority < PQ->Nodes[ParentPosition].Priority)
		{
			//선택 노드와 부모 노드를 스왑
			PQ_SwapNodes(PQ, ParentPosition, SelectedChild);
			ParentPosition = SelectedChild;
		}
		else
		{
			//작지 않고 그 위치에 있어도 된다면 브레이크
			break;
		}
		//다음노드와 비교
		LeftPosition = PQ_GetLeftChild(ParentPosition);
		RightPosition = LeftPosition + 1;
	}
	//사용 사이즈가 할당량 /2보다 작다면
	if (PQ->UsedSize < (PQ->Capacity / 2))
	{
		//할댱랼을 줄인다.
		PQ->Capacity /= 2;
		PQ->Nodes = (PQNode*)realloc(PQ->Nodes, sizeof(PQNode) * PQ->Capacity);
	}
	//루트 노드를 뺌으로써 메모리도 줄이는 코드
}
int PQ_GetParent(int Index)
{
	return (int)((Index - 1) / 2);
}
int PQ_GetLeftChild(int Index)
{
	return (2 * Index) + 1;
}

int PQ_IsEmpty(PriorityQueue* PQ)
{
	return (PQ->UsedSize == 0);
}
