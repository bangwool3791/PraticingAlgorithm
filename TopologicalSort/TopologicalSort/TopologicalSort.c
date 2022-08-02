#include "TopologicalSort.h"

void TopologicalSort( Vertex* V, Node** List )
{
	//정점이 NULL이 아니고
	//방문을 안했다면
	while (V != NULL && V->Visited == NotVisited)
	{
		//깊이 탐색을 실행한다.
		TS_DFS(V, List);
		//깊이 탐색이 끝나면 다음 정점을 탐색한다.
		V = V->Next;
	}
}

//깊이 탐색
void TS_DFS( Vertex* V, Node** List )
{
	//스택
	//Node Edge 포인터 
	Node* NewHead = NULL;
	Edge* E = NULL;
	
	//깊이 탐색에 진입한 정점은 방문으로 상태 변경
	V->Visited = Visited;
	//정점의 인접 간선을 가져온다.
	E = V->AdjacencyList;
	//인접 간선이 NULL이 아니라면
	while (E != NULL)
	{
		//목표 값, 목표 값이 방문을 안항 상태라면
		if (E->Target != NULL && E->Target->Visited == NotVisited)
		{
			//목표 값의 다음 깊이를 탐색한다.
			TS_DFS(E->Target, List);
		}
		//다음 인접 간선을 탐색한다.
		E = E->Next;
	}

	printf("%d\n", V->Data);
	//깊이 탐색이 끝나면
	//새 노드를 만들고
	NewHead = SLL_CreateNode(V);
	//헤드에 새 노드를 추가한다.
	SLL_InsertNewHead(List, &NewHead);
}