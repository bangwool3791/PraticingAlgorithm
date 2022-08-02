#include "Test.h"

#define MAX_WEIGHT 50

void Prim(Graph* G, Vertex* StartVertex, Graph* MST)
{
	int i = 0;

	//시작 노드
	PQNode StartNode = { 0, StartVertex };
	//Queue 동적할당
	PriorityQueue* PQ = PQ_Create(10);
	
	Vertex* CurrentVertex = NULL;
	Edge* CurrentEdge = NULL;

	int* Weights = (int*)malloc(sizeof(int) * G->VertexCount);

	//정점 수를 받는다.
	Vertex** MSTVertices = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);

	Vertex** Fringes = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);

	Vertex** Precedences = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);

	CurrentVertex = G->Vertices;

	while (CurrentVertex != NULL)
	{
		Vertex* NewVertex = CreateVertex(CurrentVertex->Data);
		AddVertex(&MST, NewVertex);

		Fringes[i] = NULL;
		Precedences[i] = NULL;
		MSTVertices[i] = NewVertex;
		Weights[i] = MAX_WEIGHT;
		CurrentVertex = CurrentVertex->Next;
		i++;
	}

	PQ_Enqueue(PQ, StartNode);
}