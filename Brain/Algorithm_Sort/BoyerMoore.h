#pragma once

#include <stdio.h>

int BoyerMoore(char* Text, int TextSize, int Start, char* Pattern, int PatternSize);
void BuildGST(char* Pattern, int PatternSize, int* Suffix, int* GST);
void BuildBCT(char* Pattern, int PatternSize, int * BST);
int Max(int A, int B);