#include "ShortestPath.h"


void Dijkstra(Graph* G, Vertex* StartVertex, Graph* ShortestPath)
{
	int i = 0;

	PQNode StartNode = { 0, StartVertex };
	PriorityQueue* PQ = PQ_Create(10);

	Vertex* CurrentVertex = NULL;
	Edge* CurrentEdge = NULL;

	//������ ����ŭ ���� ������ �Ҵ�
	//�����߽�
	int* Weights = (int*)malloc(sizeof(int) * G->VertexCount);

	//�ִ� ��θ� �����ϴ� ���� ������ �����
	//���� �������� ���� �迭
	Vertex** ShortesPathVertices = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);

	//���𰡸� �����ϴ� ���� ������ ���� �迭
	Vertex** Fringes = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);
	//�ִ� ��� ���� ����
	//���� �ƴ��� �������ƴ���
	Vertex** Precedences = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);

	CurrentVertex = G->Vertices;
	//���ο� ������ ShortestPath�� ���� ���縦 ���� �־��ְ�
	while (CurrentVertex != NULL)
	{
		//�׷����� ������ ���� �������� �ϳ��� �����.
		Vertex* NewVertex = CreateVertex(CurrentVertex->Data);
		//ShortesPath�� �� ���� �����͸� �����Ѵ�.
		AddVertex(ShortestPath, NewVertex);

		Fringes[i] = NULL;
		Precedences[i] = NULL;
		//�ִ� ��θ� �����ϴ� ���� ������ ����ҿ� ������ �����Ѵ�.
		ShortesPathVertices[i] = NewVertex;
		//���Ը� �������� �д�.
		Weights[i] = MAX_WEIGHT;
		CurrentVertex = CurrentVertex->Next;
		i++;
	}
	//���� ������ ť�� �ִ´�. 
	//���������� ���� B
	PQ_Enqueue(PQ, StartNode);
	//���� B�� �����߽��� 0���� �ʱ�ȭ
	Weights[StartVertex->Index] = 0;

	while (!PQ_IsEmpty(PQ))
	{
		PQNode Popped;
		//B��带 Dequeue�Ѵ�.
		PQ_Dequeue(PQ, &Popped);
		CurrentVertex = (Vertex*)Popped.Data;
		//���� ������ �ӽ� �޸𸮿� ����
		Fringes[CurrentVertex->Index] = CurrentVertex;
		//�ֺ� ���� �ҷ���
		CurrentEdge = CurrentVertex->AdjacencyList;
		//�ֺ� ������ ���� �ƴ϶��
		while (CurrentEdge != NULL)
		{
			//���� �ֺ� ������ ��ǥ����
			Vertex* TargetVertex = CurrentEdge->Target;
			//�� �κ� ���� �Ȱ�
			if(Fringes[TargetVertex->Index] == NULL &&
				//���� ���� + ���� ���� < ���� ���� 
				Weights[CurrentVertex->Index] + CurrentEdge->Weight <
							Weights[TargetVertex->Index])
				{
					PQNode NewNode = { CurrentEdge->Weight, TargetVertex };
					PQ_Enqueue(PQ, NewNode);
					//�ִ� ��� ���� ����
					Precedences[TargetVertex->Index] = CurrentEdge->From;
					Weights[TargetVertex->Index] = Weights[CurrentVertex->Index] + CurrentEdge->Weight;
					printf("���� ���� : %d\r\n", Precedences[TargetVertex->Index]->Data);
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