#include "TopologicalSort.h"

void TopologicalSort( Vertex* V, Node** List )
{
	//������ NULL�� �ƴϰ�
	//�湮�� ���ߴٸ�
	while (V != NULL && V->Visited == NotVisited)
	{
		//���� Ž���� �����Ѵ�.
		TS_DFS(V, List);
		//���� Ž���� ������ ���� ������ Ž���Ѵ�.
		V = V->Next;
	}
}

//���� Ž��
void TS_DFS( Vertex* V, Node** List )
{
	//����
	//Node Edge ������ 
	Node* NewHead = NULL;
	Edge* E = NULL;
	
	//���� Ž���� ������ ������ �湮���� ���� ����
	V->Visited = Visited;
	//������ ���� ������ �����´�.
	E = V->AdjacencyList;
	//���� ������ NULL�� �ƴ϶��
	while (E != NULL)
	{
		//��ǥ ��, ��ǥ ���� �湮�� ���� ���¶��
		if (E->Target != NULL && E->Target->Visited == NotVisited)
		{
			//��ǥ ���� ���� ���̸� Ž���Ѵ�.
			TS_DFS(E->Target, List);
		}
		//���� ���� ������ Ž���Ѵ�.
		E = E->Next;
	}

	printf("%d\n", V->Data);
	//���� Ž���� ������
	//�� ��带 �����
	NewHead = SLL_CreateNode(V);
	//��忡 �� ��带 �߰��Ѵ�.
	SLL_InsertNewHead(List, &NewHead);
}