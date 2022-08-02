#include "Huffman.h"
#include <string.h>

int main(void)
{
	int StringLen = strlen("http://www.seanlab.net") + 1;
	char* Source = (char*)malloc(sizeof(char) * StringLen);
	memset(Source, 0, sizeof(char) * StringLen);
	memcpy_s(Source, StringLen, "http://www.seanlab.net", StringLen);

	char* Decoded = (char*)malloc(sizeof(char) * StringLen);
	memset(Decoded, 0, sizeof(char) * StringLen);

	HuffmanNode* Tree = NULL;
	BitBuffer Encoded = { NULL, 0 };
	HuffmanCode CodeTable[MAX_CHAR];


	memset(&CodeTable, 0, sizeof(HuffmanCode) * MAX_CHAR);

	Huffman_Encode(&Tree, Source, &Encoded, CodeTable);

	printf("Original Size:%d Encoded Size:%d\n", (strlen(Source) + 1) * sizeof(char) * 8, Encoded.Size);

	Decoded = (char*)malloc(sizeof(char) * (strlen(Source) + 1));
	Huffman_Decode(Tree, &Encoded, Decoded);

	printf("Original : %s\n", Source);
	printf("Encoded : ");

	Huffman_PrintBinary(&Encoded);

	printf("\n");

	for (int k = 0; k < StringLen -1 ; k++)
	{
		printf("%c", Decoded[k]);
	}
	printf("\n");

	printf("Decoded : %s\n", Decoded);

	Huffman_DestroyTree(Tree);
	free(Decoded);
	free(Source);
	return 0;
}