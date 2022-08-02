#include "BinaryTree.h"

SBTNode* SBT_CrateNode(ElementType Newdata)
{
	SBTNode* NewNode = (SBTNode*)malloc(sizeof(SBTNode));
	NewNode->Data = Newdata;
	NewNode->Left = NULL;
	NewNode->Right = NULL;
}

void SBT_DestroyNode(SBTNode* Node)
{
	free(Node);
}

void SBT_DestroyTree(SBTNode* Node)
{
	if (Node == NULL)
		return;

	//노드의 왼쪽까지 타고 내려가고, 최 하위 왼쪽 노드이면
	//Left, Right가 NULL이므로 삭제 수행을 안하고
	//SBT_DestroyNode를 수행한다.
	SBT_DestroyNode(Node->Left);
	
	SBT_DestroyNode(Node->Right);

	SBT_DestroyNode(Node);
}

void SBT_PreorderPrintTree(SBTNode* Node)
{
	if (Node == NULL)
		return;

	printf("%c ", Node->Data);
	SBT_PreorderPrintTree(Node->Left);
	SBT_PreorderPrintTree(Node->Right);
}

void SBT_InorderPrintTree(SBTNode* Node)
{
	if (Node == NULL)
		return;

	SBT_InorderPrintTree(Node->Left);
	printf("%c ", Node->Data);
	SBT_InorderPrintTree(Node->Right);
}

void SBT_PostorderPrintTree(SBTNode* Node)
{
	if (Node == NULL)
		return;

	SBT_PostorderPrintTree(Node->Left);
	SBT_PostorderPrintTree(Node->Right);
	printf("%c ", Node->Data);
}