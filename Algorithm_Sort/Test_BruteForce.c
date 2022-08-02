#include <stdio.h>
#include <string.h>
#include "BruteForce.h"

#define MAX_BUFFER 512

int main(int argc, char** argv)
{
	char* FilePath;
	FILE* fp = NULL;

	char Text[MAX_BUFFER];
	char* Pattern;
	int PatternSize = 0;
	int Line = 0;

	if (argc < 3)
	{
		printf("Usage: %s <FilaPath> <Pattern>\n", argv[0]);
		return 1;
	}

	FilePath = argv[1];
	Pattern = argv[2];

	PatternSize = strlen(Pattern);

	if ((fopen_s(fp, FilePath, "r")) == -1)
	{
		printf("Cannot open file:%s\n", FilePath);
		return 1;
	}

	while (fgets(Text, MAX_BUFFER, fp) != NULL)
	{
		int Position = BruteForce(Text, strlen(Text), 0, Pattern, PatternSize);

		if (Position > 0)
		{
			printf("line:%d, column:%d : %s", Line++, Position, Text);
		}
	}

	fclose(fp);
	return 0;
}