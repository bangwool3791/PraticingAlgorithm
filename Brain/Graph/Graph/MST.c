#include "MST.h"

void Prim(Graph* G, Vertex* StartVertex, Graph* MST )
{
    int i = 0;
    //���� ��� 
    PQNode         StartNode = { 0, StartVertex };
    //�켱���� ť ����
    PriorityQueue* PQ        = PQ_Create(10);
    //���� ���� �ӽ� ������ ����
    Vertex*  CurrentVertex = NULL;
    //���� ���� �ӽ� ������ ����
    Edge*    CurrentEdge   = NULL; 
    //����ġ ������ ���� -> �迭 �뵵�� ��� �� ��
    int*     Weights       = (int*) malloc( sizeof(int) * G->VertexCount );
    //���� �����Ϳ� ���� �迭 �Ҵ�
    Vertex** MSTVertices   = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    Vertex** Fringes       = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    Vertex** Precedences   = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    //���� ������ �����͸� �����´�.
    CurrentVertex = G->Vertices;
    while ( CurrentVertex != NULL )
    {
        //���� ������ �����͸� ���� ���縦 ���� MST �׷��� �ȿ� �ִ´�.
        Vertex* NewVertex = CreateVertex( CurrentVertex->Data );
        AddVertex( MST, NewVertex);
        //���� ������ Ÿ�� ������ ������ ���� �Ǿ��ִ��� Ȯ���ϱ� ���� ������
        Fringes[i]     = NULL;
        Precedences[i] = NULL;
        MSTVertices[i] = NewVertex;        
        Weights[i]     = MAX_WEIGHT;        
        CurrentVertex  = CurrentVertex->Next;
        i++;
    }
    //ť �ȿ� ���� ��� ����
    PQ_Enqueue ( PQ, StartNode );

    //���� ���[��Ʈ���] �߽��� 0���� �д�.
    Weights[StartVertex->Index] = 0;
    //ť�� �� �� ����(���� ������ �����´�)
    while( ! PQ_IsEmpty( PQ ) )
    {
        PQNode  Popped;
        
        PQ_Dequeue(PQ, &Popped);
        //���� ���� �����´�.
        CurrentVertex = (Vertex*)Popped.Data;
        //���� ������ Fringes �̸��� ���� �����͸� �����ϴ� ������ �����Ϳ� �ִ´�.
        //������ �������� �ε����� ���� ������ �ε����̴�.
        Fringes[CurrentVertex->Index] = CurrentVertex;
        //���� ������ ���� ���� �����͸� �����´�.
        CurrentEdge = CurrentVertex->AdjacencyList;
        //CurrentEdge->Weight ������ MAX

        while ( CurrentEdge != NULL )
        {            
            Vertex* TargetVertex = CurrentEdge->Target;
            //���� �Ǿ����� �ʰ�, ���� ������ ���� �߽ɺ��� Ÿ�� ���� ���� ���� �߽��� ������
            //������ ���� �߽��� �Լ� �ۿ��� ���� �ȴ�.
            //���� ���� ���� �߽� ������ �ƽ�
            //�ѹ��� ���� ������ �ȵǾ������� !
            if ( Fringes[TargetVertex->Index] == NULL &&
                 CurrentEdge->Weight < Weights[TargetVertex->Index] )
                //�ּ� ����ġ ã�� !
            {
                
                PQNode NewNode =  { CurrentEdge->Weight, TargetVertex };
                //���� ������ ����ġ, ��ǥ ������ �̴ϼ� ������� PQNode ����
                PQ_Enqueue ( PQ, NewNode );
                //�� ��� �켱���� ť�� ����
                Precedences[TargetVertex->Index] = CurrentEdge->From;
                //��� ��� ����
                Weights[TargetVertex->Index]     = CurrentEdge->Weight;      
                //����ġ ���� 
            }
            //���� ���� �Ѿ��
            CurrentEdge = CurrentEdge->Next;
        }
    }

    for ( i=0; i<G->VertexCount; i++ )
    {
        int FromIndex, ToIndex;

        if ( Precedences[i] == NULL )
            continue;

        //��� ������ NULL�� �ƴ϶��
        FromIndex = Precedences[i]->Index;
        ToIndex   = i;

        //�̹� ���Ե� ������ ��Ͽ� ���� �߰�
        //���� ���� Edge �߰�
        AddEdge( MSTVertices[FromIndex], 
            CreateEdge( MSTVertices[FromIndex], MSTVertices[ToIndex],   Weights[i] ) );
        //�� ���� Edge �߰�
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
    //���� ������ ����Ű�� ������
    Vertex*       CurrentVertex = NULL;
    //��� ������ �����ϴ� �޸� ����
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
        //�θ� ��带 �����ϴ� Vertex ����
        VertexSet[i]   = DS_MakeSet( CurrentVertex );
        //���ؽ� ���� ����
        MSTVertices[i] = CreateVertex( CurrentVertex->Data );
        //�׷����� ���ؽ� ����
        AddVertex( MST, MSTVertices[i] );
        //���� ���ؽ� ���� ���� �ӽ� �޸� ���� ����
        CurrentEdge = CurrentVertex->AdjacencyList;
        //���ؽ� ����Ʈ ����
        while ( CurrentEdge != NULL )
        {
            //�� ��� �Ҵ�
            //���� �߽ɰ� ���� ���� ����
            PQNode NewNode = { CurrentEdge->Weight, CurrentEdge };
            //�켱���� ť�� �� ��� ����
            PQ_Enqueue( PQ, NewNode );
            //���� ���� ����
            CurrentEdge = CurrentEdge->Next;
        }
        //���� ������ ���� ���� ����
        CurrentVertex  = CurrentVertex->Next;        
        i++;
    }

    while ( !PQ_IsEmpty( PQ ) )
    {
        Edge*  CurrentEdge;
        int    FromIndex;
        int    ToIndex;
        PQNode Popped;
        //ť���� PQNode Dequeue
        PQ_Dequeue( PQ, &Popped );
        //���� ���� ������ �ӽ� �޸� ����
        CurrentEdge = (Edge*)Popped.Data;

        printf("%c - %c : %d\n", 
            CurrentEdge->From->Data, 
            CurrentEdge->Target->Data, 
            CurrentEdge->Weight );

        FromIndex = CurrentEdge->From->Index;
        ToIndex   = CurrentEdge->Target->Index;
        //������ ���谡 �ƴϸ�
        //�θ� ���� �ʴٸ�
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
