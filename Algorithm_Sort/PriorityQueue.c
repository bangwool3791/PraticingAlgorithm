#include "PriorityQueue.h"

//�켱���� ť�� �����ϴ� �Լ�
//�Ű� ������ �ʱ� �켱����ť ����� �޴´�.
PriorityQueue* PQ_Create(int InitialSize)
{
	//�����Ҵ�
	PriorityQueue* NewPQ = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	//�ʱ� ����� Capacity ���� ����
	NewPQ->Capacity = InitialSize;
	//UsedSize �ʱ� �� 0
	NewPQ->UsedSize = 0;
	//��带 Capacity��ŭ ���� �Ҵ�
	NewPQ->Nodes = (PQNode*)malloc(sizeof(PQNode) * NewPQ->Capacity);
	return NewPQ;
}

//PriorityQueue ���� �Լ�
void PQ_Destroy(PriorityQueue* PQ)
{
	//PriorityQueue �ȿ� Node�� ���� ���� ��
	free(PQ->Nodes);
	//PriorityQueue ����
	free(PQ);
}
//PriorityQueue�ȿ� �� ��� ���� �Լ�
void PQ_Enqueue(PriorityQueue* PQ, PQNode NewNode)
{
	//���� ť�� ���� �� ������ ��ġ
	int CurrentPosition = PQ->UsedSize;
	//���� ��ġ�� �θ� ��ġ
	int ParentPosition = PQ_GetParent(CurrentPosition);
	//���� ������� ť �Ҵ緮�� ���ٸ�
	if (PQ->UsedSize == PQ->Capacity)
	{
		//�ƿ� �Ҵ��� �ȵ� ���
		if (PQ->Capacity == 0)
		{
			//�Ҵ緮�� 1�� �����.
			PQ->Capacity = 1;
		}
		//�Ҵ緮�� �ι�� �ѵ�
		PQ->Capacity *= 2;
		//��忡 ���� �Ҵ��� �ٽ��Ѵ�.
		PQ->Nodes = (PQNode*)realloc(PQ->Nodes, sizeof(PQNode) * PQ->Capacity);
	}
	//�� ��带 �켱���� ť ���� ��ġ�� ����
	PQ->Nodes[CurrentPosition] = NewNode;
	//���� ��ġ�� 0���� ũ�� ���� ��ġ ��尡 �θ� ��庸�� �켱������ ���ٸ�
	while (CurrentPosition > 0 && PQ->Nodes[CurrentPosition].Priority < PQ->Nodes[ParentPosition].Priority)
	{
		//����
		PQ_SwapNodes(PQ, CurrentPosition, ParentPosition);
		//�켱������ ���� ������� �����Ѵ�.
		//�θ���ġ�� ���� ��ġ�� �־��ְ�
		CurrentPosition = ParentPosition;
		//�θ� ��ġ�� �ٲ� ������ġ�� �θ�� �����Ѵ�.
		ParentPosition = PQ_GetParent(CurrentPosition);
	}
	//�ȿ� �� ������ ũ�⸦ ������Ų��.
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

//�켱���� ť �ȿ��� �����͸� ������ �Լ�
void PQ_Dequeue(PriorityQueue* PQ, PQNode* Root)
{
	int ParentPosition = 0;
	int LeftPosition = 0;
	int RightPosition = 0;

	//��Ʈ ����� �����͸� �ӽ� ��ġ�� �̵�
	memcpy(Root, &PQ->Nodes[0], sizeof(PQNode));
	//��Ʈ ��� ������ �ʱ�ȭ
	memset(&PQ->Nodes[0], 0, sizeof(PQNode));
	//������ ��带 ��Ʈ ��忡 ����
	PQ->UsedSize--;
	PQ_SwapNodes(PQ, 0, PQ->UsedSize);
	//���� ��ġ Get
	LeftPosition = PQ_GetLeftChild(0);
	RightPosition = LeftPosition + 1;

	while (1)
	{
		int SelectedChild = 0;

		//������ ��� ��ġ��
		//���� ��ġ�� ���
		if (LeftPosition >= PQ->UsedSize)
		{
			//�극��ũ
			//�� ? �극��ũ ?
			break;
		}
		//������ ��ġ�� ���
		if (RightPosition >= PQ->UsedSize)
		{
			SelectedChild = LeftPosition;
		}
		else
		{
			//���� ����� ��ġ �켱������ ������ ��� ��ġ �켱 �������� ���ٸ�
			if (PQ->Nodes[LeftPosition].Priority < PQ->Nodes[RightPosition].Priority)
			{
				//�켱������ ���� ������ ��ġ�� ����
				SelectedChild = RightPosition;
			}
			else
			{
				//�켱������ ���� ���� ��ġ�� ����
				SelectedChild = LeftPosition;
			}
		}

		//���� ��� �켱������ �θ� ��� �켱�������� �۴ٸ� 
		if (PQ->Nodes[SelectedChild].Priority < PQ->Nodes[ParentPosition].Priority)
		{
			//���� ���� �θ� ��带 ����
			PQ_SwapNodes(PQ, ParentPosition, SelectedChild);
			ParentPosition = SelectedChild;
		}
		else
		{
			//���� �ʰ� �� ��ġ�� �־ �ȴٸ� �극��ũ
			break;
		}
		//�������� ��
		LeftPosition = PQ_GetLeftChild(ParentPosition);
		RightPosition = LeftPosition + 1;
	}
	//��� ����� �Ҵ緮 /2���� �۴ٸ�
	if (PQ->UsedSize < (PQ->Capacity / 2))
	{
		//�҈ԎU�� ���δ�.
		PQ->Capacity /= 2;
		PQ->Nodes = (PQNode*)realloc(PQ->Nodes, sizeof(PQNode) * PQ->Capacity);
	}
	//��Ʈ ��带 �����ν� �޸𸮵� ���̴� �ڵ�
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
