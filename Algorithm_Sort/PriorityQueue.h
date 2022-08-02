#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
//우선순위 int타입
typedef int PriorityType;

typedef struct tagePQNode
{
	//우선순위
	PriorityType Priority;
	//데이터
	void* Data;
}PQNode;

typedef struct tagPriorityQueue
{
	//노드
	PQNode* Nodes;
	//용적
	int Capacity;
	//사용량
	int UsedSize;
}PriorityQueue;


PriorityQueue* PQ_Create(int InitialSize);
void PQ_Destroy(PriorityQueue* PQ);
void PQ_Enqueue(PriorityQueue* PQ, PQNode NewData);
void PQ_Dequeue(PriorityQueue* PQ, PQNode* Root);
int PQ_GetParent(int Index);
int PQ_GetLeftChild(int Index);
void PQ_SwapNodes(PriorityQueue* PQ, int Index1, int Index2);
int PQ_IsEmpty(PriorityQueue* PQ);

#endif

