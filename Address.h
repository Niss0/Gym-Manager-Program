#pragma once
#include "General.h"

typedef struct
{
	char	city[MAX_LEN];						
	char	street[MAX_LEN];					
	int		streetNum;							
	int		floorNum;							
} Address;

void	initAddress(Address* pAddress);
void	printAddress(const Address* pAddress);