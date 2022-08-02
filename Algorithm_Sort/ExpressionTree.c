#include "ExpressionTree.h"

ETNode* ET_CreateNode(ElementType NewData)
{
	ETNode* NewNode = (ETNode*)malloc(sizeof(ETNode));
	NewNode->Data = NewData;
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	return NewNode;
}

void ET_DestroyNode(ETNode* Node)
{
	free(Node);
}

void ET_DestroyTree(ETNode* Root)
{
	if (Root == NULL)
		return;

	ET_DestroyNode(Root->Left);
	ET_DestroyNode(Root->Right);
	ET_DestroyNode(Root);
}

void ET_PreorderPrintTree(ETNode* Node)
{
	if (Node == NULL)
		return;

	printf(" %c ", Node->Data);
	ET_PreorderPrintTree(Node->Left);
	ET_PreorderPrintTree(Node->Right);
}

void ET_InorderPrintTree(ETNode* Node)
{
	if (Node == NULL)
		return;

	printf("(");
	ET_InorderPrintTree(Node->Left);
	printf("%c", Node->Data);
	ET_InorderPrintTree(Node->Right);
	printf(")");
}

void ET_PostorderPrintTree(ETNode* Node)
{
	if (Node == NULL)
		return;

	ET_PostorderPrintTree(Node->Left);
	ET_PostorderPrintTree(Node->Right);
	printf(" %c", Node->Data);
}

void ET_BuildExpressionTree(char* PostfixExpression, ETNode** Node)
{
	//���ڿ� ���� �Է�
	int len = strlen(PostfixExpression);
	//���� �Է�
	char Token = PostfixExpression[len - 1];
	//���� ���� NULL ��ü
	PostfixExpression[len - 1] = '\0';

	switch (Token)
	{
	case '+':
	case '-':
	case '/':
	case '*':
		*Node = ET_CreateNode(Token);
		ET_BuildExpressionTree(PostfixExpression, &(*Node)->Right);
		ET_BuildExpressionTree(PostfixExpression, &( * Node)->Left);
	break;
	default:
		(*Node) = ET_CreateNode(Token);
		break;
	}
}

double ET_Evaluate(ETNode* Tree)
{
	char Temp[2];

	double Left = 0;
	double Right = 0;
	double Result = 0;

	switch (Tree->Data)
	{
	case '+':
	case '-':
	case '*':
	case '/':
		Left = ET_Evaluate(Tree->Left);
		Right = ET_Evaluate(Tree->Right);
		if (Tree->Data == '+')
			Result = Left + Right;
		if (Tree->Data == '-')
			Result = Left - Right;
		if (Tree->Data == '*')
			Result = Left * Right;
		if (Tree->Data == '/')
			Result = Left / Right;
		break;
	default:
		//��� �Է��� ���ڿ��� �������� null ������ �� ���� �ʱ�ȭ �Ѵ�.
		memset(Temp, 0, sizeof(Temp));
		Temp[0] = Tree->Data;
		Result = atof(Temp);
		break;
	}
	return Result;
}