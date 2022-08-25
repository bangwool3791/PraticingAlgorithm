#include "MST.h"

void Prim(Graph* G, Vertex* StartVertex, Graph* MST )
{
    int i = 0;
    //시작 노드 
    PQNode         StartNode = { 0, StartVertex };
    //우선순위 큐 생성
    PriorityQueue* PQ        = PQ_Create(10);
    //현재 정점 임시 포인터 생성
    Vertex*  CurrentVertex = NULL;
    //현재 간선 임시 포인터 생성
    Edge*    CurrentEdge   = NULL; 
    //가중치 포인터 생성 -> 배열 용도로 사용 할 것
    int*     Weights       = (int*) malloc( sizeof(int) * G->VertexCount );
    //정점 포인터에 대한 배열 할당
    Vertex** MSTVertices   = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    Vertex** Fringes       = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    Vertex** Precedences   = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    //현재 정점의 포인터를 가져온다.
    CurrentVertex = G->Vertices;
    while ( CurrentVertex != NULL )
    {
        //현재 정점의 포인터를 깊은 복사를 통해 MST 그래프 안에 넣는다.
        Vertex* NewVertex = CreateVertex( CurrentVertex->Data );
        AddVertex( MST, NewVertex);
        //현재 정점과 타겟 정점의 간선이 연결 되어있느지 확인하기 위한 포인터
        Fringes[i]     = NULL;
        Precedences[i] = NULL;
        MSTVertices[i] = NewVertex;        
        Weights[i]     = MAX_WEIGHT;        
        CurrentVertex  = CurrentVertex->Next;
        i++;
    }
    //큐 안에 시작 노드 삽입
    PQ_Enqueue ( PQ, StartNode );

    //시작 노드[루트노드] 중심을 0으로 둔다.
    Weights[StartVertex->Index] = 0;
    //큐가 빌 때 까지(다음 정점을 가져온다)
    while( ! PQ_IsEmpty( PQ ) )
    {
        PQNode  Popped;
        
        PQ_Dequeue(PQ, &Popped);
        //다음 정점 가져온다.
        CurrentVertex = (Vertex*)Popped.Data;
        //다음 정점을 Fringes 이름의 정점 포인터를 보관하는 이차원 포인터에 넣는다.
        //이차원 포인터의 인덱스는 현재 정점의 인덱스이다.
        Fringes[CurrentVertex->Index] = CurrentVertex;
        //현재 정점의 인접 정점 포인터를 가져온다.
        CurrentEdge = CurrentVertex->AdjacencyList;
        //CurrentEdge->Weight 무조건 MAX

        while ( CurrentEdge != NULL )
        {            
            Vertex* TargetVertex = CurrentEdge->Target;
            //연결 되어있지 않고, 연재 간선의 무게 중심보다 타겟 정점 버퍼 무게 중심이 작으면
            //간선의 무게 중심은 함수 밖에서 정의 된다.
            //복사 간선 무게 중심 무조건 맥스
            //한번도 간선 연결이 안되어있으면 !
            if ( Fringes[TargetVertex->Index] == NULL &&
                 CurrentEdge->Weight < Weights[TargetVertex->Index] )
                //최소 가중치 찾기 !
            {
                
                PQNode NewNode =  { CurrentEdge->Weight, TargetVertex };
                //현재 간선의 가중치, 목표 정점을 이니셜 라이즈로 PQNode 생성
                PQ_Enqueue ( PQ, NewNode );
                //새 노드 우선순위 큐에 삽입
                Precedences[TargetVertex->Index] = CurrentEdge->From;
                //출발 노드 삽입
                Weights[TargetVertex->Index]     = CurrentEdge->Weight;      
                //가중치 삽입 
            }
            //다음 간선 넘어가기
            CurrentEdge = CurrentEdge->Next;
        }
    }

    for ( i=0; i<G->VertexCount; i++ )
    {
        int FromIndex, ToIndex;

        if ( Precedences[i] == NULL )
            continue;

        //출발 간선이 NULL이 아니라면
        FromIndex = Precedences[i]->Index;
        ToIndex   = i;

        //이미 삽입된 정점들 목록에 간선 추가
        //시작 정점 Edge 추가
        AddEdge( MSTVertices[FromIndex], 
            CreateEdge( MSTVertices[FromIndex], MSTVertices[ToIndex],   Weights[i] ) );
        //끝 정점 Edge 추가
        AddEdge( MSTVertices[ToIndex],   
            CreateEdge( MSTVertices[ToIndex],   MSTVertices[FromIndex], Weights[i] ) );
    }

    free( Fringes );
    free( Precedences );
    free( MSTVertices );
    free( Weights );

    PQ_Destroy( PQ );
}

void Kruskal(Graph* G, Graph* MST )
{
    int           i;
    //현재 정점을 가리키는 포인터
    Vertex*       CurrentVertex = NULL;
    //모든 정점을 보관하는 메모리 버퍼
    Vertex**      MSTVertices   = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    //
    DisjointSet** VertexSet     = 
                         (DisjointSet**)malloc( sizeof(DisjointSet*) * G->VertexCount );
    
    PriorityQueue* PQ      = PQ_Create(10);

    i = 0;    
    CurrentVertex = G->Vertices;
    while ( CurrentVertex != NULL )
    {
        Edge* CurrentEdge;
        //부모 노드를 보관하는 Vertex 생성
        VertexSet[i]   = DS_MakeSet( CurrentVertex );
        //버텍스 깊은 복사
        MSTVertices[i] = CreateVertex( CurrentVertex->Data );
        //그래프에 버텍스 저장
        AddVertex( MST, MSTVertices[i] );
        //현재 버텍스 인접 간선 임시 메모리 공간 저장
        CurrentEdge = CurrentVertex->AdjacencyList;
        //버텍스 리스트 생성
        while ( CurrentEdge != NULL )
        {
            //새 노드 할당
            //무게 중심과 현재 인접 간선
            PQNode NewNode = { CurrentEdge->Weight, CurrentEdge };
            //우선순위 큐에 새 노드 저장
            PQ_Enqueue( PQ, NewNode );
            //다음 인접 간선
            CurrentEdge = CurrentEdge->Next;
        }
        //현재 정점에 다음 정점 저장
        CurrentVertex  = CurrentVertex->Next;        
        i++;
    }

    while ( !PQ_IsEmpty( PQ ) )
    {
        Edge*  CurrentEdge;
        int    FromIndex;
        int    ToIndex;
        PQNode Popped;
        //큐에서 PQNode Dequeue
        PQ_Dequeue( PQ, &Popped );
        //현재 간선 포인터 임시 메모리 저장
        CurrentEdge = (Edge*)Popped.Data;

        printf("%c - %c : %d\n", 
            CurrentEdge->From->Data, 
            CurrentEdge->Target->Data, 
            CurrentEdge->Weight );

        FromIndex = CurrentEdge->From->Index;
        ToIndex   = CurrentEdge->Target->Index;
        //합집합 관계가 아니면
        //부모가 같지 않다면
        if ( DS_FindSet( VertexSet[FromIndex] ) != DS_FindSet( VertexSet[ToIndex] ) )
        {
            AddEdge( MSTVertices[FromIndex], 
                     CreateEdge( MSTVertices[FromIndex], 
                                 MSTVertices[ToIndex], 
                                 CurrentEdge->Weight ) );

            AddEdge( MSTVertices[ToIndex], 
                     CreateEdge( MSTVertices[ToIndex], 
                                 MSTVertices[FromIndex], 
                                 CurrentEdge->Weight ) );

            DS_UnionSet( VertexSet[FromIndex], VertexSet[ToIndex] );
        }
    }

    for ( i=0; i<G->VertexCount; i++ )
        DS_DestroySet( VertexSet[i] );

    free( VertexSet );
    free( MSTVertices );
}
