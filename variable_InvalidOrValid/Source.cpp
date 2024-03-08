#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define COL 15

void readFromFile(FILE* inp, char** arr, int size) {
	int i = 0;
	while (i != size)
	{
		fscanf(inp, " %[^\n]", arr[i]);
		i++;
	}
}

int countBlank(char let) {
	if (let == ' ')
		return 1;
	return 0;
}

int countPunc(char let) {
	return (ispunct(let));
}

int isValid(char *arr) {
	int sentlen = strlen(arr);
	if (arr[0] >= '0' && arr[0] <= '9')
		return 0;
	for (int c = 1; c < sentlen; c++)
		if ((arr[c] > ' ' && arr[c] < '0') || (countPunc(arr[c]) != 0) || (countBlank(arr[c]) != 0))
			return 0;
	return 1;
}

void newFormat(char* arr) {
	int sentlen = strlen(arr), temp;
	if (arr[0] >= '0' && arr[0] <= '9')
	{
		temp = arr[0];
		for (int c = 0; c < sentlen - 1; c++)
			arr[c] = arr[c + 1];
		arr[sentlen - 1] = temp;
	}

	for (int c = 0; c < sentlen; c++)
		if (!((arr[c] >= 'a' && arr[c] <= 'z') || (arr[c] >= 'A' && arr[c] <= 'Z') || (arr[c] >= '0' && arr[c] <= '9')))
			arr[c] = '_';
}

int main(void)
{
	FILE* inp;
	inp = fopen("VarNames.txt", "r");
	if (inp == NULL)
		printf("Error");
	else
	{
		char** arr;
		int size;
		fscanf(inp, "%d", &size);

		arr = (char**)malloc(sizeof(char*) * size);
		for (int i = 0; i < size; i++)
			arr[i] = (char*)malloc(sizeof(char) * COL);

		readFromFile(inp, arr, size);
		fclose(inp);

		printf("      Variables    Status     New Format\n");
		int validity;
		for (int r = 0; r < size; r++)
		{
			validity = isValid(arr[r]);
			printf("%15s ", arr[r]);
			switch (validity)
			{
			case 0:
				printf("  INVALID   ");  break;
			case 1:
				printf("  VALID     ");  break;
			}
			if (validity == 0)
				newFormat(arr[r]);
			printf("  %s", arr[r]);
			printf("\n");
		}

		free(arr);
	}
	return 0;
}