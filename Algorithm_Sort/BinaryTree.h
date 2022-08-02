#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct tagSBTNode
{
	struct tagSBTNode* Left;
	struct tagSBTNode* Right;

	ElementType Data;
}SBTNode;

SBTNode* SBT_CrateNode(ElementType Newdata);
void SBT_DestroyNode(SBTNode* Node);
void SBT_DestroyTree(SBTNode* Root);

void SBT_PreorderPrintTree(SBTNode* Node);
void SBT_InorderPrintTree(SBTNode* Node);
void SBT_PostorderPrintTree(SBTNode* Node);



