#include "PriorityQueue.h"

//우선순위 큐 동적 할당
PriorityQueue* PQ_Create( int IntitialSize )
{
	//우선순위 큐 구조체 동적 할당
    PriorityQueue* NewPQ = (PriorityQueue*) malloc( sizeof( PriorityQueue ) );
	//우선순위 큐 크기 할당
	NewPQ->Capacity = IntitialSize;
	//우선순위 큐 초기 크기 할당
    NewPQ->UsedSize = 0;
	//우선순위 큐 노드 동적 할당
    NewPQ->Nodes = (PQNode*) malloc( sizeof ( PQNode ) * NewPQ->Capacity );
	//우선순위 큐 구조체 리턴
    return NewPQ;
}

void  PQ_Destroy( PriorityQueue* PQ )
{
	//우선순위 큐 노드 메모리 해제
    free( PQ->Nodes );
	//우선순위 큐 구조체 메모리 해제
    free( PQ );
}

void  PQ_Enqueue( PriorityQueue* PQ, PQNode NewNode )
{
	//현재 큐 위치를 가져온다.
    int CurrentPosition = PQ->UsedSize;
	//부모 위치를 가져온다.
	int ParentPosition  = PQ_GetParent( CurrentPosition );
	//큐가 꽉 찼다면
    if ( PQ->UsedSize == PQ->Capacity ) 
    {
		//큐의 크기가 지정이 안된 경우
        if ( PQ->Capacity == 0 )
			//1로 만든다.
            PQ->Capacity = 1;
        //큐의 크기를 두배로 늘린다.
        PQ->Capacity *= 2;
		//큐 안의 노드를 다시 동적 할당한다.
        PQ->Nodes = (PQNode*) realloc( PQ->Nodes, sizeof( PQNode ) * PQ->Capacity );
    }
	//큐의 현재 위치에 새로운 데이터를 넣는다.
    PQ->Nodes[CurrentPosition] = NewNode;

    /*  후속 처리. */
	//현재 위치가 루트가 아니고(루트이면 스왑 할 필요가 없음)
	//현재 노드의 우선 순위가 부모 노드의 우선 순위보다 작다면
	//스왑!
    while ( CurrentPosition > 0 
        && PQ->Nodes[CurrentPosition].Priority < PQ->Nodes[ParentPosition].Priority )
    {
        PQ_SwapNodes( PQ, CurrentPosition, ParentPosition );
        //현재 위치를 부모의 위치로 바꾸고
        CurrentPosition = ParentPosition;
		//부모의 위치를 현재 위치의 부모로 바꾼다.
        ParentPosition  = PQ_GetParent( CurrentPosition );
    }

    PQ->UsedSize++;
}

void      PQ_SwapNodes( PriorityQueue* PQ, int Index1, int Index2 )
{ 
    int CopySize = sizeof( PQNode );
    PQNode* Temp = (PQNode*)malloc(CopySize);
        
    memcpy( Temp,               &PQ->Nodes[Index1], CopySize);
    memcpy( &PQ->Nodes[Index1] , &PQ->Nodes[Index2], CopySize);
    memcpy( &PQ->Nodes[Index2] , Temp,              CopySize);

    free(Temp);
}

void      PQ_Dequeue( PriorityQueue* PQ, PQNode* Root )
{
    int ParentPosition = 0;
    int LeftPosition   = 0;    
    int RightPosition  = 0;    
    
    memcpy(Root, &PQ->Nodes[0], sizeof(PQNode));
    memset(&PQ->Nodes[0], 0, sizeof(PQNode));

    PQ->UsedSize--;
    PQ_SwapNodes( PQ, 0, PQ->UsedSize );

    LeftPosition  = PQ_GetLeftChild( 0 );
    RightPosition = LeftPosition + 1;

    while ( 1 )
    {
        int SelectedChild = 0;

        if ( LeftPosition >= PQ->UsedSize )
            break;

        if ( RightPosition >= PQ->UsedSize )
        {
            SelectedChild = LeftPosition;
        }
        else {
            if ( PQ->Nodes[LeftPosition].Priority > PQ->Nodes[RightPosition].Priority)
                SelectedChild = RightPosition;
            else
                SelectedChild = LeftPosition;                
        }

        if ( PQ->Nodes[SelectedChild].Priority < PQ->Nodes[ParentPosition].Priority)
        {
            PQ_SwapNodes(PQ, ParentPosition, SelectedChild);
            ParentPosition = SelectedChild;
        }
        else
            break;

        LeftPosition  = PQ_GetLeftChild(ParentPosition);
        RightPosition = LeftPosition + 1;
    }

    if ( PQ->UsedSize < ( PQ->Capacity / 2 ) ) 
    {
        PQ->Capacity /= 2;
        PQ->Nodes = 
            (PQNode*) realloc( PQ->Nodes, sizeof( PQNode ) * PQ->Capacity );
    }
}

//부모 노드를 가져오는 함수
int PQ_GetParent( int Index )
{
    return (int) ((Index - 1) / 2);
}

int PQ_GetLeftChild( int Index )
{
    return (2 * Index) + 1;
}

int PQ_IsEmpty( PriorityQueue* PQ )
{
    return ( PQ->UsedSize == 0 );
}