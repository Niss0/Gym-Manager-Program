#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileHelper.h"
#include "General.h"


// Write functions

int	 writeStringToBinFile(const char* str, FILE* fp)
{
	int length = (int)strlen(str);
	length++;
	if (!writeIntToBinFile(length, fp))
		return 0;

	if (!writeCharsToBinFile(str, length, fp))
		return 0;


	return 1;
}

int	 writeCharsToBinFile(const char* arr, int size, FILE* fp)
{
	if (fwrite(arr, sizeof(char), size, fp) != size)
		return 0;

	return 1;

}

int	 writeIntToBinFile(int val, FILE* fp)
{
	if (fwrite(&val, sizeof(int), 1, fp) != 1)
		return 0;

	return 1;
}

int	writeDoubleToBinFile(double val, FILE* fp)
{
	if (fwrite(&val, sizeof(double), 1, fp) != 1)
		return 0;
	return 1;
}

// Read functions

int readStringFromBinFile(char** pStr, FILE* fp)
{
	char* str = *pStr;
	int length = 0;
	if (!readIntFromBinFile(&length, fp))
		return 0;
	str = (char*)malloc((length + 1) * sizeof(char));
	if (str == NULL)
		return 0;
	if (fread(str, sizeof(char), length, fp) != length)
	{
		free(str);
		return 0;
	}
	str[length] = '\0';
	*pStr = str;

	return 1;
}

int readFixSizeStrFromBinFile(char* arr, FILE* fp)
{
	int len;
	if (!readIntFromBinFile(&len, fp))
		return 0;

	if (!readCharsFromBinFile(arr, len, fp))
		return 0;

	arr[len] = '\0';

	return 1;
}

int	 readCharsFromBinFile(char* arr, int length, FILE* fp)
{
	CHECK_IF_NOT_EQUALS(fread(arr, sizeof(char), length, fp), length, 0);

	return 1;
}

int	 readIntFromBinFile(int* pVal, FILE* fp)
{
	CHECK_IF_NOT_EQUALS(fread(pVal, sizeof(int), 1, fp), 1, 0);

	return 1;
}

int	readDoubleFromBinFile(double* pVal, FILE* fp)
{
	CHECK_IF_NOT_EQUALS(fread(pVal, sizeof(double), 1, fp), 1, 0);

	return 1;
}



char* readStrFromTextFile(FILE* fp)
{
	char tempBuffer[MAX_LEN] = { 0 };
	if (!fgets(tempBuffer, sizeof(tempBuffer), fp))
		return NULL;
	tempBuffer[strcspn(tempBuffer, "\n")] = '\0';
	return _strdup(tempBuffer);
}

