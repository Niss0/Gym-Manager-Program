#include "General.h"

char* getStrExactLength(const char* msg)
{
	char* theStr = NULL;
	char inpStr[MAX_LEN];

	puts(msg);
	if (!myGets(inpStr, sizeof(inpStr)))
		return NULL;

	theStr = _strdup(inpStr);
	return theStr;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;

	strcpy(theStr, str);
	return theStr;
}

char* myGets(char* buffer, int size)
{
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do { //skip only '\n' strings
			ok = fgets(buffer, size, stdin);
		} while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			//trim end spaces
			while ((buffer < back) && (isspace(*--back)));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

void generalArrayFunction(void* arr, int size, size_t typeSize, void (*f)(void*))
{
	for (int i = 0; i < size; i++)
	{
		printf("%d) ", i + 1);
		void* curElem = (void*)((char*)arr + i * typeSize);
		f(curElem);
	}
}

int getPositiveNumber(char* str)
{
	int temp;
	int firstTime = 1;
	do
	{
		if (firstTime)
			firstTime = 0;
		else
			printf("%s need to be positive \n", str);
		printf("%s: \n", str);
		scanf("%d", &temp);
	} while (temp < 0);

	return temp;
}

int getNumberInRange(char* str, int start, int end)
{
	int temp;
	int firstTime = 1;
	do
	{
		if (firstTime)
			firstTime = 0;
		else
		{
			if (start == end)
				printf("%s can be only %d \n", str, start);
			else
				printf("%s need to be between %d-%d \n", str, start, end);
		}
		printf("Enter %s: \n", str);
		scanf("%d", &temp);
	} while (temp < start || temp > end);

	return temp;
}

void printHeader(char* str)
{
	system("cls");
	printf("%s \n", str);
	printf("------------------------- \n");
}

void timeDelay(int number_of_seconds)
{
	int milli_seconds = 1000 * number_of_seconds;

	clock_t start_time = clock();

	while (clock() < start_time + milli_seconds);
}