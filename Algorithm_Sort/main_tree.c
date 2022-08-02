#include "BinaryTree.h"

int main(void)
{
	SBTNode* A = SBT_CrateNode('A');
	SBTNode* B = SBT_CrateNode('B');
	SBTNode* C = SBT_CrateNode('C');
	SBTNode* D = SBT_CrateNode('D');
	SBTNode* E = SBT_CrateNode('E');
	SBTNode* F = SBT_CrateNode('F');
	SBTNode* G = SBT_CrateNode('G');

	A->Left = B;
	B->Left = C;
	B->Right = D;

	A->Right = E;
	E->Left = F;
	E->Right = G;

	printf("Preorder ...\n");
	SBT_PreorderPrintTree(A);
	printf("\n\n");

	printf("Inorder ...\n");
	SBT_InorderPrintTree(A);
	printf("\n\n");

	printf("Postorder ...\n");
	SBT_PostorderPrintTree(A);
	printf("\n\n");

	SBT_DestroyTree(A);

	return 0;
}