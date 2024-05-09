#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "General.h"

int		writeStringToBinFile(const char* str, FILE* fp);
int		writeCharsToBinFile(const char* arr, int size, FILE* fp);
int		writeIntToBinFile(int val, FILE* fp);
int		writeDoubleToBinFile(double val, FILE* fp);

int		readStringFromBinFile(char** pStr, FILE* fp);
int		readFixSizeStrFromBinFile(char* arr, FILE* fp);
int		readCharsFromBinFile(char* arr, int length, FILE* fp);
int		readIntFromBinFile(int* pVal, FILE* fp);
int		readDoubleFromBinFile(double* pVal, FILE* fp);

char*	readStrFromTextFile(FILE* fp);
