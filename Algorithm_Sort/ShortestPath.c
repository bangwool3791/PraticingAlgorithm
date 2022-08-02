#include "ShortestPath.h"


void Dijkstra(Graph* G, Vertex* StartVertex, Graph* ShortestPath)
{
	int i = 0;

	PQNode StartNode = { 0, StartVertex };
	PriorityQueue* PQ = PQ_Create(10);

	Vertex* CurrentVertex = NULL;
	Edge* CurrentEdge = NULL;

	//정점의 수만큼 동적 포인터 할당
	//무게중심
	int* Weights = (int*)malloc(sizeof(int) * G->VertexCount);

	//최단 경로를 저장하는 정점 포인터 저장소
	//정점 포인터의 동적 배열
	Vertex** ShortesPathVertices = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);

	//무언가를 저장하는 정점 포인터 동적 배열
	Vertex** Fringes = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);
	//최단 경로 정점 저장
	//지나 쳤는지 안지나쳤는지
	Vertex** Precedences = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);

	CurrentVertex = G->Vertices;
	//새로운 정점을 ShortestPath에 깊은 복사를 통해 넣어주고
	while (CurrentVertex != NULL)
	{
		//그래프의 정점을 동적 정점으로 하나더 만든다.
		Vertex* NewVertex = CreateVertex(CurrentVertex->Data);
		//ShortesPath에 새 정점 포인터를 저장한다.
		AddVertex(ShortestPath, NewVertex);

		Fringes[i] = NULL;
		Precedences[i] = NULL;
		//최단 경로를 저장하는 정점 포인터 저장소에 정점을 저장한다.
		ShortesPathVertices[i] = NewVertex;
		//무게를 무한으로 둔다.
		Weights[i] = MAX_WEIGHT;
		CurrentVertex = CurrentVertex->Next;
		i++;
	}
	//시작 정점을 큐에 넣는다. 
	//예제에서는 정점 B
	PQ_Enqueue(PQ, StartNode);
	//정점 B의 무게중심을 0으로 초기화
	Weights[StartVertex->Index] = 0;

	while (!PQ_IsEmpty(PQ))
	{
		PQNode Popped;
		//B노드를 Dequeue한다.
		PQ_Dequeue(PQ, &Popped);
		CurrentVertex = (Vertex*)Popped.Data;
		//현재 정점을 임시 메모리에 저장
		Fringes[CurrentVertex->Index] = CurrentVertex;
		//주변 정점 불러옴
		CurrentEdge = CurrentVertex->AdjacencyList;
		//주변 정점이 널이 아니라면
		while (CurrentEdge != NULL)
		{
			//현재 주변 정점의 목표정점
			Vertex* TargetVertex = CurrentEdge->Target;
			//이 부분 이해 안감
			if(Fringes[TargetVertex->Index] == NULL &&
				//경유 무게 + 현재 무게 < 이전 무게 
				Weights[CurrentVertex->Index] + CurrentEdge->Weight <
							Weights[TargetVertex->Index])
				{
					PQNode NewNode = { CurrentEdge->Weight, TargetVertex };
					PQ_Enqueue(PQ, NewNode);
					//최단 경로 정점 저장
					Precedences[TargetVertex->Index] = CurrentEdge->From;
					Weights[TargetVertex->Index] = Weights[CurrentVertex->Index] + CurrentEdge->Weight;
					printf("현재 정점 : %d\r\n", Precedences[TargetVertex->Index]->Data);
				}
			CurrentEdge = CurrentEdge->Next;
		}
	}

	for (i = 0; i < G->VertexCount; ++i)
	{
		int FromIndex, ToIndex;

		if (Precedences[i] == NULL)
			continue;

		FromIndex = Precedences[i]->Index;
		ToIndex = i;
		
		AddEdge(ShortesPathVertices[FromIndex], CreateEdge(ShortesPathVertices[FromIndex],
			ShortesPathVertices[ToIndex],
			Weights[i]));
	}
	free(Fringes);
	free(Precedences);
	free(ShortesPathVertices);
	free(Weights);

	PQ_Destroy(PQ);
}